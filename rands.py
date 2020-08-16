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

s  = t = s0 = s1 = 0
a1 = int(sys.argv[1])
a2 = int(sys.argv[2])
while(True):
  #ss = s
  #s += getrand(a1, a2)
  #s  += getrand(a1, a2) / getrand(a1, a2)
  s0 += getrand(a1, a2)
  s1 += getrand(a1, a2)
  s0 *= .125
  s1 *= .125
  s  += s0 / (s1 + 2000.)
  print s
  #if(t % 20 == 0):
  #  print s
  #  #print s + ss
  #t += 1
  #print 1. / s
  #print s + ss
  #print int(s)
  #print s - int(s)
  #print getrand(a1, a2)

