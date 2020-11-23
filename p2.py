import sys
import subprocess
import random

nproc = 8
pp    = ['./p']

def getrand():
  return random.uniform(- 1., 1.)

p = []
r = []
d = []
for s in range(0, nproc):
  p.append(subprocess.Popen(pp, stdin=subprocess.PIPE, stdout=subprocess.PIPE))
  r.append(0)
  d.append(0)

bd = 0
bb = 0
ss = 0
for line in sys.stdin:
  dd = float(line)
  b  = 0
  for s in range(0, nproc):
    d[s] += (dd - bd) * r[s]
    p[s].stdin.write(str(d[s]) + "\n")
    p[s].stdin.flush()
    r[s]  = getrand()
    b    += float(p[s].stdout.readline()) * r[s]
  ss += (dd - bd) * bb
  # with beat:
  #ss += (dd - bd) * bb * getrand()
  bd  = dd
  bb  = b
  print ss, ",", b, ",", dd

