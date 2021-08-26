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

p = subprocess.Popen(sys.argv[1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

s = D = bd = bbd = 0
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d  = ifloat(line.decode("utf-8")[:- 1].split(",")[0])
  s += D * (d - bd)
  p.stdin.write((str(d - bbd) + "\n").encode('utf-8'))
  p.stdin.flush()
  D  = ifloat(p.stdout.readline().decode('utf-8').split(",")[1]) - (d - bd)
  print(s)
  sys.stdout.flush()
  bbd = bd
  bd  = d

