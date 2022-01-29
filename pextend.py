import sys
import subprocess
import random
from PIL import Image
import numpy as np

def sgn(x):
  if(x < 0): return - 1
  elif(x > 0): return 1
  return 0

p = subprocess.Popen(["p0"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
q = subprocess.Popen(["p0"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
P = subprocess.Popen(["p0"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
for file in sys.stdin:
  for tt in range(0, int(sys.argv[1])):
    img0 = Image.open(file[:- 1])
    w    = img0.size[0]
    hh   = img0.size[1]
    img  = []
    jmg  = []
    for x in range(0, w):
      img.append([])
      jmg.append([])
      for y in range(0, hh):
        pp = img0.getpixel((x, y))
        if(not isinstance(pp, tuple) or len(pp) <= 1):
          pp = (pp, pp, pp)
        elif(len(pp) < 3):
          pp = (pp[0], pp[1 % len(pp)], pp[2 % len(pp)])
        img[- 1].append(list(pp))
        qq = (1. / (pp[0] + 1.), 1. / (pp[1] + 1.), 1. / (pp[2] + 1.))
        jmg[- 1].append(list(qq))
    out = Image.new("RGB", (len(img), len(img[0]) + 1))
    for x in range(0, w):
      for y in range(0, hh):
        out.putpixel((x, y), tuple(img[x][y]))
    for x in range(0, w):
      dd = [0, 0, 0]
      for k in range(0, 3):
        d = t = M = S = SS = 0
        H = [0, 0, 0]
        h = [0, 0, 0]
        g = [0, 0, 0]
        for idx in range(1, hh):
          t   += 1
          diff = img[x][idx][k] - img[x][idx - 1][k]
          S   += diff
          SS  += S
          bbd = g[- 1]
          g[- 1] = h[- 1]
          h[- 1] = SS
          H[- 1] += h[- 1]
          h[- 1] *= 2
          q.stdin.write((str(M * (h[- 1] - g[- 1] * 2 + bbd)) + "\n").encode("utf-8"))
          P.stdin.write((str(abs(diff)) + "\n").encode("utf-8"))
          q.stdin.flush()
          P.stdin.flush()
          d = img[x][idx][k] - sgn(M * float(q.stdout.readline().decode("utf-8").split(",")[1])) * abs(float(P.stdout.readline().decode("utf-8").split(",")[1]))
          if(t == 2):
            H = H[- 5:]
            h = h[- 5:]
            g = g[- 5:]
            for tt in range(1, len(H)):
              p.stdin.write((str(H[tt] - h[tt - 1] - h[- 1] + g[- 1] + 1.) + "\n").encode("utf-8"))
              p.stdin.flush()
              M = (float(p.stdout.readline().decode("utf-8").split(",")[1]) - 1.)
            H.append(0)
            h.append(0)
            g.append(0)
            t = 0
        dd[k] = max(0, min(255, int(d)))
      out.putpixel((x, hh), tuple(dd))
    out.save(file[:- 1])

