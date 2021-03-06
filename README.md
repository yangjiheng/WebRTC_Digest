# WebRTC Digest

[WebRTC](https://webrtc.org/)是一个极其宏大的工程，其中代码与逻辑实现都非常优雅，算得上一个代码宝藏库。W3C和IETF最近已经正式把WebRTC接受为一个[新标准](https://www.w3.org/TR/webrtc/)。如果你深挖WebRTC的代码内容，不仅可以学到完整的媒体数据的处理、压缩、传输算法实现（有些应用场景下还包括通用数据的传输实现），而且你还可以看到非常多高水平的C++代码，这些实践也可以很轻松的迁移到其他的项目中，发挥巨大的作用。

WebRTC的代码在近些年相比前些年已经变化非常大了，项目非常活跃，值得重新深读一下。在这个实验项目中，我们将尝试把我们对WebRTC的理解按它的代码结构进行梳理和理解总结。同时也期望把一些粗浅的认知和这里面的历史都尽可能的挖掘出来，希望这也能帮助其他想从这个史诗级项目中获得能量的人们。

我们把WebRTC里的一些主要模块进行了单独剥离，这样一方面方便对单独的模块进行理解和分析，另一方面，如果在其他的项目中需要引用个别模块，可以直接引用一个子项目，它们都是可以单独编译运行的，就会比较方便。如果你觉得这样做有价值，可以跟你们一起补充对它的理解。

  * api
    * [scoped_refptr背后的故事](api/scoped_refptr/README.md)
  * rtc_base
    * [thread_annotations的来源](rtc_base/thread_annotation/README.md)
    * synchronization
      * [mutex的实现，包括safe_compare，yield的演化](rtc_base/synchronization/mutex/README.md)
