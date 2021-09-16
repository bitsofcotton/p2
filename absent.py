import sys
import io

t = 0
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d = float(line.decode('utf-8').split(",")[1])
  if(t < 0):
    print(d)
  if(d < 0):
    t = int(sys.argv[1])
  t -= 1
  sys.stdout.flush()

