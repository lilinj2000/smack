#include "SocketMulticast.hh"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <cstring>

namespace smack
{

SocketMulticast::SocketMulticast()
{
  m_thrade_quit_flag = false;

  m_id = 0;
  m_remote_port = 0;

  m_event = NULL;
  m_sock = MY_SOCKET_DEFAULT;
}

SocketMulticast::~SocketMulticast(void)
{
}

bool SocketMulticast::sock_init(const std::string& remote_ip,
                                unsigned short remote_port,
                                const std::string& local_ip,
                                int id,
                                SocketEvent* ptr_event)
{
  bool b_ret = false;
  const int CONST_ERROR_SOCK = -1;

  m_remote_ip = remote_ip;
  m_remote_port = remote_port;
  m_local_ip = local_ip;
  m_id = id;
  m_event = ptr_event;

  try
  {
    m_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(MY_SOCKET_ERROR == m_sock) 
    {
      throw CONST_ERROR_SOCK;
    }
		
    //socket��������ʹ��һ�����ص�ַ
    int flag=1;
    if(setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, sizeof(flag)) != 0)
    {
      throw CONST_ERROR_SOCK;
    }

    int options = fcntl(m_sock, F_GETFL);
    if(options < 0)
    {
      throw CONST_ERROR_SOCK;
    }
    options = options | O_NONBLOCK;
    int i_ret = fcntl(m_sock, F_SETFL, options);
    if(i_ret < 0)
    {
      throw CONST_ERROR_SOCK;
    }

    struct sockaddr_in local_addr;
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);	
    local_addr.sin_port = htons(m_remote_port);	//multicast port
    if (bind(m_sock, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0)
    {
      throw CONST_ERROR_SOCK;
    }

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(m_remote_ip.c_str());	//multicast group ip
    mreq.imr_interface.s_addr = inet_addr(m_local_ip.c_str());

    if (setsockopt(m_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) != 0)
    {
      throw CONST_ERROR_SOCK;
    }

    int receive_buf_size  = RCV_BUF_SIZE;	
    if (setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (const char*)&receive_buf_size, sizeof(receive_buf_size)) != 0)
    {
      throw CONST_ERROR_SOCK;
    }

    //�����߳�
    b_ret = start_server_event_thread();
  }
  catch(...)
  {
    close(m_sock);				
    b_ret = false;
  }

  return b_ret;
}


bool SocketMulticast::sock_close()
{
  bool b_ret = false;
  //�ر��߳�
  b_ret = stop_server_event_thread();

  if (m_sock != MY_SOCKET_DEFAULT)
  {
    close(m_sock);
    m_sock = MY_SOCKET_DEFAULT;
  }

  return b_ret;
}


void* SocketMulticast::socket_server_event_thread(void* ptr_param)	
{
  SocketMulticast* ptr_this = (SocketMulticast*) ptr_param;
  if (NULL == ptr_this)
  {
    return NULL;
  }

  return ptr_this->on_socket_server_event_thread();
}

void* SocketMulticast::on_socket_server_event_thread()
{
  char line[RCV_BUF_SIZE] = "";

  int n_rcved = -1;

  struct sockaddr_in muticast_addr;

  memset(&muticast_addr, 0, sizeof(muticast_addr));
  muticast_addr.sin_family = AF_INET;
  muticast_addr.sin_addr.s_addr = inet_addr(m_remote_ip.c_str());	
  muticast_addr.sin_port = htons(m_remote_port);

  while (true)
  {
    socklen_t len = sizeof(sockaddr_in);

    n_rcved = recvfrom(m_sock, line, RCV_BUF_SIZE, 0, (struct sockaddr*)&muticast_addr, &len);
    if ( n_rcved < 0) 
    {
      continue;
    } 
    else if (0 == n_rcved)
    {
      continue;
    }					
    else
    {
      report_user(EVENT_RECEIVE, m_id, line, n_rcved);				
    }	

    //����߳��˳��ź�
    if (m_thrade_quit_flag)
    {
      //��ʱ�ѹر������еĿͻ���
      return NULL;
    }		
  }

  return NULL;

}


bool SocketMulticast::start_server_event_thread()
{
  m_thrade_quit_flag = false;


  pthread_t thread_id;
  pthread_attr_t thread_attr;
  pthread_attr_init(&thread_attr);
  pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);		///<�����߳̿ɷ���
  //pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED);		///<�����̵߳ļ̳в��ԺͲ���������schedpolicy �� schedparam����������ʾ����
  //pthread_attr_setscope(&thread_attr, PTHREAD_SCOPE_SYSTEM);				///<�����̵߳���ϵͳ�������߳̽��о���

  //pthread_attr_setschedpolicy(&thread_attr, SCHED_FIFO);					///<�����̵߳ĵ��Բ���
  //int max_priority = sched_get_priority_max(SCHED_FIFO);					///<ȡ���������ȼ�
  ////int min_priority = sched_get_priority_min(SCHED_FIFO);				///<ȡ����С�����ȼ�

  //struct sched_param sched_value;
  //sched_value.sched_priority = max_priority;
  //pthread_attr_setschedparam(&thread_attr, &sched_value);					///<�������ȼ�

  int ret = pthread_create(&thread_id, &thread_attr, socket_server_event_thread, this);
  pthread_attr_destroy(&thread_attr);

  if (ret != 0)
  {
    return false;
  }
	
  return true;
}

bool SocketMulticast::stop_server_event_thread()
{
  m_thrade_quit_flag = true;

  return true;
}


bool SocketMulticast::report_user( SOCKET_EVENT type, int id, const char *buff, unsigned int size )
{
  if(NULL == m_event)
  {
    return false;
  }

  switch(type)
  {
    case  EVENT_RECEIVE:
      {
        m_event->on_receive_message(id, buff, size);
      }
      break;
    default:
      break;
  }
  return true;
}


void SocketMulticast::log_msg( const std::string& msg )
{
  std::cout << msg << std::endl;
}

}



