import io
import sys
import subprocess

t = 0
p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
for line in io.open(sys.stdin.fileno(), 'r', encoding = "utf-8", closefd = False):
  p.stdin.write(line.encode("utf-8"))
  q.stdin.write(line.encode("utf-8"))
  p.stdin.flush()
  q.stdin.flush()
  if(int(int(sys.argv[1]) / 2) == t):
    q.stdin.close()
    q.kill()
    q = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    q.stdin.write(line.encode("utf-8"))
    q.stdin.flush()
  if(int(sys.argv[1]) < t):
    p.stdin.close()
    p.kill()
    p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    p.stdin.write(line.encode("utf-8"))
    p.stdin.flush()
    t = 0
  if(t < int(int(sys.argv[1]) / 2)):
    p.stdout.readline()
    print(q.stdout.readline().decode("utf-8")[:- 1])
  else:
    print(p.stdout.readline().decode("utf-8")[:- 1])
    q.stdout.readline()
  sys.stdout.flush()
  t += 1

