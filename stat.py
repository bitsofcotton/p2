import sys
import io

hM = [0]
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  M = float(line.decode('utf-8').split(",")[1])
  if(M == 0.): continue
  hM.append(abs(M))
  hM  = hM[- int(sys.argv[1]):]
  shM = sorted(hM)
  if(abs(M) < shM[int(float(sys.argv[2]) * len(shM))]):
    print(line.decode('utf-8')[:- 1])
    sys.stdout.flush()

