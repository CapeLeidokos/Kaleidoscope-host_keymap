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
#include <boost/tokenizer.hpp>
#include <iostream>

#include "Settings.h"
#include "LayoutProcessor.h"

int main(int argc, const char** argv) {
   
   Settings settings;
   auto parse_result = settings.parse(argc, argv);
   
   if(parse_result != 0) {
      return parse_result - 1;
   }
   
   LayoutProcessor lp(settings);
   
   try {
      lp.readKeyboardLayouts();
   }
   catch(const std::runtime_error &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      exit(1);
   }
}
