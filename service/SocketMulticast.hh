#ifndef SOCKET_MULTICAST_HH
#define SOCKET_MULTICAST_HH

#include <string>

namespace smack
{

#define SL_SOCK_DEFAULT						0
#define SL_SOCK_SEND						1
#define SL_SOCK_RECV						2
#define SL_SOCK_ERROR						3

///socket文件描述符缺省值
#define MY_SOCKET_DEFAULT					-1
///socket错误信息
#define MY_SOCKET_ERROR						-1	
///最大的接收缓冲区最
#define	RCV_BUF_SIZE						65535
///服务器端最大的支持的客户端的连接数
#define MAX_SOCKET_CONNECT					1024



///-----------------------------------------------------------------------------
///回调参数事件
///-----------------------------------------------------------------------------
enum SOCKET_EVENT
{
  EVENT_CONNECT,				//连接成功事件
  EVENT_REMOTE_DISCONNECT,	//联接端断开事件
  EVENT_LOCALE_DISCONNECT,	//主动断开事件
  EVENT_NETWORK_ERROR,		//网络错误
  EVENT_RECEIVE,				//数据接收事件
  EVENT_SEND,					//数据发送结束事件
  EVENT_RECEIVE_BUFF_FULL,	//接收缓冲区满
  EVENT_UNKNOW,				//未定义状态
};

class SocketEvent
{
public:
  virtual ~SocketEvent() {}
  /// \brief 接收到组播数据的回詷事件
  virtual void on_receive_message(int id, const char* buff, unsigned int len) = 0;
};


class SocketMulticast
{
public:
  SocketMulticast();
  
  virtual ~SocketMulticast();
  
  /// \brief 组播实例初始化
  bool sock_init(const std::string& remote_ip, unsigned short remote_port,
                 const std::string& local_ip,
                 int id, SocketEvent* ptr_event);
  
  /// \brief 组播实例关闭
  bool sock_close();

protected:
  //----------------------------------------------------------------------------
  //保护类成员函数
  //----------------------------------------------------------------------------

  /// \brief 组播数收发信号的线程函数(linux 版)
  static void* socket_server_event_thread(void* ptr_param);			

  /// \brief 组播数收发信号的处理函数
  void* on_socket_server_event_thread();

  /// \brief 启动组播信号处理线程
  bool start_server_event_thread();										
  /// \brief 停止组播信号处理线程
  bool stop_server_event_thread();	
	
  /// \brief 向客户报告的回调事件
  bool report_user(SOCKET_EVENT eventType, int id, const char *buff, unsigned int size);
  /// \brief 日志记录接口
  void log_msg(const std::string& msg);

protected:
  SocketEvent*			m_event;				///< 回调接口
  bool				m_thrade_quit_flag;		///< 信号检测线程退出标志		

  std::string			m_remote_ip;			///< 组播IP
  unsigned short		m_remote_port;			///< 组播端口
  std::string			m_local_ip;				///< 本地IP
  int				m_id;					///< 连接编号
  int				m_sock;					///< 套接口
};

}


#endif




