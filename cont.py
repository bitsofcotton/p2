import sys

Mdh = abs(int(sys.argv[1]))
off = 8
if(2 < len(sys.argv)): off = abs(int(sys.argv[2]))
bd = 0
dh = []
gg = []
for t in range(0, Mdh):
  dh.append([])
  gg.append([0, t * 2 + off])
t = 0
for line in sys.stdin:
  t += 1
  dd = float(line.split(",")[0])
  d  = dd - bd
  bd = dd
  for s in range(0, len(dh)):
    if(len(dh[s]) <= 0):
      continue
    sdh = []
    avg = 0.
    for u in range(0, len(dh[s])):
      sdh.append(dh[s][u])
      avg += dh[s][u]
    avg /= len(dh[s])
    for u in range(0, len(dh[s])):
      sdh[u] -= avg
      sdh[u]  = abs(sdh[u])
    sdh = sorted(sdh)
    if(0 < len(sdh) and \
       sdh[len(sdh) / 2] * pow(len(sdh), .5) < abs(d - avg)):
      gg[s][0] += 1
  ggg = sorted(gg)
  print ggg[0], ggg[1], ggg[- 2], ggg[- 1]
  sys.stdout.flush()
  for s in range(0, len(dh)):
    dh[s].append(d)
    dh[s] = dh[s][- gg[s][1]:]

