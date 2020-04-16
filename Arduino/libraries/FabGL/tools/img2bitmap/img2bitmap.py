#!/usr/bin/env python

# Converts an image (png, jpeg, ....) to FabGL Bitmap structure
#
# usage:
#    img2bitmap filename [-t x y] [-s width height]
#
# -t = pixel where to take transparent color
# -s = resize to specified values
#
# Example:
#   python img2bitmap.py test.png -s 64 64 >out.c
#
# Requires PIL library:
#   sudo pip install pillow

import sys
import os
from PIL import Image

transpColorPos = None
newSize = None
dithering = False

if len(sys.argv) < 2:
  print "Converts an image (png, jpeg, ....) to FabGL Bitmap structure"
  print "Usage:"
  print "  python img2bitmap filename [-t x y] [-s width height] [-d]\n"
  print "  -t = pixel where to take transparent color"
  print "  -s = resize to specified values\n"
  print "  -d = enable dithering\n"
  print "Example:"
  print "  python img2bitmap.py input.png -s 64 64 >out.c"
  sys.exit()

i = 2
while i < len(sys.argv):
  if sys.argv[i] == "-t":
    transpColorPos = (int(sys.argv[i + 1]), int(sys.argv[i + 2]))
    i += 3
  elif sys.argv[i] == "-s":
    newSize = (int(sys.argv[i + 1]), int(sys.argv[i + 2]))
    i += 3
  elif sys.argv[i] == "-d":
    dithering = True
    i += 1
  else:
    i += 1

filename = sys.argv[1]
name = os.path.basename(os.path.splitext(filename)[0])
im = Image.open(filename).convert("RGBA")

pix = im.load()

transpColor = None
if transpColorPos:
  transpColor = pix[transpColorPos[0], transpColorPos[1]]

for y in range(0, im.height):
  for x in range(0, im.width):
    if transpColor == pix[x, y]:
      pix[x, y] = (0, 0, 0, 0)

if newSize:
  im = im.resize(newSize)

opix = im.load()

if dithering:
  # dithering
  pal64 = []
  for r in range(4):
    for g in range(4):
      for b in range(4):
        pal64.extend((r * 64, g * 64, b * 64))
  pal64image = Image.new('P', (16, 16))
  pal64image.putpalette(pal64)

  im = im.convert("RGB").quantize(64, palette = pal64image).convert("RGB")

else:
  # no dithering
  im = im.quantize(64).convert("RGB")

pix = im.load()


print "const uint8_t {}_data[] = {{".format(name)

for y in range(0, im.height):
  print "\t",
  for x in range(0, im.width):
    v  = int(pix[x, y][0] / 255.0 * 3.0)        # R
    v |= int(pix[x, y][1] / 255.0 * 3.0) << 2   # G
    v |= int(pix[x, y][2] / 255.0 * 3.0) << 4   # B
    v |= int(opix[x, y][3] / 255.0 * 3.0) << 6  # A
    print "0x{:02x},".format(v),
  print

print "};"

print "const Bitmap {} = Bitmap({}, {}, &{}_data[0]);".format(name, im.width, im.height, name)
