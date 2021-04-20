import sys
import numpy
import io

def ifloat(x):
  b = x.split("*")
  return float(b[0]) * pow(2., float(b[1][2:]))

s = bd = bbd = 0
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    try:
      d = float(line.decode("utf-8").split(",")[0])
    except:
      d = ifloat(line.decode("utf-8").split(",")[0])
    s  += (d - bd) * (bd - bbd)
    print(str(d - bd) + ", " + str(s))
    bbd = bd
    bd  = d
    sys.stdout.flush()

