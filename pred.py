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
m = M = 0.
def ps(x, p):
  if(not np.isfinite(x)): return 0.
  elif(x < 0): return - pow(- x, p)
  return pow(x, p)
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
          d = (ps(float(pp0[1]) * float(pp0[3]), .5) / float(pp0[4]) / 2. + dimg[idx][x][y][0],
               ps(float(pp1[1]) * float(pp1[3]), .5) / float(pp1[4]) / 2. + dimg[idx][x][y][1],
               ps(float(pp2[1]) * float(pp2[3]), .5) / float(pp2[4]) / 2. + dimg[idx][x][y][2] )
        else:
          d = (0, 0, 0)
        if(len(dimg) - idx - 1 < 3):
          break
    print(d)
    if(np.isfinite(d[0])):
      M = max(d[0], M)
      m = min(d[0], m)
    if(np.isfinite(d[1])):
      M = max(d[1], M)
      m = min(d[1], m)
    if(np.isfinite(d[2])):
      M = max(d[2], M)
      m = min(d[2], m)
    pixels[- 1].append(list(d))
out = Image.new("RGB", (w, h), (256, 256, 256))
for x in range(0, w):
  for y in range(0, h):
    for idx in range(0, 3):
      pixels[x][y][idx] -= m
      if(M == m or not np.isfinite(pixels[x][y][idx])):
        pixels[x][y][idx]  = 1.
      else:
        pixels[x][y][idx] /= M - m
      pixels[x][y][idx]  = int(255 * pixels[x][y][idx])
    out.putpixel((x, y), tuple(pixels[x][y]))
out.save("./pred.png")

