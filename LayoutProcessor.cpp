#include "LayoutProcessor.h"
#include "KaleidoscopeKeycodeInfo.h"
#include "KeymapInfo.h"
#include "static_maps.h"

#include <exception>
#include <string>
#include <iostream>
#include <sstream>

#include <boost/tokenizer.hpp>

   LayoutProcessor
      ::LayoutProcessor(const Settings &settings) 
   :  settings_{settings}
{
   xkb_context_ = xkb_context_new(XKB_CONTEXT_NO_DEFAULT_INCLUDES);
   
   if(!xkb_context_) {
      throw std::runtime_error{"Unable to create xkbcommon context"};
   }
   
   if(!xkb_context_include_path_append(xkb_context_, "/usr/share/X11/xkb/")) {
      throw std::runtime_error{"Failed appending include path"};
   }
}
   
   LayoutProcessor
      ::~LayoutProcessor()
{
   xkb_context_unref(xkb_context_);
   xkb_context_ = nullptr;
}

std::string getStdoutFromCommand(std::string cmd) {

   std::string data;
   FILE * stream;
   const int max_buffer = 256;
   char buffer[max_buffer];
   cmd.append(" 2>&1");

   stream = popen(cmd.c_str(), "r");
   if (stream) {
      while (!feof(stream)) {
         if (fgets(buffer, max_buffer, stream) != NULL) {
            data.append(buffer);
         }
      }
   }
   pclose(stream);
         
   return data;
}

int keyEventToKeyCode(int key_event) {
   return key_event + 8;
}

int keyCodeToKeyEvent(int key_code) {
   return key_code - 8;
}

template<typename _MapType>
void addIfLessModifiersUsed(_MapType &m,
                            const typename _MapType::key_type &key,
                            const KaleidoscopeKeycodeInfo &value,
                            int num_modifiers_active)
{
   auto it = m.find(key);
   
   bool add_new_entry = true;
   if(it != m.end()) {
      if(num_modifiers_active >= it->second.modifier_state_.getNumModifiersActive()) {
         add_new_entry = false;
      }
   }
   
   if(add_new_entry) {
      m[key] = value;
   }
}


void
   LayoutProcessor
      ::handleKeysym(KeymapInfo &keymap_info, 
                     int key_event, 
                     const ModifierState &modifier_state,
                     xkb_keysym_t key_sym)
{
   // First check if the key_sym is
   if(key_sym == XKB_KEY_VoidSymbol) { return; }
   
   auto kaleidoscope_key_name = kaleidoscopeNameFromKeyEvent(key_event);
         
   KaleidoscopeKeycodeInfo key_info{
      key_sym,
      kaleidoscope_key_name,
      modifier_state
   };
   
   auto num_modifiers_active = modifier_state.getNumModifiersActive();
   
   constexpr std::size_t utf8_buffer_size = 7;
   char utf8_buffer[utf8_buffer_size];
   
   auto utf8_bytes_written 
      = xkb_keysym_to_utf8(key_sym , utf8_buffer, utf8_buffer_size);
      
   if(utf8_bytes_written > 0) {
      
      auto utf32 = xkb_keysym_to_utf32(key_sym);
      
      if(utf32 <= 127) {
         
         // Is an ascii character
         //
         addIfLessModifiersUsed(
            keymap_info.ascii_to_kaleidoscope_key_code_,
            char(utf32), 
            key_info, 
            num_modifiers_active
         );
       }
      
      addIfLessModifiersUsed(
         keymap_info.unicode_to_kaleidoscope_key_code_,
         utf32, 
         key_info, 
         num_modifiers_active
      );
         
//       std::cout << "      key_event: " << key_event 
//          << ", key_sym: " << key_sym
//          << ", kaleidoscope key: " << kaleidoscope_key_name
//          << ", utf8: " << utf8_buffer
//          << ", modifiers: " << modifier_bits
//          << " = " << getModifiersString(modifier_bits) << std::endl;
      
      return;
   }
      
   // Not a unicode keysym
      
   constexpr std::size_t keysym_name_size = 100;
   char keysym_name[keysym_name_size];
   auto n_chars_transferred = xkb_keysym_get_name(key_sym, keysym_name, keysym_name_size);
   
   if(n_chars_transferred == 0) {
      std::cerr << "Unable to get keysym name for key sym " << key_sym
         << std::endl;
      throw std::runtime_error("Unable to get keysym name");
   }
      
   addIfLessModifiersUsed(
      keymap_info.non_printable_to_kaleidoscope_key_code_,
      std::string{keysym_name}, 
      key_info, 
      num_modifiers_active
   );
}




