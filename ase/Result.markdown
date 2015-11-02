# Advanced Software Engineering Lab 1

---

# Part 1: The dining philosophers

（1）通过 `atomic` 关键字保护 Critical Section，避免 Data Race。`g_fork` 变量表示资源可用性，每次获取资源之后，使用之前通过 `assert` 检查 `g_fork` 变量。具体实现请参阅 `dining-1.pml`。

```c
atomic {
	if
	:: g_forks[fl] ->
		assert(g_forks[fl]);
```

（2）是的，原始的模型存在死锁的问题：

```bash
% spin dining-1.pml
      timeout
#processes: 5
		g_forks[0] = 0
		g_forks[1] = 0
		g_forks[2] = 0
		g_forks[3] = 0
147:	proc  4 (phil:1) phil-1.pml:28 (state 14)
147:	proc  3 (phil:1) phil-1.pml:28 (state 14)
147:	proc  2 (phil:1) phil-1.pml:28 (state 14)
147:	proc  1 (phil:1) phil-1.pml:28 (state 14)
147:	proc  0 (:init::1) phil-1.pml:57 (state 19) <valid end state>
5 processes created
```
死锁由于*持锁等待*导致，通过资源分级的方案，解决死锁问题。对叉子进行编号，哲学家不再先拿起左手边的叉子，而是拿起较小编号的叉子。

```bash
if
:: id < N_PHIL - 1 ->
	fl = id;
	fr = (id + 1) % N_PHIL;
:: else ->
	assert(id == N_PHIL - 1);
	fl = 0;
	fr = id;
fi
```

实现细节可以参考 `dining-2.pml`。通过 verify 的方式验证（省略部分不重要的输出）：

```bash
% spin -a dining-2.pml
% gcc -DSAFETY -o pan pan.c
% ./pan

	+ Partial Order Reduction

Full statespace search for:
	never claim         	- (none specified)
	assertion violations	+
	cycle checks       	- (disabled by -DSAFETY)
	invalid end states	+

State-vector 116 byte, depth reached 111, errors: 0
      138 states, stored
      189 states, matched
      327 transitions (= stored+matched)
        0 atomic steps
hash conflicts:         0 (resolved)
```

（3）spin 提供了对于 LTL 的支持，通过关键字 `ltl` 实现：

```
bool g_forks_init = false;
int g_forks[N_PHIL];

ltl no_reuse0 { [] (g_forks_init ->
g_forks[0] <= 1 && g_forks[1] <= 1 && g_forks[2] <= 1 && g_forks[3] <= 1
) }
```
`g_forks` 初始化完成之后，所有的元素（使用叉子的人数）应该 $\le 1$。可以参见 `dining-3.pml` 获得实现细节。

---

# Part 2: Needham-Schroeder protocol verification

（1）代码参见 `ns-2.pml`。

（2）使用 `ltl` 检查 “*eventually we reach a state where both statusA and statusB are ok*”：

```c
ltl {
	<> (statusA == ok && statusB == ok)
}
```
（3）有这种可能：

