#! /usr/bin/env python3
import io
import sys

def ifloat(x):
  try:
    return float(x)
  except:
    try:
      b = x.split("*")
      return float(b[0]) * pow(2., float(b[1][2:]))
    except:
      pass
  return 0.

h = []
a = True
for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  if(a): print(line[:- 1])
  else:  print(0)
  if(2 < len(h)):
    a = abs(ifloat(line.split(",")[1])) < sorted(h)[int(len(h) / 2)] * 2.
  h.append(abs(ifloat(line.split(",")[1])))
  h = h[- int(sys.argv[1]):]

