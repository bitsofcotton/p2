import sys
import io

def pascal(n):
  if(n <= 1):
    return [1]
  ret = []
  b   = pascal(n - 1)
  ret.append(b[0])
  for t in range(1, len(b)):
    ret.append(b[t] + b[t - 1])
  ret.append(b[- 1])
  return ret

def inv(n):
  ret = []
  for t in range(1, n + 1):
    ret.append(1. / float(t))
  return ret

p  = inv(int(sys.argv[1]))
dh = []
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  dh.append(float(line.decode('utf-8').split(",")[0]))
  if(2 * len(p) <= len(dh)):
    dh = dh[- len(p):]
    ss = 0
    for s in range(0, len(p)):
      ss += p[s] * dh[s]
    print(ss)
    sys.stdout.flush()

