# 线程

## 1.引入思路

###### 进程的两个特性：

- 操作系统 **分配资源** 的独立单位
- 调度的基本单位

将进程资源分配和调度分开，引入**线程**的概念。

也就是说从系统资源分配的角度，进程是最小的独立单元，但从任务执行的调度操控来看待，我们可以划分出一个更小的单元，这个更小的调度单元我们给它命名叫做 **线程**。

## 2.线程基础

### 2.1 线程定义

**线程：** 线程是 **进程中** 可以独立调度执行的**子任务**，一个进程可以包含一个或多个线程，这若干个线程会共享进程所属的系统资源。

1.线程可以理解为是进程中一个独立的运行实体，执行单元或者说执行体。

> 有的地方也把线程定义为 “轻量级的进程”。

2.线程是 CPU 的基本调度单位，也是调度的实体

3.线程可由 系统内核控制，也可以由用户控制。

![单线程示意图](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/thread_single-thread.png?raw=true)

![thread_single-thread](C:\workplace\laravel\OperatingSystem\assets\thread_single-thread.png)

![多线程示意图](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/thread_multi-thread.png?raw=true)

![thread_multi-thread](C:\workplace\laravel\OperatingSystem\assets\thread_multi-thread.png)

### 2.2 线程组成

1.线程的基本控制单元成为 TCB（Thread-Control-Block，线程控制块），和前面讲到的进程 PCB 类似，里面会包含程序计数器，寄存器和维护的一组内部栈

2.线程是任务调度执行的基本单元，但线程不 **占有** 系统资源，它只使用所在进程内的内存和其他系统资源。

3.但线程不运行时，会保存其切换退出时的上下文。

### 2.3 线程状态

线程分为四种状态：

- 创建状态：创建一个新的线程或者由一个线程创建另一个线程。
- 阻塞状态：线程阻塞，处理器切换去调度其他已就绪的线程。
- 唤醒状态
- 完成状态：执行完成后，释放占用的寄存器上下文和栈空间。

### 2.4 线程模式

使用线程的方式可以分为单线程，多线程。所以使用时会有这几种情况：

- 单进程单线程。
- 单进程多线程
- 多进程，每个进程含一个线程
- 多进程，每个进程含多个线程。

![示意图](https://github.com/OneCodeMonkey/OperatingSystem/blob/master/assets/thread-using-mode.png?raw=true)

![thread-using-mode](C:\workplace\laravel\OperatingSystem\assets\thread-using-mode.png)

### 2.5 引入线程机制的好处

###### 1.减少资源使用的开销：

- 创建一个进程，在资源分配的角度来讲，是一种很昂贵的多任务工作方式；
- 同一进程内的多个线程可以共享进程占有的地址空间和内存数据，从资源利用率上大大提高。
- 创建一个线程所花费的时间，要远小于创建一个进程所花费的时间。
- 线程间切换所需的时间，远小于进程间切换的时间。

###### 2.减少通信上的开销：

- 进程间要想通信，只能借助外部管道，内核自带的消息队列或者共享内存区等外部手段来通讯，这样的方式费时而且不容易时间。
- 但线程之间本身就可以共享地址空间和内存数据或文件，线程间之间的通信传递数据可以直接进行，无需调用内核。这样通信的开销大大降低。

## 3.线程的实现机制

### 3.1 用户级线程

需要：系统支持 **用户线程库**

举例：

- POSIX Pthreads
- Mach C-threads
- Solaris threads

###### 优点：

- 线程切换不调用内核，
- 调度算法是应用程序特定的算法
- 可以运行在任何操作系统上（只要有线程库）

###### 缺点：

- 一旦发生进程阻塞，那么进程中所有线程都将被阻塞
- 进程内的不同线程不能同时运行于不同的处理器上。

### 3.2 内核级线程

需要：内核级支持

举例：

- Windows 95/98/NT
- Solaris
- UNIX

###### 优点：

- 对多核心处理器，可同时运行并调度同一进程的多个线程
- 阻塞是在线程一级发生的，而不是进程级

###### 缺点：

- 同一进程内，线程的切换需要调用内核，切换速度会下降。

### 3.3 两者结合的实现方法（摘录的教材描述）

###### 多对一模型：

![thread-many-to-one](C:\workplace\laravel\OperatingSystem\assets\thread-many-to-one.png)

###### 一对一模型：

举例：windows 95/98/NT

![thread-one-to-one](C:\workplace\laravel\OperatingSystem\assets\thread-one-to-one.png)

###### 多对多模型：

![thread-many-to-many](C:\workplace\laravel\OperatingSystem\assets\thread-many-to-many.png)

## 4.线程设计实现举例

![Thread-solaris2-threads-implementation](C:\workplace\laravel\OperatingSystem\assets\Thread-solaris2-threads-implementation.png)