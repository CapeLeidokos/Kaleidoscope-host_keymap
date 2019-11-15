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

#include <map>
#include <set>

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
extern std::map<int, XKB_KeyInfo> non_printable_key_sym_to_key_info;

struct XKB_KeyInfoUnicode
{
   std::string name_;
   int key_sym_;
   int unicode_;
   std::string desc_;
};
extern std::map<int, XKB_KeyInfoUnicode> printable_key_sym_to_key_info;

extern std::set<std::string> known_xkb_key_names;

const char *kaleidoscopeNameFromKeyEvent(int event_code);
