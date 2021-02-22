# Scoped Refptr

## 指针及由指针引起的问题有多严重

[Chrome项目中发现70%以上的安全bug全是内存问题](https://www.chromium.org/Home/chromium-security/memory-safety)，所以原则上所有的裸指针（raw pointers）都是被禁止使用的，因此从项目初期，就使用了智能指针规避这类问题（数据是较新的统计，即使使用了所有这些规避措施，问题依然严峻且不好解决，可见目前内存使用问题依然有多困扰这些C++项目）

## Chrome智能指针Guideline

Chrome智能指针部分的Guideline可以参考[这里](https://www.chromium.org/developers/smart-pointer-guidelines)。因为Chrome和WebRTC都是2011年以前开始的项目，C++智能指针基本上要到2015年后才进入C++11标准，所以WebRTC从很早开始，就依赖自己单独实现的智能指针来对抗所有可能的内存问题。基本的原则就是：

>The two common smart pointers in Chromium are std::unique_ptr<> and scoped_refptr<>. The former is used for singly-owned objects, while the latter is used for reference-counted objects (though normally you should avoid these -- see below). If you're familiar with C++11, scoped_refptr<> is similar in intent to std::shared_ptr<>

也就是说在使用独有指针时使用std::unique_ptr，在使用引用计数指针时，使用scoped_refptr（基本上跟C++11的std::shared_ptr一致）。

## 智能指针在WebRTC中的应用历史

从最终的角度看，使用了一个实现的组合，std::unique_ptr和rtc::scoped_refptr。为什么没有使用std::shared_ptr呢？为什么std::unique_ptr没有使用个自定义实现呢？

### 为什么没有自定义一个std::unique_str的类

其实是有的，但被移除了。WebRTC里的智能指针和Chrome里的类似实现的（但Chrome的scoped_refptr后续有些迭代，WebRTC没有更新引入了，但是主框架完全一致，并多年没有更新），最初的时候，在把libjingle合并到WebRTC的时候带进来的。最初还有一个智能指针类型叫：rtc::scoped_ptr，用于不做引用计数的处理独有指针的情况。所以在2016年2月12日开始，由[Karl Wiberg](https://treskal.com/kha)提议：

>rtc::scoped_ptr doesn't really do anything that std::unique_ptr doesn't, so in order to keep things simple, we should replace the former with the latter.

>scoped_ptr is a home-grown type that's very very close to behaving just like unique_ptr. The motivation for the change is basically just that it's better for everyone if we don't use a home-grown type where a standard type will do, since that means there's less maintenance and fewer project-specific things to learn about and keep track of.

因此一个历时三个多月的庞大重构工程开始了，细节大家可以参阅[bug report](https://bugs.chromium.org/p/webrtc/issues/detail?id=5520)，[code review](https://codereview.webrtc.org/1966423002)。

一个Fun Fact，Code Review的CC List会看到很多来自Agora的老熟人们

>CC: webrtc-reviews_webrtc.org, interface-changes_webrtc.org, **video-team_agora.io**, danilchap, yujie_mao (webrtc), **fengyue_agora.io**, **zhuangzesen_agora.io**, Andrew MacDonald, **zhengzhonghou_agora.io**, henrika_webrtc, stefan-webrtc, tterriberry_mozilla.com, **audio-team_agora.io**, qiang.lu, niklas.enbom, **sdk-team_agora.io**, peah-webrtc, minyue-webrtc, mflodman, aluebs-webrtc, bjornv1

类似这样的行业参与，Agora的确不少，这也就能解释为什么在这个阶段声网在RTC方向的确势头强劲，与一线项目接轨开始的早，挖的深。

### 既然scoped_ptr换了，为啥没有把scoped_refptr换成std::shared_ptr

WebRTC团队曾经强调过是不会使用std::shared_ptr的（是的，C++标准库的确也不完美，有很多问题），但是目前还没找到一个确切的不能替换的理由，能想到的可能的原因是：

* 重构性价比太低了，相比scoped_ptr的重构，修改scoped_refptr的测试复杂度和影响大太多，导致没有动力优化
* Chrome早期基于KHTML的老代码还好多，即使优化了，也未必解决多少问题
* scoped_refptr的引用计数实现是自定义的，这样的话，可以做出很多其他的效果，比如如果一个UI元素只能在主线程释放，那使用shared_ptr无法确保做到这点，引起崩溃。scoped_refptr可以使用自定义的引用计数实现来进行一些释放层面的调度。

当然具体原因没找到，也可能还有其他的一些考虑点，项目到这么大，改底层没把握真不好弄。

### 一些后续考虑

虽然考虑了如此多的因素，现在仍然有70%以上的严重bug跟内存问题有关，其实工程师视角看过去，已经不希望通过打补丁的方式解决这个问题了，更希望从根源解决，一次性清理这些问题，所以Firefox使用了Rust解决了大部分这类的问题，但是因为大部分网站遇到Chrome的问题，都会兼容过去，所以也使得Firefox这些努力显得没那么显著。但是的确Google，Mozilla等都在考虑是否使用更深层的解决方案避免这类问题，毕竟浏览器太重要了。

[From Diane Hosfelt](https://hacks.mozilla.org/2019/02/rewriting-a-browser-component-in-rust/)

>Over the course of its lifetime, there have been 69 security bugs in Firefox’s style component. If we’d had a time machine and could have written this component in Rust from the start, 51 (73.9%) of these bugs would not have been possible. While Rust makes it easier to write better code, it’s not foolproof.

[From Chrome](https://www.chromium.org/Home/chromium-security/memory-safety)

> We expect this strategy will boil down to two major strands:
> 
> * Significant changes to the C++ developer experience, with some performance impact. (For instance, no raw pointers, bounds checks, and garbage collection.)
> 
> * An option of a programming language designed for compile-time safety checks with less runtime performance impact — but obviously there is a cost to bridge between C++ and that new language.

要看未来，C++也只能算是不死族了，死不掉，非得用，还糟嫌弃，所以C++人才培养弧线还真的是长。

## Demo Code

* Scoped_refptr的实现：[scoped_refptr.h](api/scoped_refptr.h)
* WebRTC中，一个Ref Counted Base的实现: [ref_counted_base.h](api/ref_counted_base.h)
* WebRTC中，一个Ref Counted Object的实现: [ref_counted_object.h](rtc_base/ref_counted_object.h)
* Demo: [main.cc](app/main.cc)

## 编译方法：

* 编译absl至根目录下的third_party子目录下
* 安装gn, ninja
* 执行编译脚本[build_app.sh](build_app.sh)
* 执行运行脚本[run_app.sh](run_app.sh)

