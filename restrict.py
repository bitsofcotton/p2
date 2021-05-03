import sys
import io
import subprocess

if(len(sys.argv) < 2):
  with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
    for line in stdin:
      print("0, " + line.decode("utf-8")[:- 1] + ", 0")
      sys.stdout.flush()
  exit(0)
dot = 2
for t in range(2, len(sys.argv)):
  if(sys.argv[t] == ","):
    dot = t
    break
p = subprocess.Popen(sys.argv[2:dot], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[dot + 1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
bd = M = N = s = t = 0.
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    d  = float(line.decode("utf-8").split(",")[0])
    t += (d - bd) - N
    s += (d - bd) * M
    q.stdin.write((str(d) + "\n").encode("utf-8"))
    q.stdin.flush()
    bf = q.stdout.readline().decode("utf-8").split(",")
    p.stdin.write((str(int(t)) + "\n").encode("utf-8"))
    p.stdin.flush()
    cf = p.stdout.readline().decode("utf-8").split(",")
    N  = float(bf[0])
    M  = float(bf[0]) + float(cf[0])
    bd = d
    print(str(M) + ", " + str(s) + ", " + str(float(cf[1])))
    sys.stdout.flush()

