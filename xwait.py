#! /usr/bin/env python3
import io
import sys
import numpy
import subprocess

p  = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
h  = [0]
g  = [0]
tt = M = S = d = 0
bd = 1
for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  d0 = float(line.split(",")[0])
  d += d0
  if(d * bd < 0.):
    D  = abs(M * h[- 1]) * d * pow(- 1., tt)
    p.stdin.write((str(d) + "\n").encode("utf-8"))
    p.stdin.flush()
    h.append(float(p.stdout.readline().decode("utf-8").split(",")[1]))
    g.append(d)
    if(not numpy.isfinite(h[- 1])): h[- 1] = 0.
    hh = gg = 0.
    for idx in range(1, min(len(h) - 1, len(g))):
      hh += h[- idx - 1] * h[- idx - 1]
      gg += g[- idx] * g[- idx]
    if(abs(hh) == 0): M = 0
    else: M = pow(gg / hh, .5)
    bd = d
    d  = 0.
    h  = h[- int(sys.argv[1]):]
    g  = g[- int(sys.argv[1]):]
    tt += 1
  elif(abs(M * h[- 1]) / 2. < abs(d) and d * pow(- 1., tt) < 0):
    D  = abs(M * h[- 1]) * d * pow(- 1., tt)
    M  = 0
  else:
    D  = 0
  S += D
  print(D, ",", abs(M * h[- 1]) * pow(- 1., tt), ",", S)
  sys.stdout.flush()

