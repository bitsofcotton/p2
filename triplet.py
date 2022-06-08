import io
import sys
import subprocess

if(len(sys.argv) <= 1): n = 16
else: n = int(sys.argv[1])
if(16 < n):
  print("This may take large enough n passed into p0:", 3 * 3 * n * n / 2, file=sys.stderr)
  print("To continue, press enter. Otherwise, ^C")
  sys.stdin.readline()
p = subprocess.Popen(["sh", "-c", "p0 " + str(n * n / 2) + " | p0 -" + str(n * n / 2) + " | catgp " + str(n)], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
n = n * 2
q = subprocess.Popen(["sh", "-c", "p0 " + str(n * n / 2) + " | p0 -" + str(n * n / 2) + " | catgp " + str(n)], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
n = int(n / 2 * 3)
r = subprocess.Popen(["sh", "-c", "p0 " + str(n * n / 2) + " | p0 -" + str(n * n / 2) + " | catgp " + str(n)], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

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

