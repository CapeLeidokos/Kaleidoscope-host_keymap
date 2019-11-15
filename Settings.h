#pragma once

#include <string>

struct Settings {
   std::string base_path_;
   
   void parse(int argc, const char** argv);
};
