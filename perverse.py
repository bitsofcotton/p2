import sys
import subprocess
import random

p = subprocess.Popen(['./catgp', '8', '.75', '20', '40', '60', '80', '100', '120', '140', '160', '180', '200'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(['./p01'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
s = bd = M = MM = 0.
for line in sys.stdin:
  try:
    d  = float(line[:- 1].split(",")[0])
    p.stdin.write(str(d) + "\n")
    p.stdin.flush()
    q.stdin.write(p.stdout.readline().split(",")[5] + "\n")
    q.stdin.flush()
    bM  = M
    bMM = MM
    qq  = q.stdout.readline().split(",")
    M   = float(qq[6])
    MM  = float(qq[5])
    if(bd != 0 and bM != 0):
      if(bM < M and bMM < MM):
        s -= (d - bd)
      elif(M < bM and MM < bMM):
        s += (d - bd)
      else:
        s += (d - bd) * random.uniform(- 1, 1)
    print s
    bd  = d
    sys.stdout.flush()
  except:
    continue