```bash
  2:	proc  2 (Intruder:1) ns-3.pml:128 (state 8)	[msg = msg1]
  4:	proc  2 (Intruder:1) ns-3.pml:134 (state 14)	[recpt = agentB]
  6:	proc  2 (Intruder:1) ns-3.pml:137 (state 17)	[data.key = intercepted.key]
  6:	proc  2 (Intruder:1) ns-3.pml:138 (state 18)	[data.content1 = intercepted.content1]
  6:	proc  2 (Intruder:1) ns-3.pml:139 (state 19)	[data.content2 = intercepted.content2]
  8:	proc  2 (Intruder:1) ns-3.pml:153 (state 34)	[network!msg,recpt,data.key,data.content1,data.content2]
  9:	proc  1 (Bob:1) ns-3.pml:88 (state 1)	[network?msg1,agentB,received.key,received.content1,received.content2]
 11:	proc  2 (Intruder:1) ns-3.pml:128 (state 8)	[msg = msg1]
 13:	proc  2 (Intruder:1) ns-3.pml:133 (state 13)	[recpt = agentA]
 15:	proc  2 (Intruder:1) ns-3.pml:137 (state 17)	[data.key = intercepted.key]
 15:	proc  2 (Intruder:1) ns-3.pml:138 (state 18)	[data.content1 = intercepted.content1]
 15:	proc  2 (Intruder:1) ns-3.pml:139 (state 19)	[data.content2 = intercepted.content2]
 17:	proc  0 (Alice:1) ns-3.pml:30 (state 1)	[partnerA = agentB]
 19:	proc  0 (Alice:1) ns-3.pml:31 (state 2)	[pkey = keyB]
 19:	proc  0 (Alice:1) ns-3.pml:35 (state 3)	[messageAB.key = pkey]
 19:	proc  0 (Alice:1) ns-3.pml:36 (state 4)	[messageAB.content1 = agentA]
 19:	proc  0 (Alice:1) ns-3.pml:37 (state 5)	[messageAB.content2 = nonceA]
  <<<<<START OF CYCLE>>>>>
spin: trail ends after 21 steps
#processes: 3
		partnerA = agentB
		partnerB = 0
		statusA = err
		statusB = err
 21:	proc  2 (Intruder:1) ns-3.pml:153 (state 34)
 21:	proc  1 (Bob:1) ns-3.pml:89 (state 2)
 21:	proc  0 (Alice:1) ns-3.pml:41 (state 6)
 21:	proc  - (ltl_0:1) _spin_nvr.tmp:3 (state 3)
```
简单说来，就是：

 - Intruder 发送消息被 Bob 接受，但是 Bob 由于密钥校验而阻塞；
 - Intruder 再次尝试发送消息，无人接收，阻塞；
 - Alice 发送消息，无人接收，阻塞；

（4）很容易拓展：

```bash
  if
    :: partnerA = agentB;
       pkey     = keyB; 
    :: partnerA = agentI;
       pkey     = keyI;
  fi
```
（5）拦截消息，如果加密密钥为 `intruder` 的密钥则可以窃取 `nonce`：

```
do
:: network ? (msg, partner, data) ->
	if
	:: data.key == keyI && data.content1 == nonceA ->
		knows_nonceA = true;
	:: data.key == keyI && data.content1 == nonceB ->
		knows_nonceB = true;
	:: data.key == keyI && data.content2 == nonceA ->
		knows_nonceA = true;
	:: data.key == keyI && data.content2 == nonceB ->
		knows_nonceB = true;
```

（6）对于 `intruder` 的行为进行了一些拓展，现在 `intruder` 学会伪造更多内容（细节参考 `ns-6.pml`）。为了对于三个假设进行验证，分别提出如下三个 `ltl`：

```c
ltl ltl1 {
	[] (statusA == ok && statusB == ok -> partnerA == agentB && partnerB == agentA)
}

ltl ltl2 {
	[] (statusA == ok && partnerA == agentB -> !knows_nonceA)
}

ltl ltl3 {
	[] (statusB == ok && partnerB == agentA -> !knows_nonceB)
}
```

测试发现，`ltl1` 和 `ltl3` 失败。通过检查失败路径，发现这样一种情况：
> A 和 I 通信（`nonceA` 被拦截），I 将 A 的数据报转发至 B，B 返回 B 加密的 `nonceB`，I 将其返回给 A，A 再返回 `nonceB`（`nonceB` 被拦截）。

过程中，A、B 均完成通信，但是 A、B 并未通信，而 `nonceA` 和 `nonceB` 被拦截。所以，`ltl1` 和 `ltl3` 验证失败。
（7）现在 A 会通过 `msg2` 检查通信对象，不再受到欺骗。当 I 尝试转发 B 的报文给 A，A 通过检查 `content3 == partnerA` 发现问题（实现细节参考 `ns-7.pml`）：

```
(data.key == keyA) && (data.content1 == nonceA) && (data.content3 == partnerA);
```