import sys
import numpy

d0 = 0
for line in sys.stdin:
  try:
    d = float(line.split(",")[0]) * float(sys.argv[1])
    if(d0 == 0): d0 = d
    print numpy.arctan(d - d0)
  except:
    continue
  sys.stdout.flush()

