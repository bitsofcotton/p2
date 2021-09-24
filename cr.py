import sys
import io
import random

# mersenne twister:
rr = random.Random()
# /dev/urandom:
sr = random.SystemRandom()

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

def getrand(mm):
  m = abs(mm)
  # if mm < 0, shuffles random methods.
  if(mm < 0):
    return getrand(abs(getrand(m) * 16))
  global rr, sr
  bw = 0
  # sum up prng nums.
  if(m % 4 == 0):
    bw = rr.uniform(- 1., 1.)
  elif(m % 4 == 1):
    bw = rr.gauss(0., 1.)
  elif(m % 4 == 2):
    bw = sr.uniform(- 1., 1.)
  else:
    bw = sr.gauss(0., 1.)
  if((m / 4) % 2 == 1):
    return bw / getrand(abs(m) % 4)
  return bw

if(4 < len(sys.argv) and sys.argv[4][0] == 'r'):
  if(int(sys.argv[2]) < 0):
    while(True):
      s = getrand(int(sys.argv[1]))
      for idx in range(0, abs(int(sys.argv[3]))):
        if(int(sys.argv[3]) < 0):
          s += getrand(int(sys.argv[1]))
        else:
               getrand(int(sys.argv[1]))
      print(s)
      sys.stdout.flush()
  else:
    for idx in range(0, int(sys.argv[2])):
      s = getrand(int(sys.argv[1]))
      for idx2 in range(0, abs(int(sys.argv[3]))):
        if(int(sys.argv[3]) < 0):
          s += getrand(int(sys.argv[1]))
        else:
               getrand(int(sys.argv[1]))
      print(s)
      sys.stdout.flush()
else:
  t = s = bd = 0
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
        elif(sys.argv[4][0] == 's'):
          s += d
          print(s)
        elif(sys.argv[4][0] == 'u'):
          if(d != bd):
            print(d)
        elif(sys.argv[4][0] == 'n'):
          if(d < 0): print(- 1)
          elif(0 < d): print(1)
          else: print(0)
        bd = d
      else:
        print(d)
      sys.stdout.flush()
    t += 1

