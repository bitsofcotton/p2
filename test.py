import sys
import subprocess

b = []
for line in sys.stdin:
  b.append(line[:- 1].split(","))
  if(21 * 3 <= len(b)):
    p = subprocess.Popen(["sh", "-c", "p s | p y"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    d = []
    for t in range(0, len(b)):
      p.stdin.write((",".join(b[t]) + "\n").encode("utf-8"))
      p.stdin.flush()
      d.append(p.stdout.readline().decode("utf-8")[:- 1].split(","))
      d.append(p.stdout.readline().decode("utf-8")[:- 1].split(","))
    p.stdin.close()
    D = []
    for t in range(0, len(d[- 2])): D.append(d[- 2][t])
    for t in range(0, len(d)):
      for u in range(0, len(d[t])):
        d[t][u] = str(float(d[t][u]) - float(D[u]))
    q = subprocess.Popen(["sh", "-c", "p d | p d"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    inq = []
    for t in range(0, len(d)):
      q.stdin.write((",".join(d[t]) + "\n").encode("utf-8"))
      q.stdin.flush()
      inq.append(q.stdout.readline().decode("utf-8")[:- 1].split(","))
    q.stdin.close()
    r = subprocess.Popen(["sh", "-c", "p Ac 3 | p lH"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    out = []
    for t in range(0, len(inq)):
      r.stdin.write((",".join(inq[t]) + "\n").encode("utf-8"))
      r.stdin.flush()
      out.append(r.stdout.readline().decode("utf-8")[:- 1].split(","))
    r.stdin.close()
    s = subprocess.Popen(["p", "s"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    if(len(inq) != len(out)): exit(- 1)
    for t in range(0, len(out)):
      s.stdin.write((",".join(inq[t]) + "," + ",".join(out[t]) + "\n").encode(\
        "utf-8"))
      s.stdin.flush()
      last = s.stdout.readline().decode("utf-8")[:- 1]
    s.stdin.close()
    print(last)
    b = b[- 21 * 3:]
  sys.stdout.flush()

