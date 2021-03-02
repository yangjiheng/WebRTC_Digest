# Mutex的周边实现

## WebRTC的yield方法

这是[2020年6月2日](https://bugs.chromium.org/p/webrtc/issues/detail?id=11634)才提出来的优化，之前所有平台的yield方法都是Sleep(0)，但各平台都有各平台独有的方法，而且相比Sleep都有一定的优势，其实这个细节很多时候还是会有不少影响的。比如：

Windows平台上，有SwitchToThread()的API，它会比Sleep更加智能在两个点上：

  * SwitchToThread只会限制当前线程所在的处理器，OS也严格不会切换到另外一个处理器。但Sleep不是
  * SwitchToThread只会等待当前线程调度的上下文，但是Sleep等待条件有多个，也有可能会等待多个线程。

所以在实际执行环境中，Sleep会yield OS的，也会yield到一个时间片，所以Sleep会更有可能把当前的core从100%使用率瞬间拉到0%，但是SwitchToThread则不会。

POSIX环境里有sched_yield()方法，它也会比Sleep更智能在：

* sched_yield会被系统立刻调度到其他的core上，但是如果sleep超过1的话，core会至少sleep那么久时间才会响应，这样sched_yield会更敏锐一些。

在其他平台上，nanosleep会比Sleep更好：

* 精度高
* POSIX.1上，nanosleep不会与信号有交互，所以恢复一个被信号中断的sleep任务时会更容易。

目前应该还在继续演化中，windows端的实现仍然使用Sleep，不久的将来，应该会被SwitchToThread代替。

目前的代码[yield.cc](rtc_base/synchronization/yield.cc)

## WebRTC中的Safe Compare

使用自有实现的[type_traits.h](rtc_base/type_traits.h)，来进行各符号数据的安全对比方法，这样节省了非常多的数据转换过程。

## WebRTC的Mutex

WebRTC的mutex最早是CriticalSection跟Pthread Mutex的混合版本，不过都是用的reentrant mutex（entrant mutex是指同线程多次获得锁是可以的，但不同线程获得锁是不可以的，non-reentrant mutex是同线程不同线程都不可以重复获得锁，除非锁处于空闲状态）。这个方案在2020年6月份被认为有瑕疵的，升级为现在的混合版本：

* 如果启用了abseil的mutex，则使用absl::Mutex
* 如果是Windows环境的话，使用Critical Section（仍不安全，因为Critical Section是reentrant mutex，估计以后会往abseil::Mutex上转）
* 如果是POSIX环境的话，使用pthread，但是不启用recursive lock
* 其他环境不支持

关于C++代码里使用reentrant mutex是不是个好主意，一直是个极具争议的问题。它合理吗？合理的。同一个线程为什么不能持续访问同一个锁保护的内容。这个从本质上讲没问题。但是reentrant mutex可控吗？未必，因为没办法工程师视角和工程视角是完全不同的，太容易出bug了，维护成本高，性价比低，而且这些bug往往也是代码review和设计时无法完全避免的，并且大幅度提升代码间依赖性。有一个比较经典的论述可以参考Stephen Cleary的[blog](https://blog.stephencleary.com/2013/04/recursive-re-entrant-locks.html)，合情合理。

在去掉pthread的recursive mutex后，webrtc的test case出现了比较多的deadlock，也是在复杂线程模型下，mutex保护容易出问题的印证。所以在把握没那么大的情况下，尽可能多使用non-reentrant mutex是个明智的选择，会有效降低代码的风险。

## Demo Code

* yield的实现 [yield.cc](rtc_base/synchronization/yield.cc)
* safe_compare的实现 [safe_compare.h](rtc_base/numerics/safe_compare.h)
* mutex的实现 [mutex.h](rtc_base/synchronization/mutex.h), [mutex.cc](rtc_base/synchronization/mutex.cc)
* Demo: [main.cc](app/main.cc)

## 编译方法：

* 安装gn, ninja
* 执行编译脚本[build_app.sh](build_app.sh)
* 执行运行脚本[run_app.sh](run_app.sh)

