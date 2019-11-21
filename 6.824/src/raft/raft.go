package raft

//
// this is an outline of the API that raft must expose to
// the service (or tester). see comments below for
// each of these functions for more details.
//
// rf = Make(...)
//   create a new Raft server.
// rf.Start(command interface{}) (index, term, isleader)
//   start agreement on a new log entry
// rf.GetState() (term, isLeader)
//   ask a Raft for its current term, and whether it thinks it is leader
// ApplyMsg
//   each time a new entry is committed to the log, each Raft peer
//   should send an ApplyMsg to the service (or tester)
//   in the same server.
//

import (
	"fmt"
	"labrpc"
	"math/rand"
	"sync"
	"time"
)

// import "bytes"
// import "encoding/gob"

type state int
type AppendEntriesError int

const (
	eFollower state = iota
	eCandidate
	eLeader
)

const (
	eAppendEntriesOk AppendEntriesError = 1
	eAppendEntriesErr = 2
	eAppendEntriesLessTerm = 3
	eAppendEntriesLogInconsistent = 4
)

const (
	electionTimeoutMin = 150
	electionTimeoutMax = 300
	leaderIdle = 50
)

//
// as each Raft peer becomes aware that successive log entries are
// committed, the peer should send an ApplyMsg to the service (or
// tester) on the same server, via the applyCh passed to Make().
//
type ApplyMsg struct {
	Index       int
	Command     interface{}
	UseSnapshot bool   // ignore for lab2; only used in lab3
	Snapshot    []byte // ignore for lab2; only used in lab3
}

type requestVoteReqAndReplyChan struct {
	req RequestVoteReq
	ch chan RequestVoteReply
}

type appendEntriesReqAndReplyChan struct {
	req AppendEntriesReq
	ch chan AppendEntriesReply
}

type LogEntry struct {
	Command interface{}
	Term int
}

//
// A Go object implementing a single Raft peer.
//
type Raft struct {
	mtx     sync.Mutex
	peers     []*labrpc.ClientEnd
	persister *Persister
	me        int // index into peers[]

	// Your data here.
	// Look at the paper's Figure 2 for a description of what
	// state a Raft server must maintain.

	electionTimeout time.Duration
	state state
	recvRequestVoteReq chan requestVoteReqAndReplyChan
	recvRequestVoteReply chan RequestVoteReply
	recvAppendEntriesReq chan appendEntriesReqAndReplyChan
	recvAppendEntriesReply chan AppendEntriesReply
	recvGetState chan chan getStateReply
	recvStartReq chan startReqAndReplyChan
	applyCh chan ApplyMsg

	currentTerm int
	votedFor int
	log []LogEntry
	commitIndex int
	lastApplied int
	nextIndex []int
	matchIndex []int
}

type getStateReply struct{
	term int
	state state
}

// return currentTerm and whether this server
// believes it is the leader.
func (rf *Raft) GetState() (int, bool) {
	var term int
	var isleader bool

	// Your code here.
	ch := make(chan getStateReply)
	rf.recvGetState <- ch
	reply := <-ch
	term = reply.term
	isleader = reply.state == eLeader

	return term, isleader
}

//
// save Raft's persistent state to stable storage,
// where it can later be retrieved after a crash and restart.
// see paper's Figure 2 for a description of what should be persistent.
//
func (rf *Raft) persist() {
	// Your code here.
	// Example:
	// w := new(bytes.Buffer)
	// e := gob.NewEncoder(w)
	// e.Encode(rf.xxx)
	// e.Encode(rf.yyy)
	// data := w.Bytes()
	// rf.persister.SaveRaftState(data)
}

//
// restore previously persisted state.
//
func (rf *Raft) readPersist(data []byte) {
	// Your code here.
	// Example:
	// r := bytes.NewBuffer(data)
	// d := gob.NewDecoder(r)
	// d.Decode(&rf.xxx)
	// d.Decode(&rf.yyy)
}


