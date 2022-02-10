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

M = 0
h = []
p = []
for u in range(0, int(len(sys.argv) - 3)):
  p.append(subprocess.Popen([sys.argv[2], sys.argv[3 + u]], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
for line in sys.stdin:
  D = ifloat(line.split(",")[0])
  bM = M
  M = 1.
  for pp in p:
    pp.stdin.write((str(int(D)) + "\n").encode("utf-8"))
    pp.stdin.flush()
    buf = pp.stdout.readline().decode("utf-8").split(",")
    D   = ifloat(buf[0])
    M  *= ifloat(buf[1])
  h.append(abs(M))
  h = h[- int(sys.argv[1]):]
  if(sorted(h)[int(len(h) / 2)] * 2. < abs(M)): M = 0.
  if(bM == 0.): D = 0.
  print(D, ",", M)

