import sys
import subprocess
import io

cmd = ["python3",  "./implicit.py"]
for t in range(0, int(sys.argv[2]) - 1):
  cmd.extend(["./catgp", sys.argv[1], ".9", str(int(sys.argv[1]) * int(sys.argv[1])), ",", "python3", "./implicit.py"])
  cmd.extend(["../p1/p1", sys.argv[1], str(max(int(sys.argv[1]) / 4, 1)), "8", ",", "python3", "./implicit.py"])
  cmd.extend(["../p0/p0", sys.argv[1], ",", "python3", "./implicit.py"])
cmd.extend(["./catgp", sys.argv[1], ".9", str(int(sys.argv[1]) * int(sys.argv[1])), ",", "python3", "./implicit.py"])
cmd.extend(["../p1/p1", sys.argv[1], str(max(int(sys.argv[1]) / 4, 1)), "8", ","])
cmd.extend(["../p0/p0", sys.argv[1]])
p = subprocess.Popen(cmd, stdin = subprocess.PIPE, stdout = subprocess.PIPE)

with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    p.stdin.write(line)
    p.stdin.flush()
    print(p.stdout.readline().decode("utf-8"))
    sys.stdout.flush()

