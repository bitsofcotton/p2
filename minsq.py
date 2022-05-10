import io
import sys
import subprocess

p = []
walk = []
tilt = []
for t in range(0, int(sys.argv[2])):
  p.append(subprocess.Popen(["p0", str(int(sys.argv[1]))], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
  walk.append([])
  tilt.append([])

def minsq(a):
  xsum = ysum = xdot = ydot = 0.
  for t in range(0, len(a)):
    xsum += t
    ysum += a[t]
    xdot += t * t
    ydot += t * a[t]
  denom = len(a) * xdot - xsum * xsum
  if(denom == 0.): return [0, 10000]
  aa = (len(a) * ydot - xsum * ysum) / denom
  bb = (xdot * ysum - xdot * xsum) / denom
  ss = 0.
  for t in range(0, len(a)):
    ss += pow((aa * t + bb) - a[t], 2.)
  return [aa, ss]

t = amt = 0
for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  d = float(line.split(",")[0])
  print(d * amt)
  if(t % int(2 * int(sys.argv[1]) / int(sys.argv[2])) == 0):
    p[int(t / int(2 * int(sys.argv[1]) / int(sys.argv[2]))) % len(p)].stdin.close()
    p[int(t / int(2 * int(sys.argv[1]) / int(sys.argv[2]))) % len(p)].kill()
    p[int(t / int(2 * int(sys.argv[1]) / int(sys.argv[2]))) % len(p)] = subprocess.Popen(["p0", str(int(sys.argv[1]))], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  amt = ss = 0
  score = 2000
  for pp in p:
    pp.stdin.write((str(d) + "\n").encode("utf-8"))
    pp.stdin.flush()
    work = pp.stdout.readline().decode("utf-8").split(",")
    walk[ss].append(float(work[2]))
    walk[ss] = walk[ss][- int(sys.argv[3]):]
    tilt[ss].append(minsq(walk[ss])[1])
    tilt[ss] = tilt[ss][- int(sys.argv[3]):]
    lscore = minsq(tilt[ss])[0]
    if(lscore < score):
      score = lscore
      amt   = lscore * float(work[0])
    ss += 1
  sys.stdout.flush()
  t += 1

