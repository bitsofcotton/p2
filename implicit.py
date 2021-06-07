import sys
import subprocess

# usage:
#   cat walk | pythone implicit.py catgp ... "," catgp ... |
#              python3 implicit.py catgp ... "," catgp ...
# N.B.
# we need 2 dimension to predict one function recursions.
# but p1 and catgp needs 4 dimension to complement.
#
# if we don't have better results on some,
# the result includes illegal values.
# do them twice causes illegal values' illegal value.
# since it's normal value, divide input by illegal to illegal^2 prediction
# causes prediction itself.

comma = 1
for t in range(1, len(sys.argv)):
  if(sys.argv[t] == ","):
    comma = t
    break

p = subprocess.Popen(sys.argv[1:comma], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[comma + 1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

bd = s = M = bm0 = m0 = 0.
for line in sys.stdin:
  d   = float(line.split(",")[0])
  s  += (d - bd) * M
  p.stdin.write((str(d - bd) + "\n").encode("utf-8"))
  p.stdin.flush()
  bm0 = m0
  m0  = p.stdout.readline().decode("utf-8").split(",")
  M   = float(m0[0])
  m0  = float(m0[1])
  q.stdin.write((str(m0 - bm0) + "\n").encode("utf-8"))
  q.stdin.flush()
  M  += float(q.stdout.readline().decode("utf-8").split(",")[0])
  bd  = d
  print(s)
  sys.stdout.flush()

