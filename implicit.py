import sys
import subprocess

# if we don't have better results on alias_local,
# the result includes illegal values.
# alias_local twice causes illegal values' illegal value.
# since it's normal value, divide input by illegal to illegal^2 prediction
# causes prediction itself.

p = subprocess.Popen(['/bin/ksh', './alias_local', sys.argv[1]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(['/bin/ksh', './alias_local', sys.argv[1]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

bd = s = M = bm0 = bm1 = m0 = m1 = 0.
for line in sys.stdin:
  d   = float(line.split(",")[0])
  p.stdin.write((str(d) + "\n").encode("utf-8"))
  p.stdin.flush()
  bm0 = m0
  m0  = float(p.stdout.readline().decode("utf-8"))
  q.stdin.write((str(m0) + "\n").encode("utf-8"))
  q.stdin.flush()
  s += (d - bd) * M
  bm1 = m1
  m1  = float(q.stdout.readline().decode("utf-8").split(",")[0])
  if(bm1 == m1):
    M = 0.
  else:
    M = (bm0 - m0) / (bm1 - m1)
  bd  = d
  print(s)
  sys.stdout.flush()

