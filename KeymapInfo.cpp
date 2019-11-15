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
#include "KeymapInfo.h"
#include "Settings.h"
#include "Exception.h"
#include "static_maps.h"

#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

#include <boost/filesystem.hpp>

std::string keySymToUtf8(xkb_keysym_t key_sym) {
   constexpr std::size_t utf8_buffer_size = 7;
   char utf8_buffer[utf8_buffer_size];
   
   auto utf8_bytes_written 
      = xkb_keysym_to_utf8(key_sym , utf8_buffer, utf8_buffer_size);
      
   assert(utf8_bytes_written > 0);
      
   return std::string{utf8_buffer};
}

void 
   KeymapInfo
      ::dump() const
{
   std::cout << "ascii:" << std::endl;
   for(const auto &entry: ascii_to_kaleidoscope_key_code_) {
      std::cout << "   " << convertToPrintableAscii(entry.second.key_sym_, entry.first)
         << ": " << entry.second.convertToKaleidoscopeKey() << std::endl;
   }
   
   std::cout << "unicode:" << std::endl;
   for(const auto &entry: unicode_to_kaleidoscope_key_code_) {
      std::cout << "   " << convertToPrintableUnicode(entry.second.key_sym_)
         << ": " << entry.second.convertToKaleidoscopeKey() << std::endl;
   }
   
   std::cout << "non printable:" << std::endl;
   for(const auto &entry: non_printable_to_kaleidoscope_key_code_) {
      std::cout << "   " << entry.first 
         << ": " << entry.second.convertToKaleidoscopeKey() << std::endl;
   }
}

std::string  
   KeymapInfo
      ::convertToPrintableAscii(xkb_keysym_t key_sym, char ascii)
{
   switch(key_sym) {
      case XKB_KEY_Tab:
         return "\\t";
      case XKB_KEY_Return:
         return "\\r";
      case XKB_KEY_Linefeed:
         return "\\n";
      case XKB_KEY_Escape:
         return "\\e";
      case XKB_KEY_BackSpace:
         return "\\b";
      case XKB_KEY_apostrophe:
         return "\\\'";
      case XKB_KEY_backslash:
         return "\\\\";
   }
   
   return std::string{ascii};
}

std::string  
   KeymapInfo
      ::convertToPrintableUnicode(xkb_keysym_t key_sym)
{
   switch(key_sym) {
      case XKB_KEY_Tab:
         return "\\t";
      case XKB_KEY_Return:
         return "\\r";
      case XKB_KEY_Linefeed:
         return "\\n";
      case XKB_KEY_Escape:
         return "\\e";
      case XKB_KEY_BackSpace:
         return "\\b";
      case XKB_KEY_apostrophe:
         return "\\\'";
      case XKB_KEY_backslash:
         return "\\\\";
   }
   
   return keySymToUtf8(key_sym);
}

bool   
   KeymapInfo
      ::isPrintable(xkb_keysym_t key_sym)
{
   return printable_key_sym_to_key_info.find(key_sym) 
            != printable_key_sym_to_key_info.end();
}

bool
   KeymapInfo
      ::isNonPrintable(xkb_keysym_t key_sym)
{
   return non_printable_key_sym_to_key_info.find(key_sym) 
            != non_printable_key_sym_to_key_info.end();
}

bool
   KeymapInfo
      ::isKnown(const std::string &name)
{
   return known_xkb_key_names.find(name) 
               != known_xkb_key_names.end();
}

std::string  
   KeymapInfo
      ::formatPrintableKeysymInfo(xkb_keysym_t key_sym)
{
   auto it = printable_key_sym_to_key_info.find(key_sym);
   
   if(it != printable_key_sym_to_key_info.end()) {
   
      std::ostringstream o;
      o << " /* U+" << std::hex  << std::fixed << std::setw(4) << std::setfill('0')
         << xkb_keysym_to_utf32(key_sym) << std::dec 
         << ", " << it->second.name_;
         
      if(!it->second.desc_.empty()) {
         o << ", " << it->second.desc_;
      }
      o << " */";
         
      return o.str();
   }
   
   return formatNonPrintableKeysymInfo(key_sym);
}

std::string  
   KeymapInfo
      ::formatNonPrintableKeysymInfo(xkb_keysym_t key_sym)
{   
   auto it = non_printable_key_sym_to_key_info.find(key_sym);
   
   if(it == non_printable_key_sym_to_key_info.end()) {
      return "";
   }
   
   std::ostringstream o;
   o << " /* " << it->second.name_;
   if(!it->second.desc_.empty()) {
      o << ", " << it->second.desc_;
   }
   o << " */";
      
   return o.str();
}

