import sys
import io

bM = t = 0
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d = float(line.decode('utf-8').split(",")[0])
  M = float(line.decode('utf-8').split(",")[1])
  if(t < 0):
    print(d, ",", M, ",", 0)
  elif(M != 0):
    print(0, ",", M, ",", d / bM)
  else:
    print(0, ",", 0, ",", 0)
  if(d < 0):
    t = int(sys.argv[1])
  t -= 1
  bM = M
  sys.stdout.flush()

