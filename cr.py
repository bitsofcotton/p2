import sys
import io
import random
import numpy as np

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
      print(getrand(int(sys.argv[1])))
      for idx in range(0, int(sys.argv[3])):
        getrand(int(sys.argv[1]))
      sys.stdout.flush()
  else:
    for idx in range(0, int(sys.argv[2])):
      print(getrand(int(sys.argv[1])))
      for idx2 in range(0, int(sys.argv[3])):
        getrand(int(sys.argv[1]))
      sys.stdout.flush()
  exit(0)

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
      elif(sys.argv[4][0] == 'c'):
        if(bd < 0):
          print(- d)
        else:
          print(  d)
      elif(sys.argv[4][0] == 'e'):
        if(d != 0.):
          print(d)
      elif(sys.argv[4][0] == 'l'):
        if(d == 0):
          print(d)
        elif(d < 0):
          print(- np.log(- d + 1.))
        else:
          print(  np.log(  d + 1.))
      elif(sys.argv[4][0] == 'r'):
        if(bd != 0.):
          print(d / bd - 1.)
      bd = d
    else:
      print(d)
  t += 1
  sys.stdout.flush()

