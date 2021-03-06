import sys
import subprocess
import numpy

p = []
p.append(subprocess.Popen(['./p1', '0', '-12', '-4', '500', '10000'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
for t in range(0, int(sys.argv[1])):
  p.append(subprocess.Popen(['./p1', '0', '-12', '-4', '1', '10000'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
p.append(subprocess.Popen(['./p0', '30', '1'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
M = s = bd = 0
for line in sys.stdin:
  try:
    d  = float(line.split(",")[0])
    s += (d - bd) * M
    M = 1.
    for pp in p:
      pp.stdin.write(str(d) + "\n")
      pp.stdin.flush()
      l  = pp.stdout.readline().split(",")
      M *= float(l[0])
      d  = float(l[3])
    bd = d
  except:
    continue
  print d, ",", M
  sys.stdout.flush()

