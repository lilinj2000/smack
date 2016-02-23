#include "MDOptions.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace smack
{

MDOptions::MDOptions():
    options_("MDOptions")
{
  namespace po = boost::program_options;

  options_.add_options()
      ("smack_md.multi_ip", po::value<std::string>(&multi_ip), 
       "multi ip address")
      ("smack_md.multi_port", po::value<unsigned short>(&multi_port), 
       "multi port")
      ("smack_md.local_ip", po::value<std::string>(&local_ip), 
       "local ip address")
      ;

  return;
  
}

MDOptions::~MDOptions()
{
}

po::options_description* MDOptions::configOptions()
{
  return &options_;
}

};  
