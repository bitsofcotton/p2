import sys

for line in sys.stdin:
  d = line[:- 1].split(",")
  D = []
  E = []
  for t in range(0, int(len(d) / 4)):
    if((float(d[t + int(len(d) / 4)]) - float(d[t])) *\
      (float(d[t + int(len(d) / 4) * 3]) -\
       float(d[t + int(len(d) / 4) * 2]) ) > 0.):
      D.append(str(float(d[t]) - float(d[t + int(len(d) / 4) * 2])))
      E.append(str(float(d[t + int(len(d) / 4)]) - float(d[t + int(len(d) / 4) * 3])))
    else:
      D.append("0")
      E.append("0")
  print(",".join(D), ",", ",".join(E))

