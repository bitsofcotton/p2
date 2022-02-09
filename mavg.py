#! /usr/bin/env python3
import sys
import subprocess

M = sum = 0
t = 1
p = subprocess.Popen(sys.argv[1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
for line in sys.stdin:
  d = float(line.split(",")[0])
  D = d * (M + (sum / t))
  p.stdin.write((str(d - (sum / t)) + "\n").encode("utf-8"))
  p.stdin.flush()
  M = float(p.stdout.readline().decode("utf-8").split(",")[1])
  print(D, ", ", M + (sum / t))
  sum += d
  t   += 1