void 
   KeymapInfo
      ::writeConfigFile(const Settings &settings) const
{
   std::ostringstream o;
   o << settings.base_path_ << "/" << layout_;
   
   if(!variant_.empty()) {
      o << "/" << variant_;
   }
   
   if(!boost::filesystem::exists(o.str())) {
      boost::system::error_code ec;
      if (!boost::filesystem::create_directories(o.str(), ec)) {
         Exception{} << "Couldn't create directory: '" << o.str() << "': "
            << ec.message();
      }
   }
   
   std::ofstream file(o.str() + "/keymap.h");
   
   this->writeConfigFile(file);
}

void 
   KeymapInfo
      ::writeConfigFile(std::ostream &file) const
{
   file << 
"/* Kaleidoscope - Firmware for computer input devices\n"
" * Copyright (C) 2013-2019  Keyboard.io, Inc.\n"
" *\n"
" * This program is free software: you can redistribute it and/or modify it under\n"
" * the terms of the GNU General Public License as published by the Free Software\n"
" * Foundation, version 3.\n"
" *\n"
" * This program is distributed in the hope that it will be useful, but WITHOUT\n"
" * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS\n"
" * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more\n"
" * details.\n"
" *\n"
" * You should have received a copy of the GNU General Public License along with\n"
" * this program. If not, see <http://www.gnu.org/licenses/>.\n"
" */\n"
"\n"
"#pragma once\n"
"\n"
"#include \"kaleidoscope/host_keymap/common.h\"\n"
"\n"
"// This file was autogenerated by host_keymap.\n"
"// Its content is based on information provided by the XKB X11 system\n"
"// collected with the extraordinary libxkbcommon.\n"
"\n";
   file << "// layout: " << layout_ << "\n";
   file << "// variant: " << variant_ << "\n";
   file << "\n";
   file << "#define _HOST_KEYMAP_ASCII_KEYMAP(OP) \\\n";

   for(const auto &entry: ascii_to_kaleidoscope_key_code_) {
      file << "   OP('" << convertToPrintableAscii(entry.second.key_sym_, entry.first) << "', "
         << entry.second.convertToKaleidoscopeKey() << ")" 
         << formatPrintableKeysymInfo(entry.second.key_sym_) << " \\\n";
   }
   file << "\n";
   
   file << "#define _HOST_KEYMAP_UNICODE_KEYMAP(OP) \\\n";
   
   for(const auto &entry: unicode_to_kaleidoscope_key_code_) {
      file << "   OP(L'" << convertToPrintableUnicode(entry.second.key_sym_) << "', "
         << entry.second.convertToKaleidoscopeKey() << ")"
         << formatPrintableKeysymInfo(entry.second.key_sym_) << " \\\n";
   }
   file << "\n";
   
   file << "#define _HOST_KEYMAP_NON_PRINTABLE_KEYMAP(OP) \\\n";
   
   for(const auto &entry: non_printable_to_kaleidoscope_key_code_) {
      if(!isKnown(std::string{"XKB_KEY_" + entry.first})) {
         continue; // Ingore strange symbols that are neigher listed in
                   // xkbcommon_keysyms_non_printable.h
                   // nor xkbcommon_keysyms_printable.h
      }
      file << "   OP(XKB_KEY_" << entry.first << ", "
         << entry.second.convertToKaleidoscopeKey() << ")"
         << formatNonPrintableKeysymInfo(entry.second.key_sym_) << " \\\n";
   }
   file << "\n";
   
   file << "\n";
   file << "namespace kaleidoscope {\n";
   file << "namespace host_keymap {\n";
   file << "namespace linux {\n";
   file << "namespace " << layout_ << " {\n";
   file << "namespace " << variant_ << " {\n";
   file << "\n";
   file << "HOST_KEYMAP_ASCII_CONVERTER(\n";
   file << "  _HOST_KEYMAP_ASCII_KEYMAP,\n";
   file << "  ascii::CharParsingStandardFallback\n";
   file << ")\n";
   file << "\n";
   file << "HOST_KEYMAP_UNICODE_CONVERTER(\n";
   file << "  _HOST_KEYMAP_UNICODE_KEYMAP,\n";
   file << "  unicode::CharParsingStandardFallback\n";
   file << ")\n";
   file << "\n";
   file << "HOST_KEYMAP_NON_PRINTABLE_CONVERTER(\n";
   file << "  _HOST_KEYMAP_NON_PRINTABLE_KEYMAP\n";
   file << ")\n";
   file << "\n";
   file << "} // namespace " << variant_ << "\n";
   file << "} // namespace " << layout_ << "\n";
   file << "} // namespace linux\n";
   file << "} // namespace host_keymap\n";
   file << "} // namespace kaleidoscope\n";
   file << "\n";
   file << "#undef _HOST_KEYMAP_ASCII_KEYMAP\n";
   file << "#undef _HOST_KEYMAP_UNICODE_KEYMAP\n";
   file << "#undef _HOST_KEYMAP_NON_PRINTABLE_KEYMAP\n";
   file << "\n";
}
