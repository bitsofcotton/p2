import sys
import numpy
import io

def ifloat(x):
  b = x.split("*")
  return float(b[0]) * pow(2., float(b[1][2:]))

s = ss = bd = bbd = b3d = 0
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    try:
      d = float(line.decode("utf-8").split(",")[0])
    except:
      d = ifloat(line.decode("utf-8").split(",")[0])
    if((bbd - b3d) * (bd - bbd) < 0):
      M = bbd - bd
    else:
      M = bd - bbd
    if((bd - bbd) * (d - bd) < 0):
      MM = bd - d
    else:
      MM = d - bd
    s  += (d - bd) * M
    ss += (d - bd) - M
    print(str(MM) + ", " + str(ss) + ", " + str(s))
    b3d = bbd
    bbd = bd
    bd  = d
    sys.stdout.flush()

