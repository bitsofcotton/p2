import sys
import subprocess

p = subprocess.Popen(sys.argv[1:3], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[3:5], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
r = subprocess.Popen(sys.argv[5:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
for line in sys.stdin:
  p.stdin.write(line.encode("utf-8"))
  q.stdin.write(line.encode("utf-8"))
  r.stdin.write(line.encode("utf-8"))
  p.stdin.flush()
  q.stdin.flush()
  r.stdin.flush()
  pp = p.stdout.readline().decode("utf-8")[:- 1].split(",")
  qq = q.stdout.readline().decode("utf-8")[:- 1].split(",")
  rr = r.stdout.readline().decode("utf-8")[:- 1].split(",")
  print(pp[0], ",", qq[0], ",", rr[0], ",", line[:- 1].split(",")[0])
  sys.stdout.flush()

