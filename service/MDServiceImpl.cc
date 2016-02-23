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
  
  if( !callback_ )
  {
    return;
  }

  if( len<(sizeof(quote_head) + sizeof(quote_normal)) )
  {
    return;
  }

  quote_head* ptr_head = (quote_head*)buff;
  if (ptr_head->m_quote_flag != QUOTE_FLAG_SUMMARY)
  {
    quote_normal* ptr_data = (quote_normal*)(buff + sizeof(quote_head));
    callback_->onReceiveNormal(ptr_head, ptr_data);
  }
  else
  {
    quote_summary* ptr_data = (quote_summary*)(buff + sizeof(quote_head));
    callback_->onReceiveSummary(ptr_head, ptr_data);
  }
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
