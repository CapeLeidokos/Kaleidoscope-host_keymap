#!/usr/bin/python

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
