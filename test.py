import subprocess
import sys

cmd = ''
for t in range(0, int(sys.argv[1]) - 2):
  cmd += './p01 ' + str(int(sys.argv[1]) - t) + " -" + str(max(1, (int(sys.argv[1]) - t) / 2)) + ' | cut -f 3 -d "," | '
cmd += './p0 3'

p = subprocess.Popen(['ksh', '-c', cmd], stdin=subprocess.PIPE)

for line in sys.stdin:
  p.stdin.write(line)
  p.stdin.flush()
