#include "extra_layouts.h"

// This list of layouts has been generated with
// python/parse_xkb_base_extra.py
//
// It adds some layouts that for unknown reasonst are not
// reported by localectl list-x11-keymap-layouts
// which reads only the file /usr/share/X11/xkb/rules/base.lst
// and the keymaps listed in /usr/share/X11/xkb/rules/base.extras.xml
// are not considered.

std::map<std::string, std::set<std::string>> extra_layouts =
{
{ "apl", {
   "dyalog", 
   "sax", 
   "unified", 
   "apl2", 
   "aplplusII", 
   "aplx", 
   "" }
},
{ "ca", {
   "kut", 
   "shs", 
   "sun_type6", 
   "" }
},
{ "de", {
   "us", 
   "hu", 
   "pl", 
   "sun_type6", 
   "adnw", 
   "koy", 
   "bone", 
   "bone_eszett_home", 
   "neo_qwertz", 
   "neo_qwerty", 
   "ru-recom", 
   "ru-translit", 
   "lld", 
   "" }
},
{ "hu", {
   "oldhun", 
   "" }
},
{ "ir", {
   "ave", 
   "" }
},
{ "lt", {
   "us_dvorak", 
   "sun_type6", 
   "" }
},
{ "lv", {
   "dvorak", 
   "ykeydvorak", 
   "minuskeydvorak", 
   "dvorakprogr", 
   "ykeydvorakprogr", 
   "minuskeydvorakprogr", 
   "colemak", 
   "apostrophecolemak", 
   "sun_type6", 
   "" }
},
{ "us", {
   "intl-unicode", 
   "alt-intl-unicode", 
   "ats", 
   "crd", 
   "cz_sk_de", 
   "ibm238l", 
   "sun_type6", 
   "norman", 
   "carpalx", 
   "carpalx-intl", 
   "carpalx-altgr-intl", 
   "carpalx-full", 
   "carpalx-full-intl", 
   "carpalx-full-altgr-intl", 
   "scn", 
   "" }
},
{ "pl", {
   "intl", 
   "colemak", 
   "sun_type6", 
   "glagolica", 
   "" }
},
{ "ro", {
   "crh_dobruja", 
   "ergonomic", 
   "sun_type6", 
   "" }
},
{ "rs", {
   "combiningkeys", 
   "" }
},
{ "ru", {
   "chu", 
   "ruu", 
   "rulemak", 
   "sun_type6", 
   "prxn", 
   "" }
},
{ "am", {
   "olpc-phonetic", 
   "" }
},
{ "il", {
   "biblicalSIL", 
   "" }
},
{ "ara", {
   "sun_type6", 
   "basic_ext", 
   "basic_ext_digits", 
   "uga", 
   "" }
},
{ "be", {
   "sun_type6", 
   "" }
},
{ "br", {
   "sun_type6", 
   "" }
},
{ "cz", {
   "sun_type6", 
   "" }
},
{ "dk", {
   "sun_type6", 
   "" }
},
{ "nl", {
   "sun_type6", 
   "" }
},
{ "ee", {
   "sun_type6", 
   "" }
},
{ "fi", {
   "das", 
   "sun_type6", 
   "fidvorak", 
   "" }
},
{ "fr", {
   "sun_type6", 
   "" }
},
{ "gr", {
   "sun_type6", 
   "" }
},
{ "it", {
   "sun_type6", 
   "fur", 
   "lld", 
   "" }
},
{ "jp", {
   "sun_type6", 
   "sun_type7", 
   "sun_type7_suncompat", 
   "" }
},
{ "no", {
   "sun_type6", 
   "" }
},
{ "pt", {
   "sun_type6", 
   "" }
},
{ "sk", {
   "sun_type6", 
   "" }
},
{ "es", {
   "sun_type6", 
   "" }
},
{ "se", {
   "dvorak_a5", 
   "sun_type6", 
   "ovd", 
   "" }
},
{ "ch", {
   "sun_type6_de", 
   "sun_type6_fr", 
   "" }
},
{ "tr", {
   "sun_type6", 
   "" }
},
{ "ua", {
   "sun_type6", 
   "" }
},
{ "gb", {
   "sun_type6", 
   "" }
},
{ "kr", {
   "sun_type6", 
   "" }
},
{ "eu", {
   "" }
},
{ "cm", {
   "mmuock", 
   "" }
},
{ "trans", {
   "" }
},
};
