import sys
import io
import subprocess
import numpy

p  = subprocess.Popen(sys.argv[1:3], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
bd = dd = M = s = 0.
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    try:
      d = float(line.decode("utf-8").split(",")[0])
    except:
      continue
    s  += (d - bd) * M
    dd += ((numpy.arctan(d) + 2.) / (numpy.arctan(bd) + 2.)) - 1.
    p.stdin.write((str(dd) + "\n").encode("utf-8"))
    p.stdin.flush()
    cf = p.stdout.readline().decode("utf-8").split(",")
    M  = float(cf[0])
    print(str(M) + ", " + str(s) + ", " + str(cf[2][:- 1]))
    bd = d
    sys.stdout.flush()