void 
   LayoutProcessor
      ::parseKeymap(KeymapInfo &keymap_info,
                    struct xkb_keymap *keymap, 
                    struct xkb_rule_names *rule_names)
{ 
   xkb_mod_index_t num_mods = xkb_keymap_num_mods(keymap);
   
   std::cout << "Keymap " << rule_names->layout << ":" << rule_names->variant << std::endl;
   std::cout << "   " << num_mods << " mods: ";
   for(xkb_mod_index_t mod_id = 0; mod_id < num_mods; ++mod_id) {
      const char *mod_name = xkb_keymap_mod_get_name(keymap, mod_id);
      std::cout << mod_name << ", ";
   }
   std::cout << std::endl;
      
   xkb_layout_index_t num_layouts = xkb_keymap_num_layouts(keymap);
   
   std::cout << "   " << num_layouts << " layouts: ";
   for(xkb_layout_index_t layout_id = 0; layout_id < num_layouts; ++layout_id) {
      const char *layout_name = xkb_keymap_layout_get_name(keymap, layout_id);
      std::cout << layout_name << ", ";
   }
   std::cout << std::endl; 
   
   //std::cout << "   keymap:" << std::endl;
   
   auto key_state = xkb_state_new(keymap);
   
   // Iterate over all keys
         
   ModifierState old_modifier_state;
   
   for(const auto &entry: event_code_to_hid_code) {
      
      auto key_event = entry.first;
      auto key_code = keyEventToKeyCode(key_event);
      
      //xkb_layout_index_t num_layouts
      //= xkb_keymap_num_layouts_for_key(keymap, key_code);
      
      // Iterate over all modifier combinations
      //
      //
      for(ModifierState modifier_state{0}; 
          modifier_state < ModifierState::max_modifier_state; 
          ++modifier_state) {

         modifier_state.updateMods(key_state, old_modifier_state);
         
         old_modifier_state = modifier_state;

         auto key_sym = xkb_state_key_get_one_sym(key_state, key_code);
            
         this->handleKeysym(keymap_info, 
                            key_event, 
                            modifier_state,
                            key_sym);
      }
   }
   
   keymap_info.dump();
   keymap_info.writeConfigFile(settings_);
}

void 
   LayoutProcessor
      ::processLayout(const char *layout, const char *variant)
{ 
   struct xkb_rule_names rule_names;
      rule_names.rules = "evdev";
      rule_names.model = "pc105";
      rule_names.layout = layout;
      rule_names.variant = variant;
      rule_names.options = "";
   
   auto keymap = xkb_keymap_new_from_names(xkb_context_, 
                                           &rule_names, 
                                           XKB_MAP_COMPILE_PLACEHOLDER);
   
   if(!keymap) {
      std::cerr << "Error opening keymap " 
         << layout << ":" << variant << std::endl;
   }
   else {
      KeymapInfo keymap_info;
      keymap_info.layout_ = layout;
      keymap_info.variant_ = variant;
      this->parseKeymap(keymap_info, keymap, &rule_names);
      xkb_keymap_unref(keymap);
      keymap = nullptr;
   }
}

void  
   LayoutProcessor
      ::readKeyboardLayouts() 
{
    boost::char_separator<char> sep(", \n");
   
//    std::string keyboard_layouts_string
//       = getStdoutFromCommand("localectl list-x11-keymap-layouts");
//       
//    boost::tokenizer<boost::char_separator<char> > 
//       layouts(keyboard_layouts_string, sep);
   
   std::vector<std::string> layouts = { "de" };
      
   for(const auto &layout: layouts) {
      
      std::ostringstream s;
      s << "localectl list-x11-keymap-variants " << layout;
      
      std::string variants_string = getStdoutFromCommand(s.str());
      
      // Search for the error msg "Couldn't find any entries."
      // or any other string that contains spaces.
      //
      std::size_t found = variants_string.find(" ");
      if(found != std::string::npos) {
         this->processLayout(layout.c_str(), "");
         continue;
      }
      
      boost::tokenizer<boost::char_separator<char> > 
         variants(variants_string, sep);
         
      //std::cout << layout << std::endl;
         
      for(const auto &variant: variants) {
         //std::cout << "   " << variant << std::endl;
         
         this->processLayout(layout.c_str(), variant.c_str());
      }
   }
}
