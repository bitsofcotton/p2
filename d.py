import io
import sys
import subprocess

p = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
t = M = D = B = S = 0
for line in io.open(sys.stdin.fileno(), 'r', encoding='utf-8', closefd=False):
  D += float(line.split(",")[0])
  t += 1
  if(t % int(sys.argv[1]) == 0):
    if(B != 0): S += M * (D - B)
    p.stdin.write((str(D - B) + "\n").encode("utf-8"))
    p.stdin.flush()
    M = float(p.stdout.readline().decode("utf-8").split(",")[0])
    print(S, ",", M)
    B = D
    D = t = 0
  sys.stdout.flush()

