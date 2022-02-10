#! /usr/bin/env python3
import sys
import subprocess

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

M = MM = 0
t = 1
h = [0]
p = []
M = []
for u in range(0, int(sys.argv[1])):
  p.append(subprocess.Popen(sys.argv[3:], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  M.append(0)
for line in sys.stdin:
  d = ifloat(line.split(",")[0])
  D = d
  nM = []
  for u in range(0, len(p)):
    if(0 < u): D *= M[u - 1]
    p[u].stdin.write((str(int(D)) + "\n").encode("utf-8"))
    p[u].stdin.flush()
    nM.append(ifloat(p[u].stdout.readline().decode("utf-8").split(",")[1]))
  if(sorted(h)[int(len(h) / 2)] * 2. < abs(MM)): D = 0.
  M  = nM
  MM = M[0]
  for u in range(1, len(M)):
    MM *= M[u]
  print(D)
  h.append(abs(MM))
  h = h[- int(sys.argv[2]):]
  t += 1

