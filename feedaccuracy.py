import sys
import io
import subprocess

def agm(a, g):
  while(1e-8 < abs(a - g)):
    aa = (a + g) / 2.
    gg = pow(a * g, .5)
    a  = aa
    g  = gg
  return a

p  = subprocess.Popen(sys.argv[1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
bd = M = s = 0.
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    d  = float(line.decode("utf-8").split(",")[0])
    s += (d - bd) * M
    if(bd == 0):
      bd = d
      continue
    p.stdin.write((str(agm(d, bd)) + "\n").encode("utf-8"))
    p.stdin.write((str(d) + "\n").encode("utf-8"))
    p.stdin.flush()
    cf = p.stdout.readline().decode("utf-8").split(",")
    cf = p.stdout.readline().decode("utf-8").split(",")
    M  = float(cf[0])
    bd = d
    print(str(M) + ", " + str(s) + ", " + str(float(cf[2])))
    sys.stdout.flush()

