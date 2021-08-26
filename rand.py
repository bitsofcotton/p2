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
    a = numpy.matrix(v[:n])
    x = numpy.matrix(v[n:])
    res = numpy.inner(a, x)[0, 0]
    for xx in v[n:]:
      res *= xx
    v = []
  return [res, v]

s  = 0
v  = []
a1 = int(sys.argv[1])
a2 = int(sys.argv[2])
n  = abs(int(sys.argv[3]))
w  = 0
t  = 0
while(True):
  d, v = harden(getrand(a1, a2), v)
  if(v != []):
    continue
  s += d
  if(w < 0 and int(sys.argv[3]) < 0):
    w = abs(int(d)) % 4
  if(w == 0):
    print(s)
  if(int(sys.argv[3]) < 0):
    w -= 1
  if(w < - 1): w = 0
  sys.stdout.flush()
  if(0 < int(sys.argv[4]) and t > int(sys.argv[4])): break
  t += 1

