import subprocess
import io
import sys

p = subprocess.Popen(sys.argv[1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
M = 0
for line in io.open(sys.stdin.fileno(), "rb", closefd = False):
  l = line.decode("utf-8")[:- 1].split(",")[0]
  d = float(l)
  print(M * d)
  sys.stdout.flush()
  p.stdin.write((l + "\n").encode("utf-8"))
  p.stdin.flush()
  M = float(p.stdout.readline().decode("utf-8").split(",")[1])
  if(M < 0):
    M = - pow(- M, 1. / 3.)
  else:
    M =   pow(  M, 1. / 3.)

