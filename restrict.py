import sys
import io
import subprocess

p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
bd = M = s = 0.
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    d  = float(line.decode("utf-8").split(",")[0])
    s += (d - bd) * M
    p.stdin.write((str(int(d * float(sys.argv[1]))) + "\n").encode("utf-8"))
    p.stdin.flush()
    bf = p.stdout.readline().decode("utf-8").split(",")
    M  = float(bf[0])
    bd = d
    print(str(M) + ", " + str(s) + ", " + str(float(bf[1])))
    sys.stdout.flush()

