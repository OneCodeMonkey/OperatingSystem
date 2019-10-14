# 操作系统原理

分五个部分分开讲：

1.进程

2.线程

3.CPU的任务调度

4.进程的同步

5.死锁。



## 进程

### 1.进程概念

### 2.进程的调度

### 3.进程控制

### 4.进程协作

### 5.进程通信



### 1.进程概念

#### 1.1 进程定义

进程是程序的具体执行。进程执行必须按照一定的顺序进行。

进程由四部分组成：

- PCB
- 程序体
- 数据区
- 进程栈

![进程的组成](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/%E8%BF%9B%E7%A8%8B%E7%BB%84%E6%88%90.png?raw=true)

进程有几个特征：

- 并发性
- 动态性
- 独立性
- 交互性
- 异步性
- 结构性

`进程`与 `程序` 的区别：

- 进程包括`程序` 和 `数据`两部分
- 进程有生命周期，有创建有销毁，是动态的概念。而`程序`是一个静态的概念，`程序`是相对长久的存在。
- 进程能创建其他进程，而程序不能去创建其他程序
- 进程能描述并发，而程序不能

#### 1.2 进程的状态

- 新建状态
- 运行状态
- 等待状态
- 就续状态
- 终止状态

![进程状态切换2.png](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/%E8%BF%9B%E7%A8%8B%E7%9A%84%E7%8A%B6%E6%80%81%E5%88%87%E6%8D%A22.png?raw=true)



###### 进程状态切换图

![进程状态切换.png](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/%E8%BF%9B%E7%A8%8B%E7%9A%84%E7%8A%B6%E6%80%81%E5%88%87%E6%8D%A2.png?raw=true)



#### 1.3 进程控制块 （PCB, Process Control Block）

- Process state
  Program counter
  CPU registers
  CPU scheduling information
  Memory-management information
  Accounting information
  I/O status information

![PCB组成.png](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/PCB%E7%BB%84%E6%88%90.png?raw=true)



![进程运行与PCB的交互.png](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/%E8%BF%9B%E7%A8%8B%E8%BF%90%E8%A1%8C%E4%B8%8EPCB%E7%9A%84%E4%BA%A4%E4%BA%92.png?raw=true)



###### PCB表

系统会把所有 PCB 记录组织存放在内存的固定区域，这个部分就是系统的 PCB 表。

分为两部分：链表， 索引表

PCB 表的大小决定了系统中最多可以同时存在的进程的个数。这个值反映了系统的**并发度**



![PCB链表队列.png](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/PCB%E8%A1%A8%E7%9A%84%E9%93%BE%E8%A1%A8%E9%98%9F%E5%88%97.png?raw=true)



![PCB索引表示意.png](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/PCB%E8%A1%A8%E7%9A%84%E7%B4%A2%E5%BC%95%E8%A1%A8.png?raw=true)

###### 进程队列

![进程队列示意图.png](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/%E8%BF%9B%E7%A8%8B%E9%98%9F%E5%88%97%E7%A4%BA%E6%84%8F%E5%9B%BE.png?raw=true)



- 就续队列是没有优先级的，先进先出
- 当事件 n 发生时，对应的队列移进就续队列。

### 2.进程的调度

#### 2.1 调度的类型

- 高级调度

也称为作业调度或宏观调度

高级调度的时间尺度通常是分钟，小时或天。

- 中级调度

涉及进程在内外存间的交换

从存储器资源管理的角度来看，把进程部分全部换出到外存上，可为当前运行进程的执行提供所需内存空间，将当前进程所需部分换入到内存。指令和数据必须在内存里才能被处理机直接访问。

- 低级调度

也称微观调度

从处理机资源分配角度来看，处理机需要经常选择就续进程或线程进入运行状态

低级调度的时间尺度通常都是毫秒级的

由于低级调度算法使用和频繁，要求在实现上尽可能高效， 下面会简单介绍下进程的微观调度的几种算法策略。

#### 2.2 调度的模式

- 非剥夺方式
  - 简单，
  - 开销小
  - 实时性差
- 剥夺方式
  - 优先级原则：
  - 时间片原则：

#### 2.3 调度算法。

