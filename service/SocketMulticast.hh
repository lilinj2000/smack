#ifndef SOCKET_MULTICAST_HH
#define SOCKET_MULTICAST_HH

#include <string>

namespace smack
{

#define SL_SOCK_DEFAULT						0
#define SL_SOCK_SEND						1
#define SL_SOCK_RECV						2
#define SL_SOCK_ERROR						3

///socket�ļ�������ȱʡֵ
#define MY_SOCKET_DEFAULT					-1
///socket������Ϣ
#define MY_SOCKET_ERROR						-1	
///���Ľ��ջ�������
#define	RCV_BUF_SIZE						65535
///������������֧�ֵĿͻ��˵�������
#define MAX_SOCKET_CONNECT					1024



///-----------------------------------------------------------------------------
///�ص������¼�
///-----------------------------------------------------------------------------
enum SOCKET_EVENT
{
  EVENT_CONNECT,				//���ӳɹ��¼�
  EVENT_REMOTE_DISCONNECT,	//���Ӷ˶Ͽ��¼�
  EVENT_LOCALE_DISCONNECT,	//�����Ͽ��¼�
  EVENT_NETWORK_ERROR,		//�������
  EVENT_RECEIVE,				//���ݽ����¼�
  EVENT_SEND,					//���ݷ��ͽ����¼�
  EVENT_RECEIVE_BUFF_FULL,	//���ջ�������
  EVENT_UNKNOW,				//δ����״̬
};

class SocketEvent
{
public:
  virtual ~SocketEvent() {}
  /// \brief ���յ��鲥���ݵĻ�Ԙ�¼�
  virtual void on_receive_message(int id, const char* buff, unsigned int len) = 0;
};


class SocketMulticast
{
public:
  SocketMulticast();
  
  virtual ~SocketMulticast();
  
  /// \brief �鲥ʵ����ʼ��
  bool sock_init(const std::string& remote_ip, unsigned short remote_port,
                 const std::string& local_ip,
                 int id, SocketEvent* ptr_event);
  
  /// \brief �鲥ʵ���ر�
  bool sock_close();

protected:
  //----------------------------------------------------------------------------
  //�������Ա����
  //----------------------------------------------------------------------------

  /// \brief �鲥���շ��źŵ��̺߳���(linux ��)
  static void* socket_server_event_thread(void* ptr_param);			

  /// \brief �鲥���շ��źŵĴ�����
  void* on_socket_server_event_thread();

  /// \brief �����鲥�źŴ����߳�
  bool start_server_event_thread();										
  /// \brief ֹͣ�鲥�źŴ����߳�
  bool stop_server_event_thread();	
	
  /// \brief ��ͻ�����Ļص��¼�
  bool report_user(SOCKET_EVENT eventType, int id, const char *buff, unsigned int size);
  /// \brief ��־��¼�ӿ�
  void log_msg(const std::string& msg);

protected:
  SocketEvent*			m_event;				///< �ص��ӿ�
  bool				m_thrade_quit_flag;		///< �źż���߳��˳���־		

  std::string			m_remote_ip;			///< �鲥IP
  unsigned short		m_remote_port;			///< �鲥�˿�
  std::string			m_local_ip;				///< ����IP
  int				m_id;					///< ���ӱ��
  int				m_sock;					///< �׽ӿ�
};

}


#endif




