import sys
import random

#b = random.uniform(- 1, 1)
b = 0.
for line in sys.stdin:
  # (d + b) / 2. == D <=> 2D - b = d
  D = float(line.split(",")[0])
  print(b)
  print(D)
  b = 2. * D - b

