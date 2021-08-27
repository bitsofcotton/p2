import sys
import io
import subprocess

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

p = subprocess.Popen(sys.argv[1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

bd = D = DD = M = 0
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d   = ifloat(line.decode("utf-8")[:- 1].split(",")[0])
  M   = max(M, abs(d))
  p.stdin.write((str(d + bd) + "\n").encode('utf-8'))
  p.stdin.flush()
  bDD = DD
  bD  = D
  DD  = ifloat(p.stdout.readline().decode('utf-8').split(",")[1]) - d
  D   = DD * sgn(bDD * (d + bd))
  if(M < abs(D)):
    D = 0
  print(bD * d, ",", D)
  sys.stdout.flush()
  bd = d

