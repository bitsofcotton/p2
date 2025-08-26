import sys
import subprocess

b = []
for line in sys.stdin:
  b.append(line[:- 1].split(","))
  if(22 * 3 < len(b)):
    p = subprocess.Popen(["sh", "-c", "p s | p y"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    d = []
    for t in range(0, len(b)):
      p.stdin.write((str(float(b[t][0])) + "\n").encode("utf-8"))
      p.stdin.flush()
      d.append(float(p.stdout.readline().decode("utf-8")[:- 1].split(",")[0]))
      d.append(float(p.stdout.readline().decode("utf-8")[:- 1].split(",")[0]))
    p.stdin.close()
    D = d[- 2]
    for t in range(0, len(d)):
      d[t] -= D
    q = subprocess.Popen(["sh", "-c", "p d | p d"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    inq = []
    for t in range(0, len(d)):
      q.stdin.write((str(d[t]) + "\n").encode("utf-8"))
      q.stdin.flush()
      inq.append(float(q.stdout.readline().decode("utf-8")[:- 1].split(",")[0]))
    q.stdin.close()
    r = subprocess.Popen(["sh", "-c", "p Ac 3 | p lH"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    out = []
    for t in range(0, len(inq)):
      r.stdin.write((str(inq[t]) + "\n").encode("utf-8"))
      r.stdin.flush()
      out.append(float(r.stdout.readline().decode("utf-8")[:- 1].split(",")[0]))
    r.stdin.close()
    s = subprocess.Popen(["p", "s"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    for t in range(0, min(len(inq), len(out)) ):
      s.stdin.write((str(inq[t - min(len(inq), len(out))]) + ", " + \
        str(out[t - min(len(inq), len(out))]) + "\n").encode("utf-8"))
      s.stdin.flush()
      last = s.stdout.readline().decode("utf-8")[:- 1]
    s.stdin.close()
    print(last)
    b = b[- 22 * 3:]
  sys.stdout.flush()

