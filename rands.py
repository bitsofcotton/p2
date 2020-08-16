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
  # N.B. this is raw random:
  s += getrand(a1, a2)
  """
  # N.B. if rand() is created with both side random walk/values:
  s0 *= .125
  s1 *= .125
  s0 += getrand(a1, a2)
  s1 += getrand(a1, a2)
  s  += s0 / (s1 + 2000.)
  """
  #print s
  # N.B. 2 status average with stepped:
  #if(t % 20 == 0):
  #  print s + ss
  #t += 1
  # N.B. exchange higher frequency and lower frequency:
  #print 1. / s
  # N.B. continuous, hacks sampling theorem:
  #print s + ss
  # N.B. lower bit parts, upper bit parts, if they are skew ones:
  #print int(s)
  #print s - int(s)
  # N.B. predict diff (diff x):
  #print getrand(a1, a2)
  # N.B. shifts frequency space:
  """
  if(0 < s):
    print   numpy.exp(  s)
    print   numpy.log(  s)
  else:
    print - numpy.exp(- s)
    print - numpy.log(- s)
  """

