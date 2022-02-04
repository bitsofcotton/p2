#! /usr/bin/env python3
import io
import sys
import random
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

p = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
q = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
M = M0 = t = 0
b = []
H = []
h = []
g = []
for t in range(0, int(sys.argv[1])):
  H.append(0.)
  h.append(0.)
  g.append(0.)
for line in io.open(sys.stdin.fileno(), 'r', encoding='utf-8', closefd=False):
  b.append(float(line.split(",")[0]))
  if(t % 2 == 0 and int(sys.argv[1]) * 2 < len(b)):
    b = b[- int(sys.argv[1]) * 2:]
    S = SS = 0.
    for u in range(0, len(H)):
      H[- u - 1] = 0.
      for v in range(0, 2):
        g[- u - 1]  = h[- u - 1]
        H[- u - 1] += SS
        h[- u - 1]  = SS * 2.
        S  -= b[- u * 2 - v - 1]
        SS -= S
    D = M * (H[- 1] - h[- 1])
    q.stdin.write((str(M0 * (H[- 1] - h[- 1])) + "\n").encode("utf-8"))
    q.stdin.flush()
    for u in range(1, len(H)):
      p.stdin.write((str(H[u] - h[u] + g[- 1] - H[- 1]) + "\n").encode("utf-8"))
      p.stdin.flush()
      M = ifloat(p.stdout.readline().decode("utf-8").split(",")[1])
    M0 = M
    M *= ifloat(q.stdout.readline().decode("utf-8").split(",")[1])
    print(D, ", ", M)
  sys.stdout.flush()
  t += 1

