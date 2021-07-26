import sys
import io

def ifloat(x):
  b = x.split("*")
  return float(b[0]) * pow(2., float(b[1][2:]))

dh = []
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    ll = line.decode("utf-8").split(",")[0]
    try:
      dh.append(float(ll))
    except:
      dh.append(ifloat(ll))
    if(len(dh) > int(sys.argv[1])):
      dd = 0.
      for s in range(0, len(dh)):
        dd += dh[s] / (s + 1.)
      print(dd, ",", dh[- 1])
      #dh = dh[1:]
    sys.stdout.flush()

