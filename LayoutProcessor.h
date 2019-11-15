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
