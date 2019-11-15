#include "Settings.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
   
int 
   Settings
      ::parse(int argc, const char** argv)
{
   using namespace boost::program_options;
   options_description desc("Allowed settings");
   desc.add_options()
      // First parameter describes option name/short name
      // The second is parameter to option
      // The third is description
      ("help,h", "print usage message")
      ("base_path,b", value<std::string>(), "base path for directory creation")
      ;
   
   variables_map vm;
   store(parse_command_line(argc, argv, desc), vm);
   
   if (vm.count("help")) {
      std::cout << "Usage: " << argv[0] << "[options]\n";
      std::cout << desc;
      return 1;
   }
   
   if(vm["base_path"].empty()) {
      std::cerr << "Please define a base path" << std::endl;
      return 2;
   }
   
   base_path_ = vm["base_path"].as<std::string>();
   
   return 0;
}