//
// example RequestVote RPC arguments structure.
//
type RequestVoteReq struct {
	// Your data here.
	Term int
	CandidateId int
	LastLogIndex int
	LastLogTerm int
}

//
// example RequestVote RPC reply structure.
//
type RequestVoteReply struct {
	// Your data here.
	Term int
	VoteGranted bool
}

//
// example RequestVote RPC handler.
//
func (rf *Raft) RequestVote(req RequestVoteReq, reply *RequestVoteReply) {
	// Your code here.
	replyCh := make(chan RequestVoteReply)
	rf.recvRequestVoteReq <- requestVoteReqAndReplyChan{req, replyCh}
	*reply = <-replyCh
}

//
// example code to send a RequestVote RPC to a server.
// server is the index of the target server in rf.peers[].
// expects RPC arguments in args.
// fills in *reply with RPC reply, so caller should
// pass &reply.
// the types of the args and reply passed to Call() must be
// the same as the types of the arguments declared in the
// handler function (including whether they are pointers).
//
// returns true if labrpc says the RPC was delivered.
//
// if you're having trouble getting RPC to work, check that you've
// capitalized all field names in structs passed over RPC, and
// that the caller passes the address of the reply struct with &, not
// the struct itself.
//
func (rf *Raft) sendRequestVote(server int, req RequestVoteReq, reply *RequestVoteReply) bool {
	ok := rf.peers[server].Call("Raft.RequestVote", req, reply)
	return ok
}

type AppendEntriesReq struct {
	Term int
	LeaderId int
	PrevLogIndex int
	PrevLogTerm int
	Entries []LogEntry
	LeaderCommit int
}

type AppendEntriesReply struct {
	Term int
	Success AppendEntriesError
	me int
	req AppendEntriesReq
}

func (rf *Raft) AppendEntries(req AppendEntriesReq, reply *AppendEntriesReply) {
	replyCh := make(chan AppendEntriesReply)
	rf.recvAppendEntriesReq <- appendEntriesReqAndReplyChan{req, replyCh}
	*reply = <-replyCh
}

func (rf *Raft) sendAppendEntries(server int, req AppendEntriesReq, reply *AppendEntriesReply) bool {
	ok := rf.peers[server].Call("Raft.AppendEntries", req, reply)
	return ok
}

type startReply struct {
	index int
	term int
	isLeader bool
}

type startReqAndReplyChan struct {
	command interface{}
	ch chan startReply
}

//
// the service using Raft (e.g. a k/v server) wants to start
// agreement on the next command to be appended to Raft's log. if this
// server isn't the leader, returns false. otherwise start the
// agreement and return immediately. there is no guarantee that this
// command will ever be committed to the Raft log, since the leader
// may fail or lose an election.
//
// the first return value is the index that the command will appear at
// if it's ever committed. the second return value is the current
// term. the third return value is true if this server believes it is
// the leader.
//
func (rf *Raft) Start(command interface{}) (int, int, bool) {
	replyCh := make(chan startReply)
	rf.recvStartReq <- startReqAndReplyChan{command, replyCh}
	reply := <-replyCh

	index := reply.index
	term := reply.term
	isLeader := reply.isLeader

	return index, term, isLeader
}

//
// the tester calls Kill() when a Raft instance won't
// be needed again. you are not required to do anything
// in Kill(), but it might be convenient to (for example)
// turn off debug output from this instance.
//
func (rf *Raft) Kill() {
	// Your code here, if desired.
}

func (rf *Raft) upToDate(lastLogIndex int, lastLogTerm int) bool {
	myLastLogIndex := len(rf.log) - 1
	var myLastLogTerm int
	if myLastLogIndex == -1 { // maybe more assertions
		myLastLogTerm = 0
	} else {
		myLastLogTerm = rf.log[myLastLogIndex].Term
	}
	if myLastLogTerm < lastLogTerm {
		return true
	}
	return myLastLogIndex <= lastLogIndex
}

