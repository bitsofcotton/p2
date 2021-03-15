import sys
import subprocess
import random

p = subprocess.Popen(['./p01'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
s = bd = M = 0.
for line in sys.stdin:
  #try:
    d  = float(line[:- 1].split(",")[0])
    p.stdin.write(str(d) + "\n")
    bM = M
    r  = p.stdout.readline().split(",")
    M  = float(r[6])
    if(bd != 0 and bM != 0):
      if(bM < M):
        s -= (d - bd)
      elif(M < bM):
        s += (d - bd)
    print s
    bd  = d
    sys.stdout.flush()
  #except:
  #  continue

