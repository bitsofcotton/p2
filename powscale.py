import sys
import io
import subprocess
import numpy as np

def ifloat(x):
  try:
    return float(x)
  except:
    try:
      b = x.split("*")
      return float(b[0]) * pow(2., float(b[1][2:]))
    except:
      pass
  return 0.

p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

bM = 0.
pp = float(sys.argv[1])
if(pp < 0):
  pp = 1. / (- pp)
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d = ifloat(line.decode("utf-8")[:- 1].split(",")[0])
  if(d < 0):
    p.stdin.write((str(- pow(- d, pp)) + "\n").encode("utf-8"))
  else:
    p.stdin.write((str(  pow(  d, pp)) + "\n").encode("utf-8"))
  p.stdin.flush()
  M  = ifloat(p.stdout.readline().decode('utf-8').split(",")[1])
  if(bM < 0):
    print(- pow(- bM, 1. / pp) * d, ", ", bM)
  else:
    print(  pow(  bM, 1. / pp) * d, ", ", bM)
  bM = M
  sys.stdout.flush()

