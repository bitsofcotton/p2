import sys
import subprocess
from PIL import Image
import numpy as np
dimg = []
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
    for x in range(0, w):
      dimg[- 1].append([])
      for y in range(0, h):
        pp = img.getpixel((x, y))
        if(not isinstance(pp, tuple) or len(pp) <= 1):
          pp = (pp, pp, pp)
        elif(len(pp) < 3):
          pp = (pp[0], pp[1 % len(pp)], pp[2 % len(pp)])
        dimg[- 1][- 1].append(pp)
  except:
    pass
pixels = []
m  = 0.
M  = 1.
p0 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p1 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p2 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
for x in range(0, w):
  pixels.append([])
  for y in range(0, h):
    d = (0., 0., 0.)
    for idx in range(0, len(dimg)):
      p0.stdin.write((str(dimg[idx][x][y][0]) + "\n").encode("utf-8"))
      p1.stdin.write((str(dimg[idx][x][y][1]) + "\n").encode("utf-8"))
      p2.stdin.write((str(dimg[idx][x][y][2]) + "\n").encode("utf-8"))
      p0.stdin.flush()
      p1.stdin.flush()
      p2.stdin.flush()
      if((idx - 2) % 3 == 0):
        pp0 = p0.stdout.readline().decode("utf-8").split(",")
        pp1 = p1.stdout.readline().decode("utf-8").split(",")
        pp2 = p2.stdout.readline().decode("utf-8").split(",")
        if(4 < len(pp0) and 4 < len(pp1) and 4 < len(pp2) and \
           float(pp0[4]) != 0 and float(pp1[4]) != 0 and float(pp2[4]) != 0):
          d = (float(pp0[1]) * float(pp0[3]) / float(pp0[4]) / float(pp0[4]) / 2. + dimg[idx][x][y][0],
               float(pp1[1]) * float(pp1[3]) / float(pp1[4]) / float(pp1[4]) / 2. + dimg[idx][x][y][1],
               float(pp2[1]) * float(pp2[3]) / float(pp2[4]) / float(pp2[4]) / 2. + dimg[idx][x][y][2] )
        else:
          d = (0, 0, 0)
        if(len(dimg) - idx - 1 < 3):
          break
    d = list(d)
    for t in range(0, len(d)):
      if(not np.isfinite(d[t])):
        d[t] = 0.
      m = min(m, d[t])
      M = max(M, d[t])
    pixels[- 1].append(d)
norm20 = 0.
for y in range(0, h):
  for t in range(0, len(pixels[- 1][y])):
    pixels[- 1][y][t] = (pixels[- 1][y][t] - m) / (M - m)
    norm20 += abs(pixels[- 1][y][t])
norm21 = norm20
for x in range(0, w - 1):
  norm2 = 0.
  for y in range(0, h):
    for t in range(0, len(pixels[x][y])):
      pixels[x][y][t] = (pixels[x][y][t] - m) / (M - m)
      norm2 += abs(pixels[x][y][t])
  if(norm2 == 0.): continue
  for y in range(0, h):
    for t in range(0, len(pixels[x][y])):
      pixels[x][y][t] *= norm20 / norm2
      norm21 += abs(pixels[x][y][t])
norm21 /= len(pixels) * len(pixels[0])
print("P3")
print(w, " ", h)
print(65535)
for y in range(0, h):
  for x in range(0, w):
    for idx in range(0, 3):
      print(int(65535 * pixels[x][y][idx] / norm21))

