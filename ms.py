import io
import sys

def minsq(a):
  xsum = ysum = xdot = ydot = 0.
  for t in range(0, len(a)):
    xsum += t
    ysum += a[t]
    xdot += t * t
    ydot += t * a[t]
  if(xdot * len(a) == xsum * xsum): return 0.
  return (ydot * len(a) - xsum * ysum) / (xdot * len(a) - xsum * xsum)

h = [0]
g = [0]
S = 0
for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  d  = float(line.split(",")[0])
  S += d * minsq(g)
  print(d * minsq(g), ",", S)
  h.append(d + h[- 1])
  h  = h[- int(sys.argv[1]):]
  g.append(minsq(h))
  g  = g[- int(sys.argv[1]):]
  sys.stdout.flush()

