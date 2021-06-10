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
#
# N.B.
# if we set shorter range relative from prng, the result
# can be triangular wave or so on.
# and modern prngs uses some techniques to enlarge originals
# with some periods.

comma = 1
for t in range(1, len(sys.argv)):
  if(sys.argv[t] == ","):
    comma = t
    break

p = subprocess.Popen(sys.argv[1:comma], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[comma + 1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

def ifloat(x):
  s = x.split("*")
  return float(s[0]) * pow(2., float(s[1][2:]))

s = M = 0.
for line in sys.stdin:
  d   = ifloat(line.split(",")[0])
  s  += d * M
  p.stdin.write((line[:- 1].split(",")[0] + "\n").encode("utf-8"))
  p.stdin.flush()
  m0  = p.stdout.readline().decode("utf-8")[:- 1].split(",")
  M   = ifloat(m0[0])
  q.stdin.write((m0[4] + "\n").encode("utf-8"))
  q.stdin.flush()
  M  += ifloat(q.stdout.readline().decode("utf-8").split(",")[0])
  print(s)
  sys.stdout.flush()

