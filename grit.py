import sys
import subprocess
import numpy

p = [subprocess.Popen(['./p0', '-30', '1'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)]
#p  = [subprocess.Popen(['./p1', '0', '-6', '-2', '-3', '500', '1000'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)]
tp = [[0, 0]]
tm = [[0, 0]]
s  = [0]
M  = [0]
s0 = s1 = bd = 0
for t in range(0, int(sys.argv[1])):
  p.append(subprocess.Popen(['./p0', '-30', '1'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  #p.append(subprocess.Popen(['./p1', '0', '-6', '-2', '-3', '1', '1000'], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  tp.append([0, 0])
  tm.append([0, 0])
  s.append(0)
  M.append(0)
for line in sys.stdin:
  try:
    d   = float(line.split(",")[0])
    s1 += (d - bd) * M[- 1] * (tp[- 1][0] - tp[- 1][1] - tm[- 1][0] + tm[- 1][1])
    for u in range(0, len(p)):
      if(u == 0):
        p[u].stdin.write(str(d) + "\n")
      else:
        p[u].stdin.write(str(s[u - 1]) + "\n")
      p[u].stdin.flush()
      if(u == len(p) - 1):
        s0 += (d - bd) * M[u] * (tp[u][0] - tp[u][1] - tm[u][0] + tm[u][1])
      s[u] += (d - bd) * M[u] * (tp[u][0] - tp[u][1] - tm[u][0] + tm[u][1])
      line = p[u].stdout.readline().split(",")
      tp[u][0] = float(line[4])
      tm[u][0] = float(line[5])
      if(tp[u][0] == 0): tp[u][1] = 0
      if(tm[u][0] == 0): tm[u][1] = 0
      if(u == 0):
        M[u] = float(line[0])
      else:
        M[u] = M[u - 1] * float(line[0]) * (tp[u - 1][0] - tp[u - 1][1] - tm[u - 1][0] + tm[u - 1][1])
      M[u] *= 1e12
    if(0 < s0):
      s0 = 0
      for u in range(0, len(tp)):
        tp[u][1] = tp[u][0]
        tm[u][1] = tm[u][0]
    bd = d
  except:
    continue
  print s1, ",", M[- 1] * (tp[- 1][0] - tp[- 1][1] - tm[- 1][0] + tm[- 1][1])
  #print numpy.log(abs(s1))
  sys.stdout.flush()

