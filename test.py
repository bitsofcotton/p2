import sys
import subprocess

t = 0
b = []
for line in sys.stdin:
  b.append(line[:- 1])
  if(t % 2 == 0 and int(sys.argv[1]) <= len(b)):
    p = subprocess.Popen(["ksh", "-c", "p / | p 0 " + str(int(sys.argv[1]))], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    for t in range(0, len(b) - 2):
      p.stdin.write((b[t] + "\n").encode("utf-8"))
      p.stdin.flush()
      p.stdout.readline()
    buf = []
    bb  = b[- 2].split(",")
    bc  = b[- 3].split(",")
    for t in range(0, int(len(bc) / 3)):
      buf.append(str(bc[t]))
    for t in range(int(len(bb) / 3), len(bb)):
      buf.append(str(bb[t]))
    p.stdin.write((",".join(buf) + "\n").encode("utf-8"))
    p.stdin.flush()
    p.stdout.readline()
    p.stdin.write((b[- 1] + "\n").encode("utf-8"))
    p.stdin.flush()
    print(p.stdout.readline().decode("utf-8")[:- 1])
    p.stdin.close()
    b = b[- int(sys.argv[1]):]
  t += 1