func (rf *Raft) handleRequestVoteReq(rc requestVoteReqAndReplyChan) bool {
	req := rc.req
	ch := rc.ch
	reply := RequestVoteReply{}
	suppressed := false

	if req.Term < rf.currentTerm {
		reply.Term = rf.currentTerm
		reply.VoteGranted = false

	} else if req.Term == rf.currentTerm {
		reply.Term = rf.currentTerm

		if rf.upToDate(req.LastLogIndex, req.LastLogTerm) && (rf.votedFor == -1 || rf.votedFor == req.CandidateId) {
			rf.votedFor = req.CandidateId
			reply.VoteGranted = true
		} else {
			reply.VoteGranted = false
		}

	} else {
		rf.currentTerm = req.Term
		reply.Term = rf.currentTerm

		if rf.upToDate(req.LastLogIndex, req.LastLogTerm) {
			rf.votedFor = req.CandidateId
			reply.VoteGranted = true
		} else {
			rf.votedFor = -1
			reply.VoteGranted = false
		}
		suppressed = true
	}
	ch <- reply
	return suppressed
}

func (rf *Raft) checkPrevLogEntry(prevLogIndex int, prevLogTerm int) bool {
	if prevLogIndex < -1 {
		panic("prevLogIndex < -1")
	}
	if prevLogIndex == -1 {
		return true
	}
	if prevLogIndex >= len(rf.log) {
		return false
	}
	return rf.log[prevLogIndex].Term == prevLogTerm
}

func (rf *Raft) appendEntriesToLocal(prevLogIndex int, entries []LogEntry) {
	for i := 0; i < len(entries); i++ {
		j := prevLogIndex + 1 + i
		if j < len(rf.log) {
			if rf.log[j].Term != entries[i].Term {
				rf.log = rf.log[:j]
				rf.log = append(rf.log, entries[i])
			}
		} else {
			rf.log = append(rf.log, entries[i])
		}
	}
}

func (rf *Raft) handleAppendEntriesReq(rc appendEntriesReqAndReplyChan) bool {
	req := rc.req
	ch := rc.ch
	reply := AppendEntriesReply{}
	suppressed := false

	if req.Term < rf.currentTerm {
		reply.Term = rf.currentTerm
		reply.Success = eAppendEntriesLessTerm

	} else if req.Term == rf.currentTerm {
		suppressed = true
		reply.Term = rf.currentTerm

		if !rf.checkPrevLogEntry(req.PrevLogIndex, req.PrevLogTerm) {
			//DPrintf("inconsistent")
			reply.Success = eAppendEntriesLogInconsistent
		} else {
			reply.Success = eAppendEntriesOk
			rf.appendEntriesToLocal(req.PrevLogIndex, req.Entries)
			//DPrintf("ok req.Entries = %v, rf.log = %v", req.Entries, rf.log)
		}

	} else {
		suppressed = true
		rf.currentTerm = req.Term
		rf.votedFor = -1
		reply.Term = rf.currentTerm

		if !rf.checkPrevLogEntry(req.PrevLogIndex, req.PrevLogTerm) {
			reply.Success = eAppendEntriesLogInconsistent
		} else {
			reply.Success = eAppendEntriesOk
			rf.appendEntriesToLocal(req.PrevLogIndex, req.Entries)
		}
	}

	if req.LeaderCommit > rf.commitIndex {
		if len(rf.log) - 1 < req.LeaderCommit {
			rf.commitIndex = len(rf.log) - 1
		} else {
			rf.commitIndex = req.LeaderCommit
		}
	}
	rf.applyIfPossible()

	ch <- reply
	return suppressed
}

