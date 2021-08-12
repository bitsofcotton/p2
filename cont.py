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

bd = bbd = D = 0
vy = by  = y = 1.
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d   = ifloat(line.decode("utf-8")[:- 1].split(",")[0])
  bby = by
  by  = y
  if(d != 0.):
    bvy = vy
    vy  = (d - bd - bbd) / d
    y  *= vy / bvy
  # (d * y + bd * by) - (bd * by - bbd * bby)
  # == (d - bd - bbd) * bby + bd * by - bd * by + bbd * bby
  # == (d - bd) * bby
  BD  = D
  #D   = d * y + bd * by
  D   = (d - bd - bbd) * bby + bd * by
  print(D)
  bbd = bd
  bd  = d
  sys.stdout.flush()

