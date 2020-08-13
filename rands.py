import os, sys, random, numpy

rr = random.Random()
sr = random.SystemRandom()
def getrand(mm, r):
  m = abs(mm)
  if(mm < 0):
    return getrand(abs(getrand(m, r) * 30), r)
  if(r < 0):
    work = getrand(m, abs(r)) * 30
  else:
    work = r
  bw = 0
  global rr, sr
  m = abs(mm)
  for u in range(0, int(work)):
    if(m % 4 == 0):
      bw += rr.uniform(- 1., 1.)
    elif(m % 4 == 1):
      bw += rr.gauss(0., 1.)
    elif(m % 4 == 2):
      bw += sr.uniform(- 1., 1.)
    else:
      bw += sr.gauss(0., 1.)
  return bw

s  = 0
a1 = int(sys.argv[1])
a2 = int(sys.argv[2])
while(True):
  s += getrand(a1, a2) / getrand(a1, a2)
  #s += getrand(a1, a2)
  print 1. / s

