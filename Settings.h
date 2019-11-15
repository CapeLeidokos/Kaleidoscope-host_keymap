#pragma once

#include <string>

struct Settings {
   std::string base_path_;
   
   int parse(int argc, const char** argv);
};
