import io
import sys
import subprocess

M = M0 = S = t = 0
p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  d  = float(line.split(",")[0])
  D  = M * d
  p.stdin.write((str(d) + "\n").encode("utf-8"))
  p.stdin.flush()
  bf = p.stdout.readline().decode("utf-8").split(",")
  bS = S
  S += float(bf[0])
  if(bS != 0. and S != 0.):
    q.stdin.write((str(1. / S - 1. / bS) + "\n").encode("utf-8"))
    q.stdin.flush()
    M = float(q.stdout.readline().decode("utf-8").split(",")[1]) * float(bf[1])
  else:
    M = 0.
  print(D, ",", M)
  sys.stdout.flush()
  t += 1
  if(int(sys.argv[1]) < t):
    p.stdin.close()
    q.stdin.close()
    p.kill()
    q.kill()
    p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    q = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    t = S = 0

