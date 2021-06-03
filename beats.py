import sys
import subprocess
import io

comma = 0
for s in range(0, len(sys.argv)):
  if(sys.argv[s] == ","):
    comma = s
    break


p = subprocess.Popen(sys.argv[1:comma], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[comma + 1:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    d  = float(line.decode("utf-8").split(",")[0])
    p.stdin.write((str(d) + "\n").encode("utf-8"))
    q.stdin.write((str(d) + "\n").encode("utf-8"))
    p.stdin.flush()
    q.stdin.flush()
    print(p.stdout.readline().decode("utf-8").split(",")[2], ",", \
          q.stdout.readline().decode("utf-8").split(",")[2])
    sys.stdout.flush()

