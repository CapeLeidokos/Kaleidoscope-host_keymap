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

#include <string>
#include <map>

#include "KaleidoscopeKeycodeInfo.h"

class Settings;

struct KeymapInfo {
   
   std::string layout_;
   std::string variant_;
   
   std::map<char, KaleidoscopeKeycodeInfo> ascii_to_kaleidoscope_key_code_;
   std::map<uint32_t, KaleidoscopeKeycodeInfo> unicode_to_kaleidoscope_key_code_;
   std::map<std::string, KaleidoscopeKeycodeInfo> non_printable_to_kaleidoscope_key_code_;
   
   void dump() const;
   
   void writeConfigFile(const Settings &settings) const;
   
   void writeConfigFile(std::ostream &file) const;
   
   static std::string convertToPrintableAscii(xkb_keysym_t key_sym, char ascii);
   static std::string convertToPrintableUnicode(xkb_keysym_t key_sym);
   
   static std::string formatPrintableKeysymInfo(xkb_keysym_t key_sym);
   static std::string formatNonPrintableKeysymInfo(xkb_keysym_t key_sym);
   
   static bool isPrintable(xkb_keysym_t key_sym);
   static bool isNonPrintable(xkb_keysym_t key_sym);
   static bool isKnown(const std::string &name);
};
