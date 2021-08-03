import sys
import io

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

bd = bbd = 0
y  = vy = 1.
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d  = ifloat(line.decode("utf-8")[:- 1].split(",")[int(sys.argv[1])])
  by = y
  if(d != 0.):
    bvy = vy
    vy  = (d - bd + bbd) / d
    if(bvy != 0 and vy != 0):
      y *= vy / bvy
  print(d * y + bd * by)
  bbd = bd
  bd  = d
  sys.stdout.flush()

