import sys
import io
import subprocess

p = subprocess.Popen(sys.argv[1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

r0 = r1 = 1
M0 = M1 = s0 = s1 = MM0 = MM1 = bd = t = 0
for line in io.open(sys.stdin.fileno(), "rb", closefd = False):
  d   = float(line.decode("utf-8").split(",")[0])
  if(t % 2 == 0):
    D   = r1 * MM1 * (d - bd)
    s0 += d - bd
    p.stdin.write((str(s0) + "\n").encode("utf-8"))
    p.stdin.flush()
    MM1 = float(p.stdout.readline().decode("utf-8").split(",")[1])
    if(M1 != 0.):
      r1 *= M1 / (M1 + MM1)
    M1 += MM1
    print(D, ",", r0 * MM0, ",", r0)
  else:
    D   = r0 * MM0 * (d - bd)
    s1 += d - bd
    q.stdin.write((str(s1) + "\n").encode("utf-8"))
    q.stdin.flush()
    MM0 = float(q.stdout.readline().decode("utf-8").split(",")[1])
    if(M0 != 0.):
      r0 *= M0 / (M0 + MM0)
    M0 += MM0
    print(D, ",", r1 * MM1, ",", r1)
  sys.stdout.flush()
  bd = d
  t += 1

