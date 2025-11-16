import io
import sys

b = []
for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
  d = line[:- 1].split(",")
  for t in range(0, len(d)):
    d[t] = float(d[t])
  for t in range(0, int(len(d) / 2)):
    d[t] = (d[t] + d[t + int(len(d) / 2)]) * d[t + int(len(d) / 2)]
  if(len(b)):
    U = []
    for t in range(0, len(b)):
      U.append(str(d[t] * b[t]))
    print(",".join(U))
  b = d
  sys.stdout.flush()

