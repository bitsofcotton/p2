import sys
import io
import subprocess
import numpy

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

def sgn(x):
  if(x < 0): return - 1.
  elif(0 < x): return 1.
  return 0.

p  = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
bd = D = bD = M = 0
dh = [0]
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d  = ifloat(line.decode("utf-8")[:- 1].split(",")[0])
  M  = max(M, abs(d))
  dd = 0
  dh.append(d)
  dh = dh[- int(sys.argv[1]):]
  for s in dh:
    dd += s
  bbD = bD
  bD = D
  p.stdin.write((str(dd) + "\n").encode('utf-8'))
  p.stdin.flush()
  bf = p.stdout.readline().decode('utf-8').split(",")
  D  = ifloat(bf[1])
  if(1 < int(sys.argv[1])):
    D -= dd
  if(2 * M < abs(D)):
    D = 0.
  bt = bD * bbD * bd
  if(bt < 0):
    bt = - numpy.log(- bt + 1.)
  else:
    bt =   numpy.log(  bt + 1.)
  print(d * bt, ",", D, ",", bf[0])
  sys.stdout.flush()
  bd = dd

