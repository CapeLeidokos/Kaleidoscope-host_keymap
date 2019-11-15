#include "Settings.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
   
void 
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
      ("base_path,b", value(&base_path_), "base path for directory creation")
      ;
   
   variables_map vm;
   store(parse_command_line(argc, argv, desc), vm);
   
   if(base_path_.empty()) {
      boost::filesystem::path full_path(boost::filesystem::current_path());
      std::cout << "Basepath undefined. Setting it to PWD=" << full_path << std::endl;
      base_path_ = full_path.string();
   }
}
