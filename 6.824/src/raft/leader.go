package raft

import (
	"fmt"
	"time"
)

const (
	leaderIdle            = 50
	appendEntriesInterval = 100 // in millisecond
)

func (rf *Raft) sendHeartbeatToPeers(prevOutLink outLink) outLink {
	//DPrintf("raft[%d] sendHeartbeatToPeers", rf.me)
	n := len(rf.peers)
	reqs := make(map[int]interface{})
	for i := 0; i < n; i++ {
		if i == rf.me {
			continue
		}
		prevLogIndex := rf.ssLog.len() - 1
		prevLogTerm := 0
		if prevLogIndex >= 0 {
			prevLogTerm = rf.ssLog.termAt(prevLogIndex)
		}
		req := AppendEntriesReq{
			rf.currentTerm, rf.me, prevLogIndex, prevLogTerm, make([]LogEntry, 0), rf.commitIndex,
		}
		reqs[i] = req
	}
	olink := newOutLink(reqs, prevOutLink.replyCh)
	select {
	case <-rf.killed:
		panic("killed")
	case rf.outLinkCh <- olink:
	}
	return olink
}

func tryAnotherAppendEntries(lastTime time.Time) bool {
	return time.Since(lastTime).Milliseconds() > appendEntriesInterval
}

func (rf *Raft) sendAppendEntriesToPeers(prevOutLink outLink) outLink {
	n := len(rf.peers)
	reqs := make(map[int]interface{})
	for i := 0; i < n; i++ {
		if i == rf.me {
			continue
		}
		if rf.ssLog.len() > rf.nextIndex[i] {
			// avoid broadcasting storm
			if !tryAnotherAppendEntries(rf.appendEntriesJustSent[i]) {
				continue
			}
			rf.appendEntriesJustSent[i] = time.Now()

			prevLogIndex := rf.nextIndex[i] - 1
			if prevLogIndex < -1 {
				panic(fmt.Sprintf("prevLogIndex[%d] < -1", i))
			}
			prevLogTerm := 0

			if rf.nextIndex[i] > rf.ssLog.LastIncludedIndex {
				if prevLogIndex >= 0 {
					prevLogTerm = rf.ssLog.termAt(prevLogIndex)
				}
				nEntries := rf.ssLog.len() - rf.nextIndex[i]
				entries := make([]LogEntry, nEntries)
				si := rf.nextIndex[i]
				sj := si + nEntries
				rf.ssLog.copyTo(entries, si, sj)
				req := AppendEntriesReq{
					rf.currentTerm, rf.me, prevLogIndex, prevLogTerm, entries, rf.commitIndex,
				}
				reqs[i] = req
			} else {
				// 需要发送的 entry 已经被 snapshot 弃掉了，InstallSnapshot。
				req := installSnapshotReq{
					Term:              rf.currentTerm,
					LeaderId:          rf.me,
					LastIncludedIndex: rf.ssLog.LastIncludedIndex,
					LastIncludedTerm:  rf.ssLog.LastIncludedTerm,
					Offset:            0,
					Data:              rf.persister.ReadSnapshot(),
					Done:              true,
				}
				reqs[i] = req
			}
		}
	}
	olink := newOutLink(reqs, prevOutLink.replyCh)
	select {
	case <-rf.killed:
		panic("killed")
	case rf.outLinkCh <- olink:
	}
	return olink
}

func (rf *Raft) updateNextIndexAndMatchIndex(reply AppendEntriesReply) {
	req := reply.req
	peer := reply.me

	if reply.Success == eAppendEntriesOk {
		nAppended := len(req.Entries)
		rf.nextIndex[peer] = req.PrevLogIndex + nAppended + 1
		rf.matchIndex[peer] = rf.nextIndex[peer] - 1
		rf.appendEntriesJustSent[peer] = time.Time{}

	} else if reply.Success == eAppendEntriesLogInconsistent {
		if rf.nextIndex[peer] > reply.ConflictFirst {
			if reply.ConflictFirst < 0 {
				panic(fmt.Sprintf("reply.ConflictFirst(=%d) < 0", reply.ConflictFirst))
			}
			rf.nextIndex[peer] = reply.ConflictFirst
			rf.appendEntriesJustSent[peer] = time.Time{}
		}

	} else {
		//DPrintf("rf[%d].updateNextIndexAndMatchIndex: reply = %v", rf.me, reply)
	}
}

func (rf *Raft) updateCommitIndex() {
	n := len(rf.peers)
	maj := n/2 + 1
	for nci := rf.commitIndex + 1; nci < rf.ssLog.len(); nci++ {
		cnt := 1
		for i := 0; i < n; i++ {
			if i == rf.me {
				continue
			}
			if rf.matchIndex[i] >= nci {
				cnt++
			}
		}
		if cnt >= maj && nci < rf.ssLog.LastIncludedIndex {
			DPrintf("rf[%d].updateCommitIndex, commitIndex=%d, nci=%d, lastIncludedIndex=%d, logLen=%d",
				rf.me, rf.commitIndex, nci, rf.ssLog.LastIncludedIndex, rf.ssLog.len())
		}
		if cnt >= maj && rf.ssLog.termAt(nci) == rf.currentTerm {
			rf.commitIndex = nci
			//DPrintf("rf[%d].updateCommitIndex, commitIndex=%d", rf.me, rf.commitIndex)
		}
	}
}

