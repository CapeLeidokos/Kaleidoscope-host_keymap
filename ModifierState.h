#pragma once

#include <string>

#include "xkbcommon/xkbcommon.h"

class ModifierState {
   
   public:
      
      static constexpr int num_modifiers = 5;
      static constexpr unsigned char max_modifier_state = (1 << (num_modifiers + 1)) - 1;
  
      ModifierState(unsigned char init = 0) : modifier_bits_{init} {}
      
      ModifierState &operator=(char modifier_bits) {
         modifier_bits_ = modifier_bits;
         return *this;
      }
      
      ModifierState &operator++() {
         ++modifier_bits_;
         return *this;
      }
      
      bool operator<(char other_modifier_bits) {
         return modifier_bits_ < other_modifier_bits;
      }
      
      bool isModifierActive(int pos) const {
         return modifier_bits_ & (1 << pos);
      }
         
      std::string getModifiersString() const;
      
      unsigned int getNumModifiersActive() const;
      
      void updateMods(struct xkb_state *key_state, const ModifierState &old);
      
      std::string addModifiersToKey(const std::string &kaleidoscope_key) const;
      
   private:
      
      unsigned char modifier_bits_;
      
      static const char *kaleidoscope_mod_macros_[num_modifiers];
      static int mod_key_codes_[num_modifiers];
};
