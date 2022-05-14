import io
import sys
import subprocess

p  = subprocess.Popen(['sh', '-c', sys.argv[1]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
tt = 1
bM = 0
for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  d = float(line.split(",")[0])
  p.stdin.write((str(d) + "\n").encode("utf-8"))
  p.stdin.flush()
  M = float(p.stdout.readline().decode("utf-8").split(",")[0])
  print(tt * M)
  bM += tt * M
  if(0 < bM): tt = bM = 0
  tt += 1
  sys.stdout.flush()

