# WebRTC_Digest

## Introduction

[WebRTC](https://webrtc.org/) is a massive project with extremely elegant implementation details. W3C and IETF recently have officially accepted this as [a new standard](https://www.w3.org/TR/webrtc/), which is an expected outcome years ago. If you dig deep down into WebRTC's code, not only you will be able to learn about processing/compression/transmission technology of media content (in some usecase scenario, generic data content), but you will also see top-tier C++ code which can be applied in various other projects. 

WebRTC's codebase has been evolving drasticlly in past few years, and seems like worth a good re-reading and digest. In this experimental project, we will try to digest our understanding of WebRTC with its own code structure, in spirit of sharing understanding of the implementation. Hopefully helps other people who are also trying to learn from it.

If you are also into this idea, you can join me in this path, and surely I'll be glad to hear from you guys.

## 简介

[WebRTC](https://webrtc.org/)是一个极其宏大的工程，其中代码与逻辑实现都非常优雅，算得上一个代码宝藏库。W3C和IETF最近已经正式把WebRTC接受为一个[新标准](https://www.w3.org/TR/webrtc/), 这也算是多年的期盼如愿以偿了。如果你深挖WebRTC的代码内容，不仅可以学到完整的媒体数据的处理、压缩、传输算法实现（有些应用场景下还包括通用数据的传输实现），而且你还可以看到非常多高水平的C++代码，这些实践也可以很轻松的迁移到其他的项目中，发挥巨大的作用。

WebRTC的代码在近些年相比前些年已经变化非常大了，代码提交非常多，也看起来很值得重新深读一下。在这个实验项目中，我们将尝试把我们对WebRTC的理解按它的代码结构进行梳理和理解总结。同时也期望不只是再读一次，而是可以跟大家分享我们的一些粗浅的认知。希望这也能帮助其他想从这个史诗级项目中获得能量的人们。

如果你们也喜欢这个主意，你也可以选择与我们同行，我们非常期待听到你们的声音。
