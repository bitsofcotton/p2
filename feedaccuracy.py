import sys
import io
import subprocess

def agm(a, g):
  if(a * g < 0):
    exit(- 1)
  while(1e-8 < abs(a - g)):
    aa = (a + g) / 2.
    gg = pow(a * g, .5)
    if(a < 0):
      gg = - gg
    a = aa
    g = gg
  return (a + g) / 2.

p  = subprocess.Popen(sys.argv[1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
bd = M = s = 0.
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    try:
      d = float(line.decode("utf-8").split(",")[0])
    except:
      continue
    s += (d - bd) * M
    p.stdin.write((str((bd + agm(d, bd)) / 2.) + "\n").encode("utf-8"))
    p.stdin.write((str(( d + agm(d, bd)) / 2.) + "\n").encode("utf-8"))
    p.stdin.flush()
    cf = p.stdout.readline().decode("utf-8").split(",")
    print(str(M) + ", " + str(s) + ", " + str(cf[2][:- 1]))
    cf = p.stdout.readline().decode("utf-8").split(",")
    M  = float(cf[0])
    bd = d
    print(str(M) + ", " + str(s) + ", " + str(cf[2][:- 1]))
    sys.stdout.flush()

