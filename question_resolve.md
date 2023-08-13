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


##### tcp_buffer类
这个是
![Alt text](imgs/image.png)

##### tcp_connection
记录每一次tcp连接需要进行的操作
输入缓冲区——输出缓冲区（用来更好存储数据）
m_fd_event 这里得到tcp连接对应的fd，用于读写操作 (这里通过fcntl设置NonBlock)

如果在tcpserver上，需要使用epoll监听可读事件，加入EpollEvent

- listenRead()用于监听可读事件，绑定onRead()事件

- listenWrite()用于监控可写事件，绑定onWrite()事件

- execute 执行逻辑处理
  - 在服务器端首先按照tinyPB格式解码，得到解码组vector<AbstractProtocol::s_ptr> message
    - 调用RpcDispatcher的dispatch方法：将解码的信息，将request->response，将调用的方法解析，然后填入到tcp的connection中，service->CallMethod(method, rpc_controller, req_msg, rsp_msg, closure);
      - 处理完毕之后，会调用 ‘reply’ 函数发送给，对处理之后的数据信息进行编码，然后注册listenWrite()函数 （这里问题来了，这个时候数据应该还没有发送到缓冲区，由此还没有被监听吧。如果触动的话，会调用onWrite函数）

- onWrite 函数
  - 如果写入buffer的话，那readIndex 和 WriteIndex应该要随时变化吧，这个变化体现在哪里？
  - 如果全部写入的话，就取消可写事件（这样防止epoll一直出发可写事件，但是实际上不用触发）
  - 这里write关于缓冲区的情况需要仔细考虑，最好输出一片文档

![Alt text](image-1.png)
![Alt text](image-2.png)



##### tcp_client类

Client类
    创建客户端套接字，之后和TcpConnection关联
    errno这里应该是固定的，不需要定义
    如果处于EINPROGRESS的时候，为什么需要监听写套接字，难道这里是wakeup用法
![Alt text](image-3.png)

    调用addTimerEvent 用于保存远程连接作用？？？
    writeMessage readMessage 用来发送message，之后调用done

##### tcp_server类

使用tcp_acceptor建立连接；IOThreadGroup建立IO线程组（给套接字使用）;创建可读事件，并且加入监听
创建监听事件


#### coder







