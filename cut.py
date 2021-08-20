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

t = tt = bd = bbd = dS = s = 0
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  ll = line.decode("utf-8")[:- 1].split(",")[int(sys.argv[1])]
  if(len(sys.argv) < 4 or t % int(sys.argv[3]) == 0):
    if(len(sys.argv) < 3):
      print(ll)
      sys.stdout.flush()
      continue
    elif(0 <= float(sys.argv[2])):
      d = ifloat(ll) * float(sys.argv[2])
    else:
      d = int(ifloat(ll) * abs(float(sys.argv[2])))
    if(4 < len(sys.argv)):
      if(sys.argv[4][0] == 'd'):
        print(d - bd)
        bd = d
      elif(sys.argv[4][0] == 'c'):
        s  += (d - bd) * (bd - bbd)
        print(s)
        bbd = bd
        bd  = d
      elif(sys.argv[4][0] == 's'):
        s += d
        print(s)
      elif(sys.argv[4][0] == 'u'):
        if(d != bd):
          print(d)
        bd = d
      elif(sys.argv[4][0] == 'p'):
        print(d + bd)
        bd = d
    else:
      print(d)
  t += 1
  sys.stdout.flush()

