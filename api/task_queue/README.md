# Task Queue

## WebRTC中的Event

RTC中的Event实现与之前的scoped_refptr一样，也是随着libjingle一起被合并到WebRTC代码中的，而且后续一直在用它进行阻塞事件机制的方式留存着。

其中有一个[issue 10531](https://bugs.chromium.org/p/webrtc/issues/detail?id=10531)需要关注，在WebRTC的一个判定中，将wait时间为kForever时，超过3秒的Event阻塞认定为死锁的情况是有问题的：

>The "Probable deadlock" warning that was introduced recently (and which triggers whenever Event::Wait(kForever) end up waiting more than three seconds) frequently triggers when there is no actual deadlock.

比如在等待其他的端送消息时，是需要等kForever的，但是3000ms不收到消息是正常的，在这种机制下会被误判为死锁，因此后面把Wait方法加入了一个warn_after_ms参数，用于专门指定需要多长时间warn可能死锁了，保持了它的严谨性。

## Demo Code

* Event: [event.h](rtc_base/event.h), [event.cc](rtc_base/event.cc)
* Demo: [main.cc](app/main.cc)

## 编译方法：

* 编译absl至根目录下的third_party子目录下
* 安装gn, ninja
* 执行编译脚本[build_app.sh](build_app.sh)
* 执行运行脚本[run_app.sh](run_app.sh)

