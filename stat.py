import sys
import io

bM = 0
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  M = float(line.decode('utf-8').split(",")[1])
  if(abs(bM) < float(sys.argv[1])):
    print(line.decode('utf-8')[:- 1])
    sys.stdout.flush()
  bM = M

