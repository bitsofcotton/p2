import io
import sys
import subprocess

if(len(sys.argv) <= 1):
  p = []
  for t in range(0, 9):
    p.append(subprocess.Popen(["python3", sys.argv[0], "9"], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  M = 0.
  for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
    ll = line.encode("utf-8")
    d  = float(line.split(",")[0]) * M
    M  = 1.
    for pp in p:
      pp.stdin.write(ll)
      pp.stdin.flush()
      ll = pp.stdout.readline()
      M *= float(ll.decode("utf-8").split(",")[1])
    print(d, ",", M)
    sys.stdout.flush()
else:
  p = []
  p.append(subprocess.Popen(['p0'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  p.append(subprocess.Popen(['p0', '0'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  p.append(subprocess.Popen(['p0', '-11'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  p.append(subprocess.Popen(['p1'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  p.append(subprocess.Popen(['p1', '0'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  p.append(subprocess.Popen(['p1', '1'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  p.append(subprocess.Popen(['catgp'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  p.append(subprocess.Popen(['cr.py', 'a', '80', '80'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  p.append(subprocess.Popen(['cr.py', 'i'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  M = 0.
  for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
    for pp in p:
      pp.stdin.write(line.encode("utf-8"))
      pp.stdin.flush()
    d = float(line.split(",")[0]) * M
    if(float(line.split(",")[0]) != 0.):
      M = 0.
      for pp in p[:- 2]:
        M += max(- 1, min(1, float(pp.stdout.readline().decode("utf-8").split(",")[1]) ))
      for pp in p[- 2:]:
        M += max(- 1, min(1, float(pp.stdout.readline().decode("utf-8")) / 1e6))
    print(d, ",", M / len(p))
    sys.stdout.flush()