func (rf *Raft) updateNextIndexAndMatchIndex(reply AppendEntriesReply) {
	req := reply.req
	peer := reply.me

	if reply.Success == eAppendEntriesOk {
		// TODO out of order?
		nAppended := len(req.Entries)
		rf.nextIndex[peer] = req.PrevLogIndex + nAppended + 1
		rf.matchIndex[peer] = rf.nextIndex[peer] - 1

	} else if reply.Success == eAppendEntriesLogInconsistent {
		rf.nextIndex[peer] -= 1

	} else {
		panic("reply.Success is invalid")
	}
}

func (rf *Raft) updateCommitIndex() {
	n := len(rf.peers)
	maj := n / 2 + 1
	for nci := rf.commitIndex + 1; nci < len(rf.log); nci++ {
		cnt := 1
		for i := 0; i < n; i++ {
			if i == rf.me {
				continue
			}
			if rf.matchIndex[i] >= nci {
				cnt++
			}
		}
		if cnt >= maj && rf.log[nci].Term == rf.currentTerm {
			rf.commitIndex = nci
		}
	}
}

func (rf *Raft) applyIfPossible() {
	//DPrintf("lastApplied = %d, commitIndex = %d", rf.lastApplied, rf.commitIndex)
	for i := rf.lastApplied + 1; i <= rf.commitIndex; i++ {
		applyMsg := ApplyMsg{i + 1, rf.log[i].Command, false, nil}
		rf.applyCh <- applyMsg
	}
	rf.lastApplied = rf.commitIndex
}

func (rf *Raft) handleAppendEntriesReply(reply AppendEntriesReply) bool {
	if reply.Term < rf.currentTerm {
		// actually should not be here, confusing, bad.
		return false

	} else if reply.Term == rf.currentTerm {
		//DPrintf("raft[%d] recv from raft[%d]: term = %d, prevLogIndex = %d, entries = %v, success = %v", rf.me, reply.me, reply.Term, reply.req.PrevLogIndex, reply.req.Entries, reply.Success)
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
		return true
	}
}

func (rf *Raft) handleUnexpectedReply(Term int) bool {
	if Term <= rf.currentTerm {
		return false
	}
	rf.currentTerm = Term
	rf.votedFor = -1
	return true
}

func (rf *Raft) runAsFollower() {
	waitUntil := time.Now().Add(rf.electionTimeout)
	for {
		select {
		case ch := <-rf.recvGetState:
			ch <- getStateReply{rf.currentTerm, rf.state}

		case rc := <-rf.recvStartReq:
			rc.ch <- startReply{-1, rf.currentTerm, false}

		case rc := <-rf.recvRequestVoteReq:
			rf.handleRequestVoteReq(rc)
			return

		case reply := <-rf.recvRequestVoteReply:
			rf.handleUnexpectedReply(reply.Term)

		case rc := <-rf.recvAppendEntriesReq:
			rf.handleAppendEntriesReq(rc)
			return

		case reply := <-rf.recvAppendEntriesReply:
			rf.handleUnexpectedReply(reply.Term)

		case <- time.After(waitUntil.Sub(time.Now())):
			rf.state = eCandidate
			return
		}
	}
}

