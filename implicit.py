import sys
import subprocess
import io

def ifloat(x):
  b = x.split("*")
  return float(b[0]) * pow(2., float(b[1][2:]))

u = 0
for t in range(0, len(sys.argv)):
  if(sys.argv[t][0] == ','):
    u = t
    break
p = subprocess.Popen(sys.argv[1:u], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[u + 1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
tp = tm = Sp = Sm = bd = M = S = 0
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
 for line in stdin:
  try:
    d = float(line.decode("utf-8").split(",")[0])
  except:
    continue
  if(bd != 0):
    Sp += (d - bd) * M * tp
    Sm -= (d - bd) * M * tm
    S  += (d - bd) * M * (tp - tm)
    p.stdin.write((str(int(d)) + "\n").encode("utf-8"))
    p.stdin.flush()
    M = p.stdout.readline().decode("utf-8").split(",")
    diff = M[1]
    M    = M[0]
    try:
      M    = float(M)
      diff = float(diff)
    except:
      M    = ifloat(M)
      diff = ifloat(diff)
    q.stdin.write((str(int(diff)) + "\n").encode("utf-8"))
    q.stdin.flush()
    MM = q.stdout.readline().decode("utf-8").split(",")[0]
    try:
      M += float(MM)
    except:
      M += ifloat(MM)
    if(Sp >= 0): Sp = tp = 0
    if(Sm >= 0): Sm = tm = 0
    tp += 1
    tm += 1
  bd = d
  print(str(M) + ", " + str(S))
  sys.stdout.flush()

