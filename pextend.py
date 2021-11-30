import sys
import subprocess
from PIL import Image
import numpy as np
stp  = int(sys.argv[1])
img0 = Image.open(sys.stdin.readline()[:- 1])
w    = img0.size[0]
h    = img0.size[1]
img  = []
for x in range(0, w):
  img.append([])
  for y in range(0, h):
    pp = img0.getpixel((x, y))
    if(not isinstance(pp, tuple) or len(pp) <= 1):
      pp = (pp, pp, pp)
    elif(len(pp) < 3):
      pp = (pp[0], pp[1 % len(pp)], pp[2 % len(pp)])
    img[- 1].append(list(pp))
p0 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p1 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p2 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
for x in range(0, w):
  d = (0., 0., 0.)
  for line in range(1, stp + 1):
    lidx = int(h / line)
    for idx in range(0, lidx):
      p0.stdin.write((str(img[x][h + (idx - lidx + 1) * line - 1][0]) + "\n").encode("utf-8"))
      p1.stdin.write((str(img[x][h + (idx - lidx + 1) * line - 1][1]) + "\n").encode("utf-8"))
      p2.stdin.write((str(img[x][h + (idx - lidx + 1) * line - 1][2]) + "\n").encode("utf-8"))
      p0.stdin.flush()
      p1.stdin.flush()
      p2.stdin.flush()
      if((idx - 2) % 3 == 0):
        pp0 = p0.stdout.readline().decode("utf-8").split(",")
        pp1 = p1.stdout.readline().decode("utf-8").split(",")
        pp2 = p2.stdout.readline().decode("utf-8").split(",")
        if(4 < len(pp0) and 4 < len(pp1) and 4 < len(pp2) and \
           float(pp0[4]) != 0 and float(pp1[4]) != 0 and float(pp2[4]) != 0):
          d = (float(pp0[1]) * float(pp0[3]) / float(pp0[4]) / float(pp0[4]) / 2. + img[x][h - 1][0],
               float(pp1[1]) * float(pp1[3]) / float(pp1[4]) / float(pp1[4]) / 2. + img[x][h - 1][1],
               float(pp2[1]) * float(pp2[3]) / float(pp2[4]) / float(pp2[4]) / 2. + img[x][h - 1][2] )
        else:
          d = (0, 0, 0)
        if(int(h / (line + 1)) - idx < 3):
          break
    d = list(d)
    for t in range(0, len(d)):
      if(not np.isfinite(d[t])):
        d[t] = 0.
    img[x].append(d)
norm20 = 0.
for y in range(0, h):
  for x in range(0, w):
    for t in range(0, len(img[x][y])):
      norm20 += abs(img[x][y][t])
norm20 /= h * len(img) / w
m = 0.
M = 255.
stat = []
for y in range(h, len(img[0])):
  norm2 = 0.
  for x in range(0, len(img)):
    for t in range(0, len(img[x][y])):
      norm2 += abs(img[x][y][t])
  for x in range(0, len(img)):
    for t in range(0, len(img[x][y])):
      img[x][y][t] *= pow(norm20 / norm2, .5)
print("P3")
print(w, " ", len(img[0]))
print(65535)
for y in range(0, len(img[0])):
  for x in range(0, w):
    for idx in range(0, 3):
      print(int(65535 * max(0., min(1., (img[x][y][idx] - m) / (M - m)))))

