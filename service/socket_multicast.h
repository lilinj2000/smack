// Copyright 2017 The Smack Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// -----------------------------------------------------------------------------
// File: [file_name]
// -----------------------------------------------------------------------------
//
// [file_descrition]
//
// Example:
//
//   ... ...
//
//

#ifndef SERVICE_SOCKET_MULTICAST_H_
#define SERVICE_SOCKET_MULTICAST_H_

#include <string>

namespace smack {

#define SL_SOCK_DEFAULT 0
#define SL_SOCK_SEND 1
#define SL_SOCK_RECV 2
#define SL_SOCK_ERROR 3

#define MY_SOCKET_DEFAULT -1
#define MY_SOCKET_ERROR -1
#define RCV_BUF_SIZE 65535
#define MAX_SOCKET_CONNECT 1024

enum SOCKET_EVENT {
  EVENT_CONNECT,
  EVENT_REMOTE_DISCONNECT,
  EVENT_LOCALE_DISCONNECT,
  EVENT_NETWORK_ERROR,
  EVENT_RECEIVE,
  EVENT_SEND,
  EVENT_RECEIVE_BUFF_FULL,
  EVENT_UNKNOW
};

class SocketEvent {
 public:
  virtual ~SocketEvent() {
  }

  virtual void on_receive_message(
      int id,
      const char* buff,
      unsigned int len) = 0;
};

class SocketMulticast {
 public:
  SocketMulticast();

  virtual ~SocketMulticast();

  bool sock_init(
      const std::string& remote_ip,
      uint16_t remote_port,
      const std::string& local_ip,
      int id, SocketEvent* ptr_event);

  bool sock_close();

 protected:
  static void* socket_server_event_thread(void* ptr_param);

  void* on_socket_server_event_thread();

  bool start_server_event_thread();

  bool stop_server_event_thread();

  bool report_user(
      SOCKET_EVENT eventType,
      int id,
      const char *buff,
      unsigned int size);

  void log_msg(const std::string& msg);

 protected:
  SocketEvent* m_event;
  bool m_thrade_quit_flag;

  std::string m_remote_ip;
  uint16_t m_remote_port;
  std::string m_local_ip;
  int m_id;
  int m_sock;
};

}  // namespace smack

#endif  // SERVICE_SOCKET_MULTICAST_H_
