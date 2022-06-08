import io
import sys
import subprocess

n = int(sys.argv[1])
p = subprocess.Popen(["sh", "-c", "p0 -" + str(n)], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(["sh", "-c", "p0 " + str(n) + " | p0 -" + str(n)], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
r = subprocess.Popen(["sh", "-c", "p0 " + str(n) + " | p0 " + str(n) + " | p0 -" + str(n)], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  p.stdin.write(line.encode("utf-8"))
  q.stdin.write(line.encode("utf-8"))
  r.stdin.write(line.encode("utf-8"))
  p.stdin.flush()
  q.stdin.flush()
  r.stdin.flush()
  print(p.stdout.readline().decode("utf-8")[:- 1].split(",")[2], ",", \
        q.stdout.readline().decode("utf-8")[:- 1].split(",")[2], ",", \
        r.stdout.readline().decode("utf-8")[:- 1].split(",")[2])
  sys.stdout.flush()

