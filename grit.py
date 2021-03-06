import sys
import subprocess

p = subprocess.Popen(['./p1', '0', str(int(sys.argv[1])), '-' + str(int(sys.argv[1]) / 4), '500', '10000'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(['./p0', '30', '1'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
M = M0 = s = ss = bd = 0
for line in sys.stdin:
  try:
    d   = float(line.split(",")[0])
    s  += (d - bd) * M
    ss +=  d - bd  - M0
    p.stdin.write(str(d) + "\n")
    p.stdin.flush()
    q.stdin.write(str(ss) + "\n")
    q.stdin.flush()
    l  = p.stdout.readline().split(",")
    M0 = float(l[0])
    M  = M0 * float(q.stdout.readline().split(",")[0])
    bd = d
  except:
    continue
  print s, ",", M
  sys.stdout.flush()

