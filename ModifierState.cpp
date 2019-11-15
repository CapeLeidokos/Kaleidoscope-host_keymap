#include "ModifierState.h"

#include <sstream>

const char *
   ModifierState
      ::kaleidoscope_mod_macros_[ModifierState::num_modifiers] = {
   "LCTRL",
   "LALT",
   "RALT",
   "LSHIFT",
   "LGUI"
};

int 
   ModifierState
      ::mod_key_codes_[ModifierState::num_modifiers] = {
   37, // LCTRL
   64, // LALT
   108, // RALT
   50, // LSHIFT
   133 // LGUI
};

std::string  
   ModifierState
      ::getModifiersString() const {
   
   std::ostringstream s;
   
   for(int i = 0; i < num_modifiers; i++) {
      if(modifier_bits_ & (1 << i)) {
         s << kaleidoscope_mod_macros_[i] << ", ";
      }
   }
   
   return s.str();
}

unsigned int  
   ModifierState
      ::getNumModifiersActive() const
{ 
   unsigned int n = (unsigned int)modifier_bits_;
   unsigned int count = 0; 
   while (n) { 
      count += n & 1; 
      n >>= 1; 
   } 
   return count; 
} 

void  
   ModifierState
      ::updateMods(struct xkb_state *key_state, const ModifierState &old) 
{ 
   auto mod_changes = this->modifier_bits_ ^ old.modifier_bits_;
   
   //std::cout << "      modifier bits: " << new_mods 
   //   << ", changes: " << mod_changes << std::endl;
      
   // Press/release modifiers
   //
   for(int mod_id = 0; mod_id < num_modifiers; ++mod_id) {
      
      if(mod_changes & (1 << mod_id)) {
         
         auto key_dir = XKB_KEY_UP;
         if(this->isModifierActive(mod_id)) {
            key_dir = XKB_KEY_DOWN;
         }
         
         //std::cout << "         updating modifier " << mod_id
         //   << "=" << mod_key_codes[mod_id] << ", dir: " 
         //   << key_dir << std::endl;
         xkb_state_update_key(key_state, 
                              mod_key_codes_[mod_id],
                              key_dir);
      }
   }
   
//    auto mod_mask 
//       = xkb_state_serialize_mods(key_state, XKB_STATE_MODS_EFFECTIVE);
//       
//    std::cout << "      mod mask: " << mod_mask << std::endl;
}

std::string  
   ModifierState
      ::addModifiersToKey(const std::string &kaleidoscope_key) const {
   std::ostringstream s;
   for(int i = 0; i < num_modifiers; i++) {
      if(this->isModifierActive(i)) {
         s << kaleidoscope_mod_macros_[i] << "(";
      }
   }
   s << kaleidoscope_key;
   for(int i = 0; i < num_modifiers; i++) {
      if(this->isModifierActive(i)) {
         s << ")";
      }
   }
   return s.str();
}
