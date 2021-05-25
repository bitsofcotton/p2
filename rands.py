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

def harden(x, m):
  global n
  res = 0.
  if(len(m) == 0):
    m.append([])
  m[- 1].append(x)
  if(len(m[- 1]) == n):
    if(n + 2 <= len(m)):
      M = numpy.matrix(m[:- 2])
      A = numpy.matrix(m[- 2])
      x = numpy.matrix(m[- 1])
      res = numpy.arctan(numpy.inner(A, x * M)[0, 0])
      m = []
    else:
      m.append([])
  return [res, m]

s  = 0
m  = []
a1 = int(sys.argv[1])
a2 = int(sys.argv[2])
n  = abs(int(sys.argv[3]))
w  = 0
while(True):
  d, m = harden(getrand(a1, a2), m)
  if(m != []):
    continue
  if(d < 0):
    d = - pow(- d, 1. / 3.)
  else:
    d =   pow(  d, 1. / 3.)
  s += d
  if(w <= 0):
    if(int(sys.argv[3]) < 0):
      w = abs(int(d)) % 4
    print(s)
  w -= 1
  sys.stdout.flush()

