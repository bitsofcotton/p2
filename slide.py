import sys
import io
import subprocess

# N.B. if the algorithm step.py is targetted to jam,
#      average each causes de-jamming.
p = []
for t in range(0, int(sys.argv[1])):
  p.append([])
  for s in range(0, t + 1):
    p[- 1].append(subprocess.Popen(['python3', 'step.py', str(t)], stdin = subprocess.PIPE, stdout = subprocess.PIPE))

t = 1
s = 0
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  for q in p:
    for tt in range(0, min(len(q), t)):
      q[tt].stdin.write(line)
      q[tt].stdin.flush()
      if(len(q) < t and tt % len(q) == (t - 1) % len(q)):
        s += float(q[tt].stdout.readline().decode('utf-8').split(",")[0])
  print(s)
  sys.stdout.flush()
  t += 1

