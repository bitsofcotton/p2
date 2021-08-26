import sys
import io

def ifloat(x):
  try:
    return float(x)
  except:
    try:
      b = x.split("*")
      return float(b[0]) * pow(2., float(b[1][2:]))
    except:
      pass
  return 0.

dh = []
for s in range(0, int(sys.argv[1])):
  dh.append(0)

for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d = ifloat(line.decode('utf-8').split(",")[0])
  for s in range(0, len(dh)):
    bd = d
    d  = (dh[s] + d) / 2.
    dh[s] = bd
  print(d)
  sys.stdout.flush()

