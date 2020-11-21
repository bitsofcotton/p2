import sys
import subprocess
import random

pp    = ['./p']

def getrand():
  return random.uniform(- 1., 1.)

def sgn(x):
  if(x < 0): return - 1
  elif(0 < x): return 1
  return 0

p  = subprocess.Popen(pp, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
d  = 0.
bd = 0.

for line in sys.stdin:
  ld = float(line)
  p.stdin.write(str(ld) + "\n")
  d += (ld - bd) * sgn(float(p.stdout.readline().split(",")[1])) * getrand()
  bd = ld
  print d

