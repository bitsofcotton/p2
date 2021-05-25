import sys
import numpy
import io

def ifloat(x):
  b = x.split("*")
  return float(b[0]) * pow(2., float(b[1][2:]))

t = bd = 0
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    ll = line.decode("utf-8").split(",")[int(sys.argv[1])]
    try:
      if(len(sys.argv) < 4 or t % int(sys.argv[3]) == 0):
        if(len(sys.argv) < 3):
          print(ll)
          continue
        elif(0 <= float(sys.argv[2])):
          try:
            d = float(ll) * float(sys.argv[2])
          except:
            d = ifloat(ll) * float(sys.argv[2])
        else:
          try:
            d = int(float(ll) * abs(float(sys.argv[2])))
          except:
            d = int(ifloat(ll) * abs(float(sys.argv[2])))
    except:
      t += 1
      continue
    if(4 < len(sys.argv)):
      print(d - bd)
    else:
      print(d)
    t += 1
    bd = d
    sys.stdout.flush()

