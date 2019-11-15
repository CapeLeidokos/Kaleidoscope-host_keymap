#include "hid_keyboard_keys.h"
#include "kaleidoscope_keyboard_keys.h"
#include "xkbcommon_keysyms_non_printable.h"
#include "xkbcommon_keysyms_printable.h"
#include "hid_to_key_event.h"

#include <iostream>

#include "Exception.h"
#include "static_maps.h"

#define INIT_HID_CODE_TO_HID_NAME(HID_NAME, NUMBER) { NUMBER, #HID_NAME },
std::map<char, std::string> hid_code_to_hid_name = {
   HID_KEYBOARD_KEYS(INIT_HID_CODE_TO_HID_NAME)
   { 0x00, "UNUSED" }
};
#undef INIT_HID_CODE_TO_HID_NAME

// #define INIT_HID_NAME_TO_HID_CODE(HID_NAME, NUMBER) { #HID_NAME, NUMBER },
// std::map<std::string, char> hid_name_to_hid_code = {
//    HID_KEYBOARD_KEYS(INIT_HID_NAME_TO_HID_CODE)
//    { "UNUSED", 0x00 }
// };
// #undef INIT_HID_NAME_TO_HID_CODE

#define INIT_HID_NAME_TO_KALEIDOSCOPE_NAME(HID_NAME, KALEIDOSCOPE_NAME) \
   { #HID_NAME, #KALEIDOSCOPE_NAME },
std::map<std::string, std::string> hid_name_to_kaleidoscope_name = {
   KALEIDOSCOPE_HID_KEYS(INIT_HID_NAME_TO_KALEIDOSCOPE_NAME)
   { "UNUSED", "UNUSED" }
};
#undef INIT_HID_NAME_TO_KALEIDOSCOPE_NAME

// #define INIT_KALEIDOSCOPE_NAME_TO_HID_NAME(HID_NAME, KALEIDOSCOPE_NAME) \
//    { #KALEIDOSCOPE_NAME, #HID_NAME },
// std::map<std::string, std::string> kaleidoscope_name_to_hid_name = {
//    KALEIDOSCOPE_HID_KEYS(INIT_KALEIDOSCOPE_NAME_TO_HID_NAME)
//    { "UNUSED", "UNUSED" }
// };
// #undef INIT_KALEIDOSCOPE_NAME_TO_HID_NAME

#define INIT_EVENT_CODE_TO_HID_CODE(HID_CODE, EVENT_CODE, EVENT_NAME) \
   { EVENT_CODE, HID_CODE },
std::map<int, char> event_code_to_hid_code = {
   HID_CODE_EVENT_CODE_AND_NAME(INIT_EVENT_CODE_TO_HID_CODE)
   { 0, 0 }
};
#undef INIT_EVENT_CODE_TO_HID_CODE

#define INIT_NON_PRINTABLE_KEY_SYM_TO_KEY_INFO(KEY_SYM_NAME, KEY_SYM, DESC) \
   {KEY_SYM, XKB_KeyInfo{ #KEY_SYM_NAME, KEY_SYM, DESC }},
std::map<int, XKB_KeyInfo> non_printable_key_sym_to_key_info = {
   XKB_KEY_SYM_NAME__KEY_SYM__DESCRIPTION(INIT_NON_PRINTABLE_KEY_SYM_TO_KEY_INFO)
   {0, XKB_KeyInfo{"", 0, ""}}
};
#undef INIT_NON_PRINTABLE_KEY_SYM_TO_KEY_INFO
   
#define INIT_PRINTABLE_KEY_SYM_TO_KEY_INFO(KEY_SYM_NAME, KEY_SYM, UNICODE, DESC) \
   {KEY_SYM, XKB_KeyInfoUnicode{ #KEY_SYM_NAME, KEY_SYM, UNICODE, DESC }},
std::map<int, XKB_KeyInfoUnicode> printable_key_sym_to_key_info = {
   XKB_KEY_NAME__KEY_SYM__UNICODE__DESC(INIT_PRINTABLE_KEY_SYM_TO_KEY_INFO)
   {0, XKB_KeyInfoUnicode{"", 0, 0, ""}}
};
#undef INIT_PRINTABLE_KEY_SYM_TO_KEY_INFO
   
const char *kaleidoscopeNameFromKeyEvent(int event_code) {
   
   auto hid_code_it = event_code_to_hid_code.find(event_code);
   
   if(hid_code_it == event_code_to_hid_code.end()) {
      Exception{} << "Unable to find hid code for event code " << event_code;
   }
   
   auto hid_name_it = hid_code_to_hid_name.find(hid_code_it->second);
   
   if(hid_name_it == hid_code_to_hid_name.end()) {
      Exception{} << "Unable to find hid name for hid code " << hid_code_it->second;
   }
   
   auto kaleidoscope_name_it 
      = hid_name_to_kaleidoscope_name.find(hid_name_it->second);
      
   if(kaleidoscope_name_it == hid_name_to_kaleidoscope_name.end()) {
      Exception{} << "Unable to find kaleidoscope key name for hid name " << 
         hid_name_it->second;
   }
   
   return kaleidoscope_name_it->second.c_str();
}
