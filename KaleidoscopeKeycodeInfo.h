/* -*- mode: c++ -*-
 * Kaleidoscope-host_keymap -- A utility for the generation 
 *                          of Kaleidoscope host_keymap files 
 * Copyright (C) 2019 noseglasses (shinynoseglasses@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "xkbcommon/xkbcommon.h"

#include "ModifierState.h"

#include <string>

struct KaleidoscopeKeycodeInfo {
   xkb_keysym_t key_sym_;
   const char *kaleidoscope_key_;
   ModifierState modifier_state_;
   
   std::string convertToKaleidoscopeKey() const {
      return modifier_state_.addModifiersToKey(kaleidoscope_key_);
   }
};
