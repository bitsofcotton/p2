import sys
import subprocess

p = subprocess.Popen(sys.argv[1:3], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[3:5], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
r = subprocess.Popen(sys.argv[5:7], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
for line in sys.stdin:
  p.stdin.write(line.encode("utf-8"))
  q.stdin.write(line.encode("utf-8"))
  r.stdin.write(line.encode("utf-8"))
  p.stdin.flush()
  q.stdin.flush()
  r.stdin.flush()
  pp = float(p.stdout.readline().decode("utf-8")[:- 1].split(",")[2])
  qq = float(q.stdout.readline().decode("utf-8")[:- 1].split(",")[2])
  rr = float(r.stdout.readline().decode("utf-8")[:- 1].split(",")[2])
  print(pp, ",", qq, ",", rr, ",", pp + qq + rr)
  sys.stdout.flush()

