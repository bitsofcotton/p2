import sys, random

# mersenne twister:
rr = random.Random()
# /dev/urandom:
sr = random.SystemRandom()

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

t  = 0
while(True):
  print(getrand(int(sys.argv[1])))
  sys.stdout.flush()
  if(0 < int(sys.argv[2]) and int(sys.argv[2]) < t): break
  t += 1

