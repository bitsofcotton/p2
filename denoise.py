import sys
import io
import subprocess

p  = []
M  = [0, 0]
dd = []
for t in range(0, 6):
  p.append(subprocess.Popen(sys.argv[1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  M.append(0)
  dd.append(0)
t = bd = s = MM = 0
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    d  = float(line.decode("utf-8").split(",")[0])
    s += MM * (d - bd)
    for u in range(0, 4):
      dd[u] += M[u] * (d - bd)
    p[t % 2].stdin.write((str(d + bd) + "\n").encode("utf-8"))
    p[t % 2].stdin.flush()
    M[t % 2] = float(p[t % 2].stdout.readline().decode("utf-8").split(",")[0])
    if(M[t % 2] * (d - bd) < 0):
      M[2 + (t % 2)] = M[t % 2]
      M[t % 2] = 0.
    else:
      M[2 + (t % 2)] = 0.
    MM = 0.
    for u in range(0, 4):
      p[2 + u].stdin.write((str(dd[u]) + "\n").encode("utf-8"))
      p[2 + u].stdin.flush()
      M[4 + u] = float(p[2 + u].stdout.readline().decode("utf-8").split(",")[0])
      MM += M[4 + u] * M[u]
    bd = d
    print(s)
    sys.stdout.flush()
    t += 1

