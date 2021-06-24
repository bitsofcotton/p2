from PIL import Image
import subprocess
import sys
import random
import numpy as np

def savePng(ff, ctr):
  sq = int(pow(float(len(ff)), .5))
  im = Image.new("RGB", (sq, sq), (256, 256, 256))
  norm = 0.
  for f in ff:
    norm += float(f) * float(f)
  norm = pow(norm, .5)
  x = y = 0
  for f in ff:
    v = int(float(f) * 127. / norm + 128)
    im.putpixel((x, y), (v, v, v))
    x += 1
    if(sq <= x):
      x = 0
      y += 1
      if(sq <= y):
        break
  im.save("./rand_png-" + str(ctr) + ".png")
  return

mA  = []
mC  = []
ms  = 0
ctr = 0
for line in sys.stdin:
  if(len(line.split("[")) <= 1): continue
  ff = line.split("[")[1].split("]")[0].split(",")
  if(len(sys.argv) <= 1):
    savePng(ff, ctr)
    ctr += 1
  else:
    if(ms == 0):
      ms  = int(np.log(len(ff)) / np.log(2.))
      while(ms != 0):
        if(len(ff) < np.exp(ms * np.log(2.))):
          break
        ms += 1
      ms -= 1
    if(len(mC) < ms):
      mC.append(ff)
      continue
    elif(len(mA) < len(ff) - ms):
      mA.append(ff)
      continue
    for s in range(0, int(sys.argv[1])):
      ff[0] = float(s) / float(sys.argv[1])
      ff[1] = 1.
      tt = []
      for u in range(0, len(mA)):
        tt.append(np.tan(float(ff[u])))
      for u in range(0, len(mC)):
        buf = 0.
        for v in range(0, len(ff)):
          buf += float(ff[v]) * float(mC[u][v])
        tt.append(np.tan(buf))
      ffu = []
      for u in range(0, len(mA)):
        ffu.append(0.)
        for v in range(0, len(mA[u])):
          ffu[- 1] += float(tt[v]) * float(mA[u][v])
      savePng(ffu, s)
    break

