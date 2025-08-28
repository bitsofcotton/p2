import sys

t = 0
b = []
for line in sys.stdin:
  d = line[:- 1].split(",")
  for t in range(0, len(d)): d[t] = float(d[t])
  if(0 < len(b)):
    D = []
    E = []
    for t in range(0, int(len(d) / 2)):
      if(0 < d[t] * b[t] or t % 2 == 1):
        D.append(str(d[t]))
        E.append(str(d[t + int(len(d) / 2)]))
      else:
        D.append(str(0))
        E.append(str(0))
    print(",".join(D), ",", ",".join(E))
  b = d
  t += 1
