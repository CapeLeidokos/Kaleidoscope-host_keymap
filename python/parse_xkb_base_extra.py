#!/usr/bin/python

# -*- mode: python -*-
# Kaleidoscope-host_keymap -- A utility for the generation 
#                          of Kaleidoscope host_keymap files 
# Copyright (C) 2019 noseglasses (shinynoseglasses@gmail.com)
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <http://www.gnu.org/licenses/>.
#

import xml.etree.ElementTree as ET
root = ET.parse('/usr/share/X11/xkb/rules/base.extras.xml').getroot()

print("{")
for layout in root.findall('layoutList/layout'):
   
   layout_name = layout.find('configItem/name').text
   
   print("{ \"" + layout_name + "\", {")
   
   for variant in layout.findall('variantList/variant'):
   
      variant_name = variant.find('configItem/name').text
      
      print("   \"" + variant_name + "\", ")
      
   print("   \"\" }")
   print("},")
print("};")
