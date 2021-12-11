import sys
import subprocess
from PIL import Image
import numpy as np
p0 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p1 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
p2 = subprocess.Popen(sys.argv[2:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
for file in sys.stdin:
  norm20 = 0.
  for tt in range(0, int(sys.argv[1])):
    img0 = Image.open(file[:- 1])
    img0 = img0.resize((img0.size[0] * 4, img0.size[1] * 4), Image.LANCZOS)
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
    for x in range(0, w):
      d = (0., 0., 0.)
      for line in range(1, 4 + 1):
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
    if(tt == 0):
      for x in range(0, len(img)):
        for y in range(0, len(img[x])):
          for t in range(0, len(img[x][y])):
            norm20 += abs(img[x][y][t])
      norm20 /= len(img) * len(img[x])
    m = 0.
    M = 255.
    stat = []
    for y in range(h, len(img[0])):
      norm2 = 0.
      for x in range(0, len(img)):
        for t in range(0, len(img[x][y])):
          norm2 += abs(img[x][y][t])
      norm2 /= len(img)
      for x in range(0, len(img)):
        for t in range(0, len(img[x][y])):
          img[x][y][t] = int(img[x][y][t] * norm20 / norm2)
    out = Image.new("RGB", (len(img), len(img[0])))
    for x in range(0, len(img)):
      for y in range(0, len(img[x])):
        out.putpixel((x, y), tuple(img[x][y]))
    out = out.resize((int(len(img) / 4), int(len(img[0]) / 4)), Image.LANCZOS)
    out.save(file[:- 1])