func (rf *Raft) runAsCandidate() {
	rf.currentTerm++
	rf.votedFor = rf.me

	n := len(rf.peers)
	if n == 1 {
		rf.state = eLeader
		return
	}

	lastLogIndex := len(rf.log) - 1
	var lastLogTerm int
	if lastLogIndex == -1 { // maybe more assertions
		lastLogTerm = 0
	} else {
		lastLogTerm = rf.log[lastLogIndex].Term
	}
	req := RequestVoteReq{
		rf.currentTerm, rf.me, lastLogIndex, lastLogTerm,
	}
	for i := 0; i < n; i++ {
		if i == rf.me {
			continue
		}
		go func(i1 int) {
			reply := RequestVoteReply{}
			ok := rf.sendRequestVote(i1, req, &reply)
			if !ok {
				reply.Term = 0
				reply.VoteGranted = false
			}
			rf.recvRequestVoteReply <- reply
		}(i)
	}

	waitUntil := time.Now().Add(rf.electionTimeout)
	vote := 1
	quorum := n / 2 + 1
	for {
		select {
		case ch := <-rf.recvGetState:
			ch <- getStateReply{rf.currentTerm, rf.state}

		case rc := <-rf.recvStartReq:
			rc.ch <- startReply{-1, rf.currentTerm, false}

		case rc := <-rf.recvRequestVoteReq:
			suppressed := rf.handleRequestVoteReq(rc)
			if suppressed {
				rf.state = eFollower
				return
			}

		case reply := <-rf.recvRequestVoteReply:
			if reply.Term > rf.currentTerm {
				rf.currentTerm = reply.Term
				rf.votedFor = -1
				rf.state = eFollower
				return
			} else {
				if reply.VoteGranted {
					vote++
					if vote == quorum {
						// to avoid leaking, trailing replies are read in leader routine.
						rf.state = eLeader
						return
					}
				}
			}

		case rc := <-rf.recvAppendEntriesReq:
			suppressed := rf.handleAppendEntriesReq(rc)
			if suppressed {
				rf.state = eFollower
				return
			}

		case reply := <-rf.recvAppendEntriesReply:
			// TODO warn weired case
			suppressed := rf.handleUnexpectedReply(reply.Term)
			if suppressed {
				rf.state = eFollower
				return
			}

		case <- time.After(waitUntil.Sub(time.Now())):
			return
		}
	}
}

func (rf *Raft) sendHeartbeat() {
	n := len(rf.peers)
	for i := 0; i < n; i++ {
		if i == rf.me {
			continue
		}
		prevLogIndex := rf.nextIndex[i] - 1
		prevLogTerm := 0
		if prevLogIndex >= 0 {
			prevLogTerm = rf.log[prevLogIndex].Term
		}
		req := AppendEntriesReq{
			rf.currentTerm, rf.me, prevLogIndex, prevLogTerm, make([]LogEntry, 0), rf.commitIndex,
		}
		go func(i1 int, req1 AppendEntriesReq) {
			reply := AppendEntriesReply{}
			ok := rf.sendAppendEntries(i1, req1, &reply)
			if !ok {
				reply.Term = 0
				reply.Success = eAppendEntriesErr
			}
			reply.me = i1
			reply.req = req1
			rf.recvAppendEntriesReply <- reply
		}(i, req)
	}
}

func (rf *Raft) sendAppendEntriesIfNecessary() {
	n := len(rf.peers)
	for i := 0; i < n; i++ {
		if i == rf.me {
			continue
		}
		if len(rf.log) > rf.nextIndex[i] {
			prevLogIndex := rf.nextIndex[i] - 1
			if prevLogIndex < -1 {
				panic(fmt.Sprintf("prevLogIndex[%d] < -1", i))
			}
			prevLogTerm := 0
			if prevLogIndex >= 0 {
				prevLogTerm = rf.log[prevLogIndex].Term
			}
			nEntries := len(rf.log) - rf.nextIndex[i]
			entries := make([]LogEntry, nEntries)
			si := rf.nextIndex[i]
			sj := si + nEntries
			copy(entries, rf.log[si:sj])
			req := AppendEntriesReq{
				rf.currentTerm, rf.me, prevLogIndex, prevLogTerm, entries, rf.commitIndex,
			}
			//DPrintf("raft[%d] send index %d cmd %v to raft[%d]", rf.me, prevLogIndex + 1, entries, i)
			go func(i1 int, req1 AppendEntriesReq) {
				reply := AppendEntriesReply{}
				ok := rf.sendAppendEntries(i1, req1, &reply)
				if !ok {
					reply.Term = 0
					reply.Success = eAppendEntriesErr
				}
				reply.me = i1
				reply.req = req1
				//DPrintf("raft[%d] recv from %v raft[%d]", rf.me, reply.Success, i1)
				rf.recvAppendEntriesReply <- reply
			}(i, req)
		}
	}
}

