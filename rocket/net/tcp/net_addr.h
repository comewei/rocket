#ifndef ROCKET_NET_TCP_NET_ADDR_H
#define ROCKET_NET_TCP_NET_ADDR_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <memory>

namespace rocket {

class NetAddr {
 public:
  typedef std::shared_ptr<NetAddr> s_ptr;

  virtual sockaddr* getSockAddr() = 0;

  virtual socklen_t getSockLen() = 0;

  virtual int getFamily() = 0;

  virtual std::string toString() = 0;

  virtual bool checkValid() = 0;

};


class IPNetAddr : public NetAddr {

 public:
  static bool CheckValid(const std::string& addr);

 public:
  
  IPNetAddr(const std::string& ip, uint16_t port);
  
  IPNetAddr(const std::string& addr);

  IPNetAddr(sockaddr_in addr);

  // 返回封装后的sockaddr
  sockaddr* getSockAddr();

  // 得到m_addrs的总长度
  socklen_t getSockLen();

  // 这里得到ip的地址簇 比如AF_NET表示IPv4
  int getFamily();

  // 返回ip地址及其端口
  std::string toString();

  // 判断ip是否合理
  bool checkValid();
 
 private:
  std::string m_ip;
  uint16_t m_port {0};

  // family + ip + port
  sockaddr_in m_addr;

};

}

#endif
