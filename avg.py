import io
import sys

h = [0]
for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  h.append(float(line.split(",")[0]))
  hh = h[0]
  for hhh in h[1:- 1]:
    hh += hhh
  print(h[- 1] - hh / (len(h) - 1.))
  sys.stdout.flush()
  h = h[- int(sys.argv[1]):]

