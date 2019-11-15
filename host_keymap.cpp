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
   settings.parse(argc, argv);
   
   LayoutProcessor lp(settings);
   
   lp.readKeyboardLayouts();
}
