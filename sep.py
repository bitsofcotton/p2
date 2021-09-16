import sys
import io
import subprocess

def sgn(x):
  if(0 < x): return 1
  if(x < 0): return - 1
  return 0

p  = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
M  = 0
df = []
for t in range(0, int(sys.argv[1])):
  df.append(0)
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d  = float(line.decode('utf-8').split(",")[0])
  print(d * M)
  sys.stdout.flush()
  u  = 0
  for idx in range(0, len(df)):
    u += sgn(d)
    u *= 2.
    D  = d
    d -= df[idx]
    df[idx] = D
  p.stdin.write((str(u) + "\n").encode('utf-8'))
  p.stdin.flush()
  M = float(p.stdout.readline().decode('utf-8').split(",")[2])

