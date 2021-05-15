import sys
import io

bd = bbd = s = 0.
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    d   = float(line.decode("utf-8").split(",")[0])
    s  += (d - bd) * (bd - bbd)
    bbd = bd
    bd  = d
    print(s)
    sys.stdout.flush()

