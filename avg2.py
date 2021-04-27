import sys
import io

def ifloat(x):
  b = x.split("*")
  return float(b[0]) * pow(2., float(b[1][2:]))

t = bd = 0
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    ll = line.decode("utf-8").split(",")[0]
    try:
      d = float(ll)
    except:
      try:
        d = ifloat(ll)
      except:
        continue
    if(t % 2 == 0):
      print(d + bd)
    bd = d
    t += 1
    sys.stdout.flush()

