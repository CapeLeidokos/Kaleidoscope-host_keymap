#pragma once

#include "xkbcommon/xkbcommon.h"

#include "ModifierState.h"

#include <string>

struct KaleidoscopeKeycodeInfo {
   xkb_keysym_t key_sym_;
   const char *kaleidoscope_key_;
   ModifierState modifier_state_;
   
   std::string format() const {
      return modifier_state_.addModifiersToKey(kaleidoscope_key_);
   }
};
