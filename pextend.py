import sys
import subprocess
from PIL import Image
import numpy as np

def sgn(x):
  if(x < 0): return - 1
  elif(x > 0): return 1
  return 0

p0 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p1 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p2 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
P0 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
P1 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
P2 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
q0 = subprocess.Popen(["p0", sys.argv[4]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
q1 = subprocess.Popen(["p0", sys.argv[4]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
q2 = subprocess.Popen(["p0", sys.argv[4]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
Q0 = subprocess.Popen(["p0", sys.argv[4]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
Q1 = subprocess.Popen(["p0", sys.argv[4]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
Q2 = subprocess.Popen(["p0", sys.argv[4]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
for file in sys.stdin:
  for tt in range(0, int(sys.argv[1])):
    img0 = Image.open(file[:- 1])
    w    = img0.size[0]
    h    = img0.size[1]
    img  = []
    jmg  = []
    for x in range(0, w):
      img.append([])
      jmg.append([])
      for y in range(0, h):
        pp = img0.getpixel((x, y))
        if(not isinstance(pp, tuple) or len(pp) <= 1):
          pp = (pp, pp, pp)
        elif(len(pp) < 3):
          pp = (pp[0], pp[1 % len(pp)], pp[2 % len(pp)])
        img[- 1].append(list(pp))
        qq = (1. / (pp[0] + 1.), 1. / (pp[1] + 1.), 1. / (pp[2] + 1.))
        jmg[- 1].append(list(qq))
    for x in range(0, w):
      d = (0., 0., 0.)
      for line in range(1, 4 + 1):
        lidx = int(h / line)
        for idx in range(0, lidx):
          p0.stdin.write((str(img[x][h + (idx - lidx + 1) * line - 1][0]) + "\n").encode("utf-8"))
          p1.stdin.write((str(img[x][h + (idx - lidx + 1) * line - 1][1]) + "\n").encode("utf-8"))
          p2.stdin.write((str(img[x][h + (idx - lidx + 1) * line - 1][2]) + "\n").encode("utf-8"))
          P0.stdin.write((str(jmg[x][h + (idx - lidx + 1) * line - 1][0]) + "\n").encode("utf-8"))
          P1.stdin.write((str(jmg[x][h + (idx - lidx + 1) * line - 1][1]) + "\n").encode("utf-8"))
          P2.stdin.write((str(jmg[x][h + (idx - lidx + 1) * line - 1][2]) + "\n").encode("utf-8"))
          p0.stdin.flush()
          p1.stdin.flush()
          p2.stdin.flush()
          P0.stdin.flush()
          P1.stdin.flush()
          P2.stdin.flush()
          if(0 < idx):
            q0.stdin.write((str(abs(img[x][h + (idx - lidx + 1) * line - 1][0] - img[x][h + (idx - lidx) * line - 1][0])) + "\n").encode("utf-8"))
            q1.stdin.write((str(abs(img[x][h + (idx - lidx + 1) * line - 1][1] - img[x][h + (idx - lidx) * line - 1][1])) + "\n").encode("utf-8"))
            q2.stdin.write((str(abs(img[x][h + (idx - lidx + 1) * line - 1][2] - img[x][h + (idx - lidx) * line - 1][2])) + "\n").encode("utf-8"))
            Q0.stdin.write((str(abs(jmg[x][h + (idx - lidx + 1) * line - 1][0] - jmg[x][h + (idx - lidx) * line - 1][0])) + "\n").encode("utf-8"))
            Q1.stdin.write((str(abs(jmg[x][h + (idx - lidx + 1) * line - 1][1] - jmg[x][h + (idx - lidx) * line - 1][1])) + "\n").encode("utf-8"))
            Q2.stdin.write((str(abs(jmg[x][h + (idx - lidx + 1) * line - 1][2] - jmg[x][h + (idx - lidx) * line - 1][2])) + "\n").encode("utf-8"))
            q0.stdin.flush()
            q1.stdin.flush()
            q2.stdin.flush()
            Q0.stdin.flush()
            Q1.stdin.flush()
            Q2.stdin.flush()
          if((idx - 2) % 3 == 0):
            pp0 = p0.stdout.readline().decode("utf-8").split(",")
            pp1 = p1.stdout.readline().decode("utf-8").split(",")
            pp2 = p2.stdout.readline().decode("utf-8").split(",")
            PP0 = P0.stdout.readline().decode("utf-8").split(",")
            PP1 = P1.stdout.readline().decode("utf-8").split(",")
            PP2 = P2.stdout.readline().decode("utf-8").split(",")
            if(0 < idx):
              qq0 = q0.stdout.readline().decode("utf-8").split(",")
              qq1 = q1.stdout.readline().decode("utf-8").split(",")
              qq2 = q2.stdout.readline().decode("utf-8").split(",")
              QQ0 = Q0.stdout.readline().decode("utf-8").split(",")
              QQ1 = Q1.stdout.readline().decode("utf-8").split(",")
              QQ2 = Q2.stdout.readline().decode("utf-8").split(",")
            else:
              qq0 = qq1 = qq2 = QQ0 = QQ1 = QQ2 = 0.
            if(4 < len(pp0) and 4 < len(pp1) and 4 < len(pp2) and \
               float(pp0[4]) != 0 and float(pp1[4]) != 0 and float(pp2[4]) != 0):
              d = ((sgn(float(pp0[1]) * float(pp0[3])) * abs(float(qq0[1])) + \
                img[x][- 1][0] - 1. + \
                1. / (sgn(float(PP0[1]) * float(PP0[3])) * abs(float(QQ0[1])) + \
                      jmg[x][- 1][0]) ) / 2.,
               (sgn(float(pp1[1]) * float(pp1[3])) * abs(float(qq1[1])) + \
                img[x][- 1][1] - 1. + \
                1. / (sgn(float(PP1[1]) * float(PP1[3])) * abs(float(QQ1[1])) + \
                      jmg[x][- 1][1]) ) / 2.,
               (sgn(float(pp2[1]) * float(pp2[3])) * abs(float(qq2[1])) + \
                img[x][- 1][2] - 1. + \
                1. / (sgn(float(PP2[1]) * float(PP2[3])) * abs(float(QQ2[1])) + \
                      jmg[x][- 1][2]) ) / 2.)
            else:
              d = (0, 0, 0)
            if(int(h / (line + 1)) - idx < 3):
              break
          elif(0 < idx):
            q0.stdout.readline()
            q1.stdout.readline()
            q2.stdout.readline()
            Q0.stdout.readline()
            Q1.stdout.readline()
            Q2.stdout.readline()
        d = list(d)
        for t in range(0, len(d)):
          if(not np.isfinite(d[t])):
            d[t] = 0.
        img[x].append(d)
    out = Image.new("RGB", (len(img), len(img[0])))
    for x in range(0, len(img)):
      for y in range(0, len(img[x])):
        for t in range(0, len(img[x][y])):
          img[x][y][t] = max(0, min(255, int(img[x][y][t])))
        out.putpixel((x, y), tuple(img[x][y]))
    out.save(file[:- 1])

