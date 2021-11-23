import sys
import subprocess
from PIL import Image
import numpy as np
img = []
for line in sys.stdin:
  try:
    img.append(Image.open(line[:- 1]))
  except:
    pass
pixels = []
out = Image.new("RGB", (img[0].size[0], img[0].size[1]), (256, 256, 256))
m = M = 0.
for x in range(0, img[0].size[0]):
  pixels.append([])
  for y in range(0, img[0].size[1]):
    d = [0., 0., 0.]
    p0 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    p1 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    p2 = subprocess.Popen(sys.argv[1:], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    t = 0
    for idx in range(0, len(img)):
      pp = img[idx].getpixel((x, y))
      if(not isinstance(pp, tuple)):
        pp = [pp, pp, pp]
      p0.stdin.write((str(pp[0]) + "\n").encode("utf-8"))
      p1.stdin.write((str(pp[1]) + "\n").encode("utf-8"))
      p2.stdin.write((str(pp[2]) + "\n").encode("utf-8"))
      p0.stdin.flush()
      p1.stdin.flush()
      p2.stdin.flush()
      t += 1
      if((t - 2) % 3 == 0):
        pp0 = p0.stdout.readline().decode("utf-8").split(",")
        pp1 = p1.stdout.readline().decode("utf-8").split(",")
        pp2 = p2.stdout.readline().decode("utf-8").split(",")
        if(float(pp0[2]) != 0 and float(pp1[2]) != 0 and float(pp2[2]) != 0):
          d = [float(pp0[0]) / float(pp0[2]) / float(pp0[2]),
               float(pp1[0]) / float(pp1[2]) / float(pp1[2]),
               float(pp2[0]) / float(pp2[2]) / float(pp2[2])]
        else:
          d = [0, 0, 0]
    p0.stdin.close()
    p1.stdin.close()
    p2.stdin.close()
    p0.kill()
    p1.kill()
    p2.kill()
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
    pixels[- 1].append(d)
for x in range(0, len(pixels)):
  for y in range(0, len(pixels[x])):
    for idx in range(0, 3):
      pixels[x][y][idx] -= m
      if(M == m or not np.isfinite(pixels[x][y][idx])):
        pixels[x][y][idx]  = 1.
      else:
        pixels[x][y][idx] /= M - m
      pixels[x][y][idx]  = int(255 * pixels[x][y][idx])
    out.putpixel((x, y), tuple(pixels[x][y]))
out.save("./pred.png")

