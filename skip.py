import sys
t = False
for line in sys.stdin:
  d = line[:- 1].split(",")
  s = []
  for dd in d:
    if(t):
      s.append(str(  float(dd)))
    else:
      s.append(str(- float(dd)))
  t = not t
  print(",".join(s))

