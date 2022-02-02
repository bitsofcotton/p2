#! /usr/bin/env python3
import sys
import subprocess
import random
from PIL import Image
import numpy as np

def sgn(x):
  if(x < 0): return - 1
  elif(x > 0): return 1
  return 0

def bits(x, b):
  return float(int(x * pow(2., b)) % 2) - .5

dimg = []
w = h = 0
for line in sys.stdin:
  img = Image.open(line[:- 1])
  if(w != 0 and h != 0 and img.size != (w, h)):
    print("NG", img.size[0], w, img.size[1], h)
  w = img.size[0]
  h = img.size[1]
  if(w == 0 or h == 0): continue
  dimg.append([])
  for x in range(0, w):
    dimg[- 1].append([])
    for y in range(0, h):
      pp = img.getpixel((x, y))
      if(not isinstance(pp, tuple) or len(pp) <= 1):
        pp = (pp, pp, pp)
      elif(len(pp) < 3):
        pp = (pp[0], pp[1 % len(pp)], pp[2 % len(pp)])
      dimg[- 1][- 1].append(pp)
p = subprocess.Popen(["p0"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
q = subprocess.Popen(["p0"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
print("P3")
print(w, " ", h)
print(65535)
for y in range(0, h):
  for x in range(0, w):
    for k in range(0, 3):
      b = d = 0.
      for bit in range(0, 8):
        d = t = M = S = SS = 0
        H = [0, 0, 0]
        h = [0, 0, 0]
        g = [0, 0, 0]
        for u in range(0, int(3000 / len(dimg)) + 1):
          for idx in range(0, len(dimg)):
            S  += bits(dimg[idx][x][y][k] / 256., bit)
            SS += S
        for idx in range(0, len(dimg)):
          t      += 1
          S      += bits(dimg[idx][x][y][k] / 256., bit)
          SS     += S
          bbd     = g[- 1]
          g[- 1]  = h[- 1]
          h[- 1]  = SS
          H[- 1] += h[- 1]
          h[- 1] *= 2
          q.stdin.write((str(M * (h[- 1] - g[- 1] * 2 + bbd)) + "\n").encode("utf-8"))
          q.stdin.flush()
          if(t == 2):
            H = H[- 5:]
            h = h[- 5:]
            g = g[- 5:]
            for tt in range(1, len(H)):
              p.stdin.write((str(H[tt] - h[tt - 1] - h[- 1] + g[- 1] + 1.) + "\n").encode("utf-8"))
              p.stdin.flush()
              M = (float(p.stdout.readline().decode("utf-8").split(",")[1]) - 1.) / 2.
            H.append(0)
            h.append(0)
            g.append(0)
            t = 0
          d = - M * float(q.stdout.readline().decode("utf-8").split(",")[1])
        b /= 2
        if(d > 0):
          b += 1
      print(max(0, min(65535, int(b * 65535))))
    sys.stdout.flush()

