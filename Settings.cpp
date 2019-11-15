/* -*- mode: c++ -*-
 * Kaleidoscope-host_keymap -- A utility for the generation 
 *                          of Kaleidoscope host_keymap files 
 * Copyright (C) 2019 noseglasses (shinynoseglasses@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
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
