import sys
import io
import random

bd = s = 0.
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    try:
      d = float(line.decode("utf-8").split(",")[0])
    except:
      continue
    s += (d - bd) * random.uniform(- 1, 1)
    bd = d
    sys.stdout.flush()

