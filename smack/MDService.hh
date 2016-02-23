#ifndef SMACK_MDSERVICE_HH
#define SMACK_MDSERVICE_HH

#include <string>

#include "soil/Config.hh"
#include "smack/SmackDef.hh"

namespace smack
{

class MDServiceCallback
{
 public:

  virtual void onReceiveNormal(const quote_head*, quote_normal* data) = 0;

  virtual void onReceiveSummary(const quote_head*, quote_summary* data) = 0;

  virtual ~MDServiceCallback() {}
};

class MDService
{
 public:

  virtual ~MDService() {};

  static soil::Options* createOptions();
  
  static MDService* createService(soil::Options* options, MDServiceCallback* callback);

}; 

}; // namesapce smack

#endif // SMACK_MDSERVICE_HH
