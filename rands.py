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

s = 0
while(True):
  s += getrand(int(sys.argv[1]), int(sys.argv[2]))
  #s  = getrand(int(sys.argv[1]), int(sys.argv[2]))
  print s

