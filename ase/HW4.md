# 高级软件工程 HW4

---

# P1: Basics
代码实现请参见代码 `p1.pml`。

# P2：Rendevous
有可能，虽然 `chan` 的读写操作不能被 interleave，但是有可能在读写开始之前循环就结束了。代码实现参见 `p2.pml`。代码通过 `assert` 检查是否读取 chan：
```c
assert(value == 100);
```

进行 verify 的结果是：
```bash
spin -a p2.pml
gcc -DSAFETY -o pan pan.c
./pan
```
    pan:1: assertion violated (value==100) (at depth 12)
    pan: wrote p2.pml.trail

跟踪失败例子：
```bash
spin -p -l -t p2.pml
```
    using statement merging
    Starting P with pid 1
      1:	proc  0 (:init::1) p2.pml:31 (state 1)	[(run P())]
      2:	proc  1 (P:1) p2.pml:18 (state 3)	[else]
      3:	proc  1 (P:1) p2.pml:19 (state 4)	[i = (i+1)]
    		P(1):i = 1
      4:	proc  1 (P:1) p2.pml:18 (state 3)	[else]
      5:	proc  1 (P:1) p2.pml:19 (state 4)	[i = (i+1)]
    		P(1):i = 2
      6:	proc  1 (P:1) p2.pml:18 (state 3)	[else]
      7:	proc  1 (P:1) p2.pml:19 (state 4)	[i = (i+1)]
    		P(1):i = 3
      8:	proc  1 (P:1) p2.pml:18 (state 3)	[else]
      9:	proc  1 (P:1) p2.pml:19 (state 4)	[i = (i+1)]
    		P(1):i = 4
     10:	proc  1 (P:1) p2.pml:18 (state 3)	[else]
     11:	proc  1 (P:1) p2.pml:19 (state 4)	[i = (i+1)]
    		P(1):i = 5
     12:	proc  1 (P:1) p2.pml:16 (state 1)	[((i>=5))]
    spin: p2.pml:26, Error: assertion violated
    spin: text of failed assertion: assert((value==100))
     13:	proc  1 (P:1) p2.pml:26 (state 12)	[assert((value==100))]
    spin: trail ends after 13 steps
    #processes: 2
    		value = 0
     13:	proc  1 (P:1) p2.pml:27 (state 13) <valid end state>
     13:	proc  0 (:init::1) p2.pml:35 (state 3) <valid end state>
    2 processes created

确实如同估计，循环跳过了读取 `chan`。

# P3: Buffered
实现参见 `p3.pml`。

# P4: Office Printer Revisited
利用 rendezvous chan 阻塞的特性，实现类似锁的互斥。
```c
if
:: usable ? true ->
```
只有当一个进程写入完毕之后，通过写入管道，另一个管道才可能解除阻塞。
```c
	usable ! true;
fi
```
实现细节参见 `p4.pml`。

Verify 结果如下：

    Full statespace search for:
    	never claim         	- (none specified)
    	assertion violations	+
    	cycle checks       	- (disabled by -DSAFETY)
    	invalid end states	+

    State-vector 44 byte, depth reached 15, errors: 0
           12 states, stored
            2 states, matched
           14 transitions (= stored+matched)
            1 atomic steps
    hash conflicts:         0 (resolved)