func (rf *Raft) applyIfPossible() {
	for i := rf.lastApplied + 1; i <= rf.commitIndex; i++ {
		if i < 0 || i <= rf.ssLog.LastIncludedIndex {
			DPrintf("rf[%d], i=%d, lastIncludedIndex=%d, lastApplied=%d", rf.me, i, rf.ssLog.LastIncludedIndex, rf.lastApplied)
		}
		applyMsg := ApplyMsg{i + 1, rf.ssLog.at(i).Command, false, nil}
		//DPrintf("rf[%d] apply %+v", rf.me, applyMsg)
		rf.applyCh <- applyMsg
	}
	rf.lastApplied = rf.commitIndex
	//DPrintf("rf[%d].applyIfPossible, lastApplied = %d", rf.me, rf.lastApplied)
}

func (rf *Raft) handleAppendEntriesReply(reply AppendEntriesReply) (suppressed bool) {
	if reply.Term < rf.currentTerm {
		// 实际上不可能出现，但是这里被复用来表示网络错误。我当时为什么会这么写？WTF。
		return false
	} else if reply.Term == rf.currentTerm {
		rf.updateNextIndexAndMatchIndex(reply)
		rf.updateCommitIndex()
		rf.applyIfPossible()
		return false
	} else {
		if reply.Success != eAppendEntriesLessTerm {
			panic("reply.Success != eAppendEntriesLessTerm")
		}
		rf.currentTerm = reply.Term
		rf.votedFor = -1
		rf.persist()
		return true
	}
}

func (rf *Raft) handleInstallSnapshotReply(reply installSnapshotReply) (suppressed bool) {
	if reply.Term < rf.currentTerm {
		panic("reply.Term < rf.currentTerm")
	} else if reply.Term == rf.currentTerm {
		req := reply.req
		peer := reply.me
		rf.nextIndex[peer] = req.LastIncludedIndex + 1
		rf.matchIndex[peer] = req.LastIncludedIndex
		rf.appendEntriesJustSent[peer] = time.Time{}
		return false
	} else {
		rf.currentTerm = reply.Term
		rf.votedFor = -1
		rf.persist()
		return true
	}
}

func (rf *Raft) runAsLeader() {
	//DPrintf("raft[%d] runAsLeader", rf.me)

	n := len(rf.peers)
	rf.nextIndex = make([]int, n)
	rf.matchIndex = make([]int, n)
	for i := 0; i < n; i++ {
		rf.nextIndex[i] = rf.ssLog.len()
		rf.matchIndex[i] = -1
	}

	rf.appendEntriesJustSent = make([]time.Time, n)

	olink := newOutLink(make(map[int]interface{}), make(chan interface{}))
	olink = rf.sendHeartbeatToPeers(olink)
	defer olink.ignoreReplies()

	ticker := time.NewTicker(time.Duration(leaderIdle) * time.Millisecond)
	defer ticker.Stop()

	for {
		select {
		case <-rf.killed:
			panic("killed")

		case <-ticker.C: // time for next heartbeat
			olink = rf.sendHeartbeatToPeers(olink)

		case iReply := <-olink.replyCh:
			switch iReply.(type) {
			case AppendEntriesReply:
				reply := iReply.(AppendEntriesReply)
				suppressed := rf.handleAppendEntriesReply(reply)
				if suppressed {
					rf.state = eFollower
					return
				}
				olink = rf.sendAppendEntriesToPeers(olink)

			case installSnapshotReply:
				reply := iReply.(installSnapshotReply)
				suppressed := rf.handleInstallSnapshotReply(reply)
				if suppressed {
					rf.state = eFollower
					return
				}
				olink = rf.sendAppendEntriesToPeers(olink)
			}

		case ilink := <-rf.inLinkCh:
			//DPrintf("raft[%d](leader) ilink %+v", rf.me, ilink)
			req := ilink.req

			switch req.(type) {
			case killReq:
				close(rf.killed)
				return

			case getStateReq:
				select {
				case <-rf.killed:
					return
				case ilink.replyCh <- getStateReply{rf.currentTerm, true}:
				}

			case startReq:
				// len(rf.log) + 1, since the test cases start index at 1 (other than 0).
				reply := startReply{rf.ssLog.len() + 1, rf.currentTerm, true}
				select {
				case <-rf.killed:
					return
				case ilink.replyCh <- reply:
				}
				sreq := req.(startReq)
				rf.ssLog.append(LogEntry{sreq.command, rf.currentTerm})
				rf.persist()
				olink = rf.sendAppendEntriesToPeers(olink)

			case snapshotReq:
				reply := rf.handleSnapshotReq(ilink)
				select {
				case <-rf.killed:
					return
				case ilink.replyCh <- reply:
				}

			case RequestVoteReq:
				reply, suppressed := rf.handleRequestVoteReq(ilink)
				select {
				case <-rf.killed:
					return
				case ilink.replyCh <- reply:
				}
				if suppressed {
					rf.state = eFollower
					return
				}

			case AppendEntriesReq:
				reply, suppressed := rf.handleAppendEntriesReq(ilink)
				select {
				case <-rf.killed:
					return
				case ilink.replyCh <- reply:
				}
				if suppressed {
					rf.state = eFollower
					return
				}

			case installSnapshotReq:
				reply, suppressed := rf.handleInstallSnapshotReq(ilink)
				select {
				case <-rf.killed:
					return
				case ilink.replyCh <- reply:
				}
				if suppressed {
					rf.state = eFollower
					return
				}

			default:
				panic(fmt.Sprintf("unknown req = %+v", req))
			}
		}
	}
}
