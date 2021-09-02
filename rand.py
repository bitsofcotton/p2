import os, sys, random, numpy

# mersenne twister:
rr = random.Random()
# /dev/urandom:
sr = random.SystemRandom()

def getrand(mm, r):
  m = abs(mm)
  # if mm < 0, shuffles random methods.
  if(mm < 0):
    return getrand(abs(getrand(m, r) * 30), r)
  # if r < 0, shuffles step number.
  if(r < 0):
    work = getrand(m, abs(r)) * 30
  else:
    work = r
  bw = 0
  global rr, sr
  m = abs(mm)
  # sum up prng nums.
  for u in range(0, int(work)):
    if(m % 4 == 0):
      bw = rr.uniform(- 1., 1.)
    elif(m % 4 == 1):
      bw = rr.gauss(0., 1.)
    elif(m % 4 == 2):
      bw = sr.uniform(- 1., 1.)
    else:
      bw = sr.gauss(0., 1.)
  if((m / 4) % 2 == 1):
    return bw / getrand(abs(m) % 4, r)
  return bw

def harden(x, v):
  global n
  res = 0.
  v.append(x)
  if(len(v) == 2 * n):
    return [numpy.arctan(numpy.tan(numpy.inner(numpy.matrix(v[:n]), numpy.matrix(v[n:]), x)[0, 0])), []]
  return [0, v]

t  = 0
v  = []
while(True):
  d, v = harden(getrand(int(sys.argv[1]), int(sys.argv[2])), v)
  if(v != []):
    continue
  print(d)
  sys.stdout.flush()
  if(0 < int(sys.argv[3]) and int(sys.argv[3]) < t): break
  t += 1

