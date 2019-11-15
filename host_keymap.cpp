#include <boost/tokenizer.hpp>
// 
// #include "xkbcommon/xkbcommon.h"
// 
#include <iostream>
// #include <exception>
// #include <string>
// #include <sstream>
// #include <map>
// #include <string>
// #include <fstream>

#include "Settings.h"
#include "LayoutProcessor.h"

int main(int argc, const char** argv) {
   
   Settings settings;
   auto parse_result = settings.parse(argc, argv);
   
   if(parse_result != 0) {
      return parse_result - 1;
   }
   
   LayoutProcessor lp(settings);
   
   try {
      lp.readKeyboardLayouts();
   }
   catch(const std::runtime_error &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      exit(1);
   }
}
