#ifndef MD_SERVIE_IMPL_HH
#define MD_SERVIE_IMPL_HH

#include "smack/MDService.hh"
#include "SocketMulticast.hh"

namespace smack
{

class MDOptions;

class MDServiceImpl : public SocketEvent, public MDService
{
 public:
  
  MDServiceImpl(soil::Options* options, MDServiceCallback* callback=0);
  
  ~MDServiceImpl();

 private:
  /// \brief 组播数据接收回调接口
  virtual void on_receive_message(int id, const char* buff, unsigned int len);

private:

  MDOptions* options_;
  
  std::unique_ptr<SocketMulticast>  multi_; ///< UDP行情接收接口

  MDServiceCallback*	callback_; ///< 行情回调事件接口
};

}

#endif
