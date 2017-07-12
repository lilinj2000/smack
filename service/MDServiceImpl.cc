#include "MDServiceImpl.hh"
#include "SmackLog.hh"
#include "MDOptions.hh"

namespace smack
{

#define QUOTE_FLAG_SUMMARY	4

MDServiceImpl::MDServiceImpl(soil::Options* options, MDServiceCallback* callback):
    callback_(callback)
{
  SMACK_TRACE <<"MDServiceImpl::MDServiceImpl()";
  
  options_ = dynamic_cast<MDOptions*>(options);

  multi_.reset( new SocketMulticast() );

  if( !multi_->sock_init(options_->multi_ip,
                         options_->multi_port,
                         options_->local_ip,
                         0, this) )
  {
    throw std::runtime_error("init multi sock failed.");
  }
}


MDServiceImpl::~MDServiceImpl()
{
  SMACK_TRACE <<"MDServiceImpl::~MDServiceImpl()";
  
  multi_->sock_close();
}

void MDServiceImpl::on_receive_message(int id, const char* buff, unsigned int len)
{
  SMACK_TRACE <<"MDServiceImpl::on_receive_message()";

  SMACK_DEBUG <<"id: " <<id
              <<" msg len: " <<len;
  
  if (!callback_)  {
    return;
  }

  if (len < sizeof(guava_udp_normal))	{
		return;
	}

	guava_udp_normal* ptr_data = (guava_udp_normal*)(buff);
  
  callback_->onReceiveNormal(ptr_data);
}

soil::Options* MDService::createOptions()
{
  return new MDOptions();
}

MDService* MDService::createService(soil::Options* options, MDServiceCallback* callback)
{
  return new MDServiceImpl(options, callback);
}

}
