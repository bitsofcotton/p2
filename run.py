import sys
import subprocess

p = subprocess.Popen(['./p012'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
s = bd = M = 0.
for line in sys.stdin:
  try:
    d  = float(line[:- 1].split(",")[0])
    p.stdin.write(str(d) + "\n")
    p.stdin.flush()
    bM = M
    M  = float(p.stdout.readline().split(",")[0])
    if(bd != 0 and bM != 0):
      s += (d - bd) * (d - bd - (M - bM))
    print s
    bd = d
    sys.stdout.flush()
  except:
    continue

