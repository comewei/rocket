#### 简介 

这个用于梳理rocket中tinyrpc不会的项目，用于记录

> 需要完成的功能
- 每一个类的具体含义 ——> 延伸出整个网络架构是怎么样的
- 运行调通过
- 如何运用日志内容，这里应该是tinyxml的使用，可以一通百通运用到其他项目中去
- 给其他人讲解这个项目的来源
- 结合之前视频上不清晰的


####TCP文件大类

##### net_addr 类


这里的类封装  IP + PORT 变成 sockaddr_in ：
    里面会指明 FAMILLY + IP + PORT，这里toString返回字符串（IP + PORT）


##### tcp_acceptor类

这里的类用于 server端用于创建监听套接字
- setsockopt 用于 创建套接字
- bind 套接字  
- listen 监听



accept 用于server 和 客户端的连接，这里是在三次握手之后


