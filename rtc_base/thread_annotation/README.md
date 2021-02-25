# Thread Annotations

## 如何引入的Thread Annotations

最早在2013年12月20日由Andrew从gperftools中集成提交至WebRTC中（[Code Review](https://webrtc-codereview.appspot.com/6209004/#ps1))，原始Author为Le-Chun Wu。通过本机制，gcc以及clang提供的一些编译warning，可以发现很多潜在的错误，并成功用这些Annotation抓到了一些多线程bug。

clang对于Thread Safety Annotation的规范可以参考：[Clang LLVM Document](https://clang.llvm.org/docs/ThreadSafetyAnalysis.html)，其中宏的定义也与thread_annotations.h的定义可以一一对应。

在启用-Wthread-safety进行编译（gn的话，在BUILDCONFIG.gn里启用gn:warnings，将对annotation实施的准确度进行检查，并将不遵守规范的代码使用方式报错。Thread-Safety Annotation是编译级别的，不对程序运行增加附加的运行开销。

## 为什么使用Thread Annotations

Google有一篇写的很好的[Slides](https://llvm.org/devmtg/2011-11/Hutchins_ThreadSafety.pdf)，把为什么使用Annotation写的很明白。

核心的bug demo是：

```C++
void bug(Key* K) {
    CacheMutex.lock();
    ScopedLookup lookupVal(K);
    doSomethingComplicated(lookupVal.getValue());
    CacheMutex.unlock();
    // OOPS!
    // 这里lookupVal还未被释放，但是CacheMutex已失去了保护的能力
};
```

所以fix为

```C++
void bug(Key* K) {
    CacheMutex.lock();
    {
        ScopedLookup lookupVal(K);
        doSomethingComplicated(lookupVal.getValue());
        // force destructor to be called here...
        // 在Scope尾巴上确保lookupVal已被释放
    }
    CacheMutex.unlock();
};
```

这类bug很隐匿，code review也很难找出来，运行时bug也不是必现（取决于race的结果）。使用Annotation之后，则上面bug会被报warning，及时解决则会避免此类bug发生。


## Demo Code

* thread_annotations的实现 [thread_annotations.h](rtc_base/thread_annotations.h)
* Demo: [main.cc](app/main.cc)

在Demo code中，将m_pFooPtr标记为：

```C++
RTC_GUARDED_BY(mutex_)
```

则使用m_pFooPtr指针的时候，函数必须标记需要Lock mutex_：

```C++
void RtcAPI::testThreadAnnotations() RTC_EXCLUSIVE_LOCKS_REQUIRED(mutex_)
```

否则编译不通过，则可以提前发现一些线程不安全问题。

## 编译方法：

* 安装gn, ninja
* 执行编译脚本[build_app.sh](build_app.sh)
* 执行运行脚本[run_app.sh](run_app.sh)

