import sys
import io
import subprocess

# interface to p0, p1, p2.
# we average input/prediction by abs(sys.argv[2]) to have
# only exists global prediction vector on the range.

def ifloat(x):
  try:
    return float(x)
  except:
    try:
      b = x.split("*")
      return float(b[0]) * pow(2., float(b[1][2:]))
    except:
      pass
  return 0.

p = subprocess.Popen([sys.argv[1], sys.argv[2]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
t = D = MM = 0
d = []
M = []
for line in io.open(sys.stdin.fileno(), "rb", closefd = False):
  d.append(ifloat(line.decode("utf-8").split(",")[0]))
  D = d[- 1] * MM
  d = d[- abs(int(sys.argv[2])):]
  a = 0.
  for dd in d:
    a += dd
  p.stdin.write(line)
  p.stdin.flush()
  M.append(ifloat(p.stdout.readline().decode("utf-8")))
  M  = d[- abs(int(sys.argv[2])):]
  MM = 0.
  for m in M:
    MM += m
  print(D, ", ", MM)
  sys.stdout.flush()

