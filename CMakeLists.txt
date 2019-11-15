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
)

target_link_libraries(
   host_keymap 
   xkbcommon
   boost_system
   boost_filesystem
   boost_program_options
)
