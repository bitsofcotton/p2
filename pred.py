import sys
import subprocess
from PIL import Image
import numpy as np

def sgn(x):
  if(x < 0): return - 1
  elif(x > 0): return 1
  return 0

dimg = []
iimg = []
w = h = 0
for line in sys.stdin:
  try:
    img = Image.open(line[:- 1])
    if(w != 0 and h != 0 and img.size != (w, h)):
      print("NG", img.size[0], w, img.size[1], h)
    w = img.size[0]
    h = img.size[1]
    if(w == 0 or h == 0): continue
    dimg.append([])
    iimg.append([])
    for x in range(0, w):
      dimg[- 1].append([])
      iimg[- 1].append([])
      for y in range(0, h):
        pp = img.getpixel((x, y))
        if(not isinstance(pp, tuple) or len(pp) <= 1):
          pp = (pp, pp, pp)
        elif(len(pp) < 3):
          pp = (pp[0], pp[1 % len(pp)], pp[2 % len(pp)])
        dimg[- 1][- 1].append(pp)
        qq = (1. / (pp[0] + 1.), 1. / (pp[1] + 1.), 1. / (pp[2] + 1.))
        iimg[- 1][- 1].append(qq)
  except:
    pass
pixels = []
p0 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p1 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p2 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
P0 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
P1 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
P2 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
q0 = subprocess.Popen(["p0", sys.argv[3]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
q1 = subprocess.Popen(["p0", sys.argv[3]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
q2 = subprocess.Popen(["p0", sys.argv[3]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
Q0 = subprocess.Popen(["p0", sys.argv[3]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
Q1 = subprocess.Popen(["p0", sys.argv[3]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
Q2 = subprocess.Popen(["p0", sys.argv[3]], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
for x in range(0, w):
  pixels.append([])
  for y in range(0, h):
    d = (0., 0., 0.)
    for idx in range(0, len(dimg)):
      p0.stdin.write((str(dimg[idx][x][y][0]) + "\n").encode("utf-8"))
      p1.stdin.write((str(dimg[idx][x][y][1]) + "\n").encode("utf-8"))
      p2.stdin.write((str(dimg[idx][x][y][2]) + "\n").encode("utf-8"))
      P0.stdin.write((str(iimg[idx][x][y][0]) + "\n").encode("utf-8"))
      P1.stdin.write((str(iimg[idx][x][y][1]) + "\n").encode("utf-8"))
      P2.stdin.write((str(iimg[idx][x][y][2]) + "\n").encode("utf-8"))
      p0.stdin.flush()
      p1.stdin.flush()
      p2.stdin.flush()
      P0.stdin.flush()
      P1.stdin.flush()
      P2.stdin.flush()
      if(0 < idx):
        q0.stdin.write((str(abs(dimg[idx][x][y][0] - dimg[idx - 1][x][y][0])) + "\n").encode("utf-8"))
        q1.stdin.write((str(abs(dimg[idx][x][y][1] - dimg[idx - 1][x][y][1])) + "\n").encode("utf-8"))
        q2.stdin.write((str(abs(dimg[idx][x][y][2] - dimg[idx - 1][x][y][2])) + "\n").encode("utf-8"))
        Q0.stdin.write((str(abs(iimg[idx][x][y][0] - iimg[idx - 1][x][y][0])) + "\n").encode("utf-8"))
        Q1.stdin.write((str(abs(iimg[idx][x][y][1] - iimg[idx - 1][x][y][1])) + "\n").encode("utf-8"))
        Q2.stdin.write((str(abs(iimg[idx][x][y][2] - iimg[idx - 1][x][y][2])) + "\n").encode("utf-8"))
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
          d = (( sgn(float(pp0[1]) * float(pp0[3])) * abs(float(qq0[1])) + \
                dimg[idx][x][y][0] - 1. + \
                1. / (sgn(float(PP0[1]) * float(PP0[3])) * abs(float(QQ0[1])) + \
                      iimg[idx][x][y][0]) ) / 2.,
               (sgn(float(pp1[1]) * float(pp1[3])) * abs(float(qq1[1])) + \
                dimg[idx][x][y][1] - 1. + \
                1. / (sgn(float(PP1[1]) * float(PP1[3])) * abs(float(QQ1[1])) + \
                      iimg[idx][x][y][1]) ) / 2.,
               (sgn(float(pp2[1]) * float(pp2[3])) * abs(float(qq2[1])) + \
                dimg[idx][x][y][2] - 1. + \
                1. / (sgn(float(PP2[1]) * float(PP2[3])) * abs(float(QQ2[1])) + \
                      iimg[idx][x][y][2]) ) / 2.)
        else:
          d = (0, 0, 0)
        if(len(dimg) - idx - 1 < 3):
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
    pixels[- 1].append(d)
print("P3")
print(w, " ", h)
print(65535)
for y in range(0, h):
  for x in range(0, w):
    for idx in range(0, 3):
      print(max(0, min(65535, int(pixels[x][y][idx] * 256))))