func (rf *Raft) runAsLeader() {
	n := len(rf.peers)
	rf.nextIndex = make([]int, n)
	rf.matchIndex = make([]int, n)
	for i := 0; i < n; i++ {
		rf.nextIndex[i] = len(rf.log)
		rf.matchIndex[i] = -1
	}

	for { // every `leaderIdle` milliseconds
		rf.sendHeartbeat()

		waitUntil := time.Now().Add(leaderIdle * time.Millisecond)
		WAIT_DONE:
		for {
			select {
			case ch := <-rf.recvGetState:
				ch <- getStateReply{rf.currentTerm, rf.state}

			case rc := <-rf.recvStartReq:
				//DPrintf("raft[%d] recv start req as leader", rf.me)
				index := len(rf.log)
				rc.ch <- startReply{index + 1, rf.currentTerm, true}
				rf.log = append(rf.log, LogEntry{rc.command, rf.currentTerm})
				rf.sendAppendEntriesIfNecessary()

			case rc := <-rf.recvRequestVoteReq:
				suppressed := rf.handleRequestVoteReq(rc)
				if suppressed {
					rf.state = eFollower
					return
				}

			case reply := <-rf.recvRequestVoteReply:
				suppressed := rf.handleUnexpectedReply(reply.Term)
				if suppressed {
					rf.state = eFollower
					return
				}

			case rc := <-rf.recvAppendEntriesReq:
				suppressed := rf.handleAppendEntriesReq(rc)
				if suppressed {
					rf.state = eFollower
					return
				}

			case reply := <-rf.recvAppendEntriesReply:
				suppressed := rf.handleAppendEntriesReply(reply)
				if suppressed {
					rf.state = eFollower
					return
				}
				rf.sendAppendEntriesIfNecessary()

			case <- time.After(waitUntil.Sub(time.Now())):
				break WAIT_DONE
			}
		}
	}
}

func (rf *Raft) run() {
	for {
		a, b := electionTimeoutMin, electionTimeoutMax
		rf.electionTimeout = time.Duration((rand.Intn(b - a) + a)) * time.Millisecond

		switch rf.state {
		case eFollower:
			rf.runAsFollower()
		case eCandidate:
			rf.runAsCandidate()
		case eLeader:
			rf.runAsLeader()
		}
	}
}

//
// the service or tester wants to create a Raft server. the ports
// of all the Raft servers (including this one) are in peers[]. this
// server's port is peers[me]. all the servers' peers[] arrays
// have the same order. persister is a place for this server to
// save its persistent state, and also initially holds the most
// recent saved state, if any. applyCh is a channel on which the
// tester or service expects Raft to send ApplyMsg messages.
// Make() must return quickly, so it should start goroutines
// for any long-running work.
//
func Make(peers []*labrpc.ClientEnd, me int,
	persister *Persister, applyCh chan ApplyMsg) *Raft {
	rf := &Raft{}
	rf.peers = peers
	rf.persister = persister
	rf.me = me

	// Your initialization code here.
	rf.recvRequestVoteReq = make(chan requestVoteReqAndReplyChan)
	rf.recvRequestVoteReply = make(chan RequestVoteReply)
	rf.recvAppendEntriesReq = make(chan appendEntriesReqAndReplyChan)
	rf.recvAppendEntriesReply = make(chan AppendEntriesReply)
	rf.recvGetState = make(chan chan getStateReply)
	rf.recvStartReq = make(chan startReqAndReplyChan)
	rf.applyCh = applyCh

	rf.currentTerm = 0
	rf.votedFor = -1
	rf.log = make([]LogEntry, 0)
	rf.commitIndex = -1
	rf.lastApplied = -1

	// initialize from state persisted before a crash
	rf.readPersist(persister.ReadRaftState())

	go rf.run()

	return rf
}
