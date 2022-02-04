#! /usr/bin/env python3
import io
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

p = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
q = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
M = M0 = S = SS = t = 0
H = []
h = []
g = []
for t in range(0, int(sys.argv[1])):
  H.append(0.)
  h.append(0.)
  g.append(0.)
for line in io.open(sys.stdin.fileno(), 'r', encoding='utf-8', closefd=False):
  S  += float(line.split(",")[0])
  SS += S
  g[- 1]  = h[- 1]
  H[- 1] += SS
  h[- 1]  = SS * 2.
  if(t % 2 == 0):
    # XXX: -S++ - S-
    D = M * (H[- 1] - h[- 1] + g[- 2] - H[- 2])
    q.stdin.write((str(M0 * (H[- 1] - h[- 1] + g[- 2] - H[- 2])) + "\n").encode("utf-8"))
    q.stdin.flush()
    for u in range(1, len(H)):
      p.stdin.write((str(H[u] - h[u] + g[- 1] - H[- 1]) + "\n").encode("utf-8"))
      p.stdin.flush()
      M = ifloat(p.stdout.readline().decode("utf-8").split(",")[1])
    M0 = M
    M *= ifloat(q.stdout.readline().decode("utf-8").split(",")[1])
    print(D, ", ", M)
    H = H[1:]
    h = h[1:]
    g = g[1:]
    H.append(0)
    h.append(0)
    g.append(0)
  sys.stdout.flush()
  t += 1

