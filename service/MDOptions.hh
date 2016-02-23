#ifndef SMACK_MD_OPTIONS_HH
#define SMACK_MD_OPTIONS_HH

#include "soil/Config.hh"

#include <string>

namespace smack
{
namespace po = boost::program_options;

class MDOptions : public soil::Options
{
 public:

  MDOptions();
  
  virtual ~MDOptions();

  virtual po::options_description* configOptions();

  std::string multi_ip;
  
  unsigned short multi_port;

  std::string local_ip;
  
 private:

  boost::program_options::options_description options_;
};

}  


#endif 
