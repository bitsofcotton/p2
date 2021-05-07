import sys
import io
import subprocess

p  = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
bd = dd = M = s = 0.
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    try:
      d = float(line.decode("utf-8").split(",")[0])
    except:
      continue
    if(abs(M) <= float(sys.argv[1])):
      s += (d - bd) * M
    if(bd == 0):
      bd = d
      continue
    dd += (d / bd) - 1.
    p.stdin.write((str(dd) + "\n").encode("utf-8"))
    p.stdin.flush()
    cf = p.stdout.readline().decode("utf-8").split(",")
    M  = float(cf[0])
    bd = d
    print(str(M) + ", " + str(s) + ", " + str(cf[2][:- 1]))
    sys.stdout.flush()