前面说到，进程的执行一定是有顺序的。cpu 会指定当前队列的进程里哪一个先执行，哪一个靠后。这就涉及到调度。

调度的衡量指标有这么几种：

- CPU利用率（谁能让CPU利用率更大）
- 吞吐量（单位时间内能处理完的数量）
- 周转时间（整个执行完一个进程所需要花的时间）（注意，如果发生了抢占，还是会以开头到结尾的时间差作为周转时间，所以发生抢占时周转时间会变长）
- 等待时间（进程在 `就绪队列`里需要等待的时间）
- 响应时间（在分时操作系统下，一个进程从被装载到 cpu，到产生第一次响应。是第一次响应，不是第一次的成功返回）

根据这几种不同的衡量指标，cpu 的调度有五种对应的最优原则：

- 最大 CPU 利用率
- 最大吞吐量
- 最小周转时间
- 最小等待时间
- 最小响应时间

CPU中的进程的调度算法，主要有下面六种

- 先到先服务调度（First Common First Serve, FCFS）
- 最短作业优先调度（Shortes-Job-First, SJR）
- 优先级调度（Priority Scheduling）
- 轮转法调度（Round Robin， RR）
- 多级队列调度（multilevel queue-scheduling）
- 多级反馈队列调度（multilevel feedback queue scheduling）

##### 2.3.1 FCFS 先到先服务

看一组例子：

![先到先服务](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/FCFS_1.png?raw=true)



![先到先服务](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/FCFS_2.png?raw=true)



##### 2.3.2 SJF 最短作业优先调度

每次先执行所有就绪队列中，所需执行时间最短的进程。

这是一种贪心策略。同时最终从平均等待时间这个角度来衡量，SJF 算法的表现也是最优的。

分为抢占式和非抢占式，抢占式又叫 **最短剩余时间优先作业调度**

看一组例子：

![SJF 非抢占式](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/SJF_1.png?raw=true)



![SJF 抢占式](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/SJF_2%E6%8A%A2%E5%8D%A0%E5%BC%8F.png?raw=true)



##### 2.3.3 优先级调度

思想: 假设当前的就绪队列的每一个进程都被赋予了一个优先级数字（优先权），那么 cpu 调度程序（dispatcher）每次决定取哪个进程来执行的时候，都优先选择优先级数字最小的进程来执行（字越小，优先权越大）。

SJF 就是一种特殊的优先权调度（根据执行时间短，长来排优先级高，低）

具体操作系统是怎么分配优先级的策略较为复杂，后面有时间再补充

优先级调度会带来两个问题：

- 饥饿：有的进程一直处在优先级低的地方，一直得不到执行。
- 倒置：有的进程先到达队列，但却很晚才执行；有的进程是晚到的，却早于最早到的进程而执行。

具体怎么解决这里不作深入讲，后面再补充。

##### 2.3.4 RR 轮转法调度

思想：把 cpu 的执行，按照一个间隔分为一个时间片。然后为当前待执行的进程，每一个都分配一个时间片，轮换着执行。轮换的时候，进程执行的先后仍然按 FIFO 先到先执行的顺序。

看这个例子：

![RR 轮转法调度](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/RR-rotate.png?raw=true)



##### 2.3.5 多级队列调度

各个级别队列用各自的调度算法，外部来决定进程进入哪个优先级的队列。

与下面的多级反馈队列调度不同的是，进程在分配 CPU 执行以后不能再继续在不同优先级队列之间跳动。

![多级队列调度](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/multi-level-feedback-dispatch.png?raw=true)



##### 2.3.6 多级反馈队列调度

进程可以在不同队列间移动，根据不同级队列的反馈来切换进程该进入哪个队列去执行。

多级反馈队列需要这几个部分来完成：

- 队列的数量
- 不同队列各自的调度算法
- 用来确定进程何时可以升级到较高优先级队列的方法
- 用来确定进程何时可以降级到较低优先级队列的方法
- 用来确定进程在需要执行时，具体要进哪个队列的方法

示意图：

![多级反馈队列调度](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/multi-level-feedback-dispatch-2.png?raw=true)



### 3.进程控制

### 4.进程协作

### 5.进程通信



