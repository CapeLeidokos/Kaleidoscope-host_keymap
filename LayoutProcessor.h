#pragma once

#include "xkbcommon/xkbcommon.h"

#include <string>

class KeymapInfo;
struct Settings;
class ModifierState;

class LayoutProcessor {
   
   public:
      
      LayoutProcessor(const Settings &settings);
      ~LayoutProcessor();
      
      void readKeyboardLayouts();
      void processLayout(const std::string &layout,
                         const std::string &variant);
   
      void parseKeymap(KeymapInfo &keymap_info,
                       struct xkb_keymap *keymap, 
                    struct xkb_rule_names *rule_names);
      
      void handleKeysym(KeymapInfo &keymap_info, 
                     int key_event, 
                     const ModifierState &modifier_state,
                     xkb_keysym_t key_sym);
      
      void updateMods(struct xkb_state *state, 
                      int old_mods, int new_mods);
      
   private:
      
      const Settings &settings_;
      struct xkb_context *xkb_context_;
};
