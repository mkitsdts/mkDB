---
title: Log in mkDB
date: 2024-10-29 11:18:07
tags: mkDB
author: mkitsdts
---
要保障数据库的数据安全，及时排查错误是很有必要的。这要求数据库拥有一个在复杂环境下安全输出的日志库。因为日志库可以独立于数据库，且数据库开发过程会经常调用日志库，所以数据库的编写工作可以从日志库开始。

## 需求分析
无论开发什么功能，在编码之前，必须先理清核心需求，也就是分析后面会在什么样的场景下使用日志库，对日志库有什么样的要求，分析清楚后再设计框架。

#### 需求一：打印日志
最核心的功能。打印的格式要有**日志等级、日期、具体时间、出错原因**，最少要有这几点才能是一个合格的日志，如果能加上出错的代码位置那就最好不过了。

#### 需求二：线程安全
可能同时有多个线程写日志，因此数据库需要考虑如何在多线程条件下的不丢失数据地输出日志。

#### 需求三：日志读档
考虑到程序可能会出现在修改数据时突然崩溃的情况，因此日志存档也是日志系统很重要的一部分，要尽可能实现在程序崩溃的情况下，能够根据日志重新获取正确结果。

#### 需求四：指定位置
因为程序可能在各种不同的位置，希望程序能够支持指定位置输出日志。


## 需求实现

#### 打印日志
核心功能设计接口必须得简洁，好用，不能有太多参数，也不能在调用之前还要创建一个对象，所以选择通过宏定义提供接口。
日志打印分为以下四个级别：
* [DEBUG] 调试时输出的信息，通常只用于调试阶段，此级别的日志内容只包含用户提交的内容以及时间而不包含函数信息，内容只通过打印台输出。

* [INFO] 程序正常情况下的输出反馈，用于获取程序运行情况，此级别的日志内容只包含用户提交的内容以及时间而不包含函数信息，内容通过打印台输出并进入二级日志缓存区，待程序结束后再统一输出至文件。

* [WARNING] 程序运行至在正常情况不会进入的分支时，建议打印该级别的日志。该级别的日志会通过打印台输出，包含函数信息，具体时间，并进入一级日志缓存区，在达到一定数量后开辟线程输出至文件。

* [ERROR] 程序运行时进入没有预测的分支，例如空指针，指针越界等情况，建议打印该级别日志。该级别日志会通过打印台输出，包含函数信息，具体时间，不进入缓存区直接输出至文件。

#### 线程安全
为保证线程安全，采用了如下技术：
* 互斥锁 日志加入打印队列时会启动锁，此时如有其他线程打印日志会将打印线程挂起，等待锁释放再执行

* 双缓冲 日志缓存区采取了两个队列，在一个队列满载后直接与一个空队列互换，开辟一个线程并将信息打印至文件，互换后得到的空队列又可以继续接收日志，如此可近似实现无缝衔接

#### 日志读档
考虑到程序在写入数据库途中崩溃的情况，采取了一个先把信息输出至日志，然后再修改磁盘文件的策略，这样可以实现程序在写入数据崩溃时的恢复。
具体实现是在写入之前先把数据格式输出至日志，并在尾部追加unfinished字样，在成功写入后，删除unfinished字样。程序在下次启动时，一步一步读取，如果遇到unfinished标记，那么将数据更新至数据库

#### 指定位置
这个需求只需要给个地方输入地址即可。

## 代码实现

大话说完了，就等上手写代码了。