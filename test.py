import sys
import subprocess

b = []
for line in sys.stdin:
  b.append(float(line[:- 1].split(",")[0]))
  if(int(sys.argv[1]) < len(b)):
    p = subprocess.Popen(["p", "Wc", "1", str(int(sys.argv[1]))], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    w = []
    for idx in range(1, len(b)):
      w.append(b[idx] - b[idx - 1])
    M = 0.
    wm2 = - b[- 2]
    for idx in range(0, len(w)):
      w[idx] -= wm2
      M = max(M, abs(w[idx]))
    for idx in range(0, len(w)):
      p.stdin.write((str(w[idx] / M) + "\n").encode("utf-8"))
      p.stdin.flush()
      dd = float(p.stdout.readline().decode("utf-8")[:- 1].split(",")[0])
    p.stdin.close()
    print(b[- 1], ",", dd + wm2)
    b = b[- int(sys.argv[1]):]
    sys.stdout.flush()

