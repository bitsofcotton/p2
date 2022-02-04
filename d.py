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

p = subprocess.Popen(sys.argv[3:], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
t = M = g = 0
H = [0, 0, 0]
h = [0, 0, 0]
g = [0, 0, 0]
for line in io.open(sys.stdin.fileno(), 'r', encoding='utf-8', closefd=False):
  t += 1
  g[- 1]  = h[- 1]
  h[- 1]  = float(line.split(",")[0])
  H[- 1] += h[- 1]
  h[- 1] *= int(sys.argv[1])
  if(t == int(sys.argv[1])):
    # N.B.: SS++ - SS- + SS+ - SS--
    D = M * (H[- 1] - h[- 1] + g[- 2] - H[- 2])
    if(int(sys.argv[2]) < len(H)):
      H = H[- int(sys.argv[2]):]
      h = h[- int(sys.argv[2]):]
      g = g[- int(sys.argv[2]):]
      for u in range(1, len(H)):
        p.stdin.write((str(H[u] - h[u] + g[- 1] - H[- 1]) + "\n").encode("utf-8"))
        p.stdin.flush()
        M = ifloat(p.stdout.readline().decode("utf-8").split(",")[1])
    H.append(0)
    h.append(0)
    g.append(0)
    t = 0
    print(D, ", ", M)
  sys.stdout.flush()

