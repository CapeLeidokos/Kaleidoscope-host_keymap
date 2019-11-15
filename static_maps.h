#pragma once

#include <map>

extern std::map<char, std::string> hid_code_to_hid_n;
// extern std::map<std::string, char> hid_name_to_hid_code;
extern std::map<std::string, std::string> hid_name_to_kaleidoscope_name;
extern std::map<int, char> event_code_to_hid_code;

struct XKB_KeyInfo
{
   std::string name_;
   int key_sym_;
   std::string desc_;
};
extern std::map<int, XKB_KeyInfo> non_unicode_key_sym_to_key_info;

struct XKB_KeyInfoUnicode
{
   std::string name_;
   int key_sym_;
   int unicode_;
   std::string desc_;
};
extern std::map<int, XKB_KeyInfoUnicode> unicode_key_sym_to_key_info;

const char *kaleidoscopeNameFromKeyEvent(int event_code);
