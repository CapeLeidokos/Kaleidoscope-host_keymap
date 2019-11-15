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

cmake_minimum_required(VERSION 3.0)

project(host_keymap CXX)

find_package(Boost COMPONENTS 
   filesystem
   program_options
   REQUIRED 
)

add_executable(host_keymap 
   host_keymap.cpp
   KeymapInfo.cpp
   LayoutProcessor.cpp
   ModifierState.cpp
   Settings.cpp
   static_maps.cpp
   extra_layouts.cpp
)

target_link_libraries(
   host_keymap 
   xkbcommon
   boost_system
   boost_filesystem
   boost_program_options
)
