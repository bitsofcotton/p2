import sys
import io

def ifloat(x):
  b = x.split("*")
  return float(b[0]) * pow(2., float(b[1][2:]))

bd = p = m = 0
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    ll = line.decode("utf-8").split(",")[0]
    try:
      d = float(ll)
    except:
      d = ifloat(ll)
    if(d < bd):
      m += 1
    if(bd < d):
      p += 1
    print(p, ",", m)
    bd = d
    sys.stdout.flush()

