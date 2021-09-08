import sys
import io
import subprocess

p = subprocess.Popen(['./catgp'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(['../p0/p0', str(int(sys.argv[2]))], stdin = subprocess.PIPE)

bM = S = 0
sh = []
Mh = []
mh = []
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  d  = float(line.decode('utf-8').split(",")[0])
  S += d
  sh.append(S)
  sh = sh[- int(sys.argv[1]):]
  q.stdin.write((str(d * bM) + "\n").encode('utf-8'))
  q.stdin.flush()
  p.stdin.write((str(S - sh[0]) + "\n").encode('utf-8'))
  p.stdin.flush()
  Mh.append(float(p.stdout.readline().decode('utf-8').split(",")[1]) + S)
  Mh = Mh[- int(sys.argv[1]):]
  bM = 0
  for midx in range(0, len(Mh)):
    bM += Mh[midx]
  mh.append(bM / len(Mh))
  mh = mh[- int(sys.argv[1]):]
  bM = 0
  for midx in range(0, len(mh)):
    bM += (mh[midx] - S) / float(len(mh) - midx)

