import sys
import subprocess

p  = subprocess.Popen(["./p"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
dh = []
t  = 0
s  = 0.
v  = 0.
bt = 0.
for line in sys.stdin:
  dh.append(float(line.split(",")[0]))
  if(t % (int(sys.argv[1]) / int(sys.argv[2])) == 0):
    dh = dh[- int(sys.argv[1]):]
    xsum = xdot = ysum = ydot = 0.
    for u in range(0, len(dh)):
      xsum += u
      ysum += dh[u]
      xdot += u * u
      ydot += u * dh[u]
    if(xdot * len(dh) == xsum * xsum):
      continue
    ms = (ydot * len(dh) - xsum * ysum) / (xdot * len(dh) - xsum * xsum)
    s += ms
    xsum = xdot = ysum = ydot = 0.
    for u in range(len(dh) * (int(sys.argv[2]) - 1) / int(sys.argv[2]), len(dh)):
      xsum += u
      ysum += dh[u]
      xdot += u * u
      ydot += u * dh[u]
    if(xdot * len(dh) == xsum * xsum):
      continue
    ms = (ydot * len(dh) - xsum * ysum) / (xdot * len(dh) - xsum * xsum)
    v += ms * bt
    p.stdin.write(str(s) + "\n")
    work = p.stdout.readline().split(",")[1]
    if(work[0] == "n" or work[1] == "n"):
      bt = 0
    else:
      bt = float(work)
    print v
  t += 1 

