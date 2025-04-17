#! /usr/bin/env python3
import sys
import io
import struct
import random
import hashlib
import subprocess

# mersenne twister:
rr = random.Random()
# /dev/urandom:
sr = random.SystemRandom()

def ifloat(x, offset = 0):
  try:
    return float(x)
  except:
    try:
      b = x.split("*")
      n = e = 0.
      tbl = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, \
        '8': 8, '9': 9, 'a': 10, 'b': 11, 'c': 12, 'd': 13, 'e': 14, 'f': 15, \
        ' ': -1, '\t': -1, '\n': -1, '-': 16}
      m = False
      for ff in b[0]:
        if(tbl[ff] < 0): continue
        if(tbl[ff] == 16):
          m = True
          continue
        n *= 16
        n += tbl[ff]
      if(m): n = - n
      m = False
      for ff in b[1][2:]:
        if(tbl[ff] < 0): break
        if(tbl[ff] == 16):
          m = True
          continue
        e *= 16
        e += tbl[ff]
      if(m): e = - e
      return n * pow(2., e - offset)
    except:
      pass
  return 0.

def getrand(mm):
  m = abs(mm)
  # if mm < 0, shuffles random methods.
  if(mm < 0):
    return getrand(abs(getrand(m) * 6 * 2))
  # if 6 <= m, divide them.
  if((m / 6) % 2 == 1):
   return getrand(abs(m) % 6) / getrand(abs(m) % 6)
  global rr, sr
  if(m % 6 == 0):
    return rr.uniform(- 1., 1.)
  elif(m % 6 == 1):
    return rr.gauss(0., 1.)
  elif(m % 6 == 2):
    return rr.randint(0, 255) - 127.5
  elif(m % 6 == 3):
    return sr.uniform(- 1., 1.)
  elif(m % 6 == 4):
    return sr.gauss(0., 1.)
  return sr.randint(0, 255) - 127.5

if(len(sys.argv) < 2):
  print("not much arguments")
elif(sys.argv[1][0] == 'r'):
  # N.B. only to ease our mind, scatter initialized states.
  scatter = 1000 + int(getrand(int(sys.argv[2])) * 8)
  for s in range(0, scatter):
    getrand(int(sys.argv[2]))
  while(True):
    print(getrand(int(sys.argv[2])))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'C'):
  import numpy
  for t in range(0, abs(int(sys.argv[2]))):
    if(int(sys.argv[2]) < 0):
      print(numpy.cos(t / float(int(sys.argv[2])) * 2. * numpy.pi * int(sys.argv[3])))
    else:
      if(int(sys.argv[3]) < 0):
        print(- pow((t - abs(int(sys.argv[2])) / 2.), - int(sys.argv[3])))
      else:
        print(  pow((t - abs(int(sys.argv[2])) / 2.),   int(sys.argv[3])))
elif(sys.argv[1][0] == 'n'):
  for t in range(0, abs(int(sys.argv[2]))):
    if(int(sys.argv[2]) < 0):
      print(- ((t % abs(int(sys.argv[3]))) - abs(int(sys.argv[3])) / 2.))
    else:
      print(   (t % abs(int(sys.argv[3]))) - abs(int(sys.argv[3])) / 2.)
elif(sys.argv[1][0] == 'R'):
  while(True):
    a = []
    idx = 0
    for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
      a.extend(struct.pack('f', ifloat(line.split(",")[0])))
      if(abs(int(sys.argv[2])) <= idx): break
      idx += 1
    m = hashlib.sha256()
    m.update(bytearray(a))
    a = m.digest()
    for byte in a:
      print(byte - 127.5)
    sys.stdout.flush()
elif(sys.argv[1][0] == 'c'):
  import numpy
  while(True):
    a = []
    idx = 0
    for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
      a.append(ifloat(line.split(",")[0]))
      if(abs(int(sys.argv[2])) <= idx): break
      idx += 1
    a = numpy.fft.ifft(a)
    for aa in a:
      print(aa.real)
elif(sys.argv[1][0] == 'w'):
  cnt = bd = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = ifloat(line.split(",")[0])
    if(float(sys.argv[2]) < abs(d - bd)):
      if(int(sys.argv[3]) < cnt):
        print(d)
        sys.stdout.flush()
        cnt = 0
      cnt += 1
      bd   = d
elif(sys.argv[1][0] == 'S'):
  t = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    if(t < int(sys.argv[2])):
      pass
    else:
      print(line[:- 1])
      sys.stdout.flush()
      t = int(sys.argv[2])
    t += 1
elif(sys.argv[1][0] == 'a'):
  d = [0.]
  M = [0.]
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    MM = M[0]
    for MMM in M[1:]:
      MM += MMM
    d.append(ifloat(line.split(",")[0]))
    print(MM * d[- 1])
    # N.B. average shift they kills some normal jammers.
    #      this takes return to origin, then, return to average.
    d  = d[- int(sys.argv[2]):]
    dd = d[0]
    for ddd in d[1:]:
      dd += ddd
    M.append(dd)
    M  = M[- int(sys.argv[3]):]
    sys.stdout.flush()
elif(sys.argv[1][0] == 'd'):
  bd = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d  = ifloat(line.split(",")[0])
    print(d - bd)
    bd = d
    sys.stdout.flush()
elif(sys.argv[1][0] == 's'):
  s = []
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = line.split(",")
    if(len(s) < len(d)):
      for t in range(0, len(d) - len(s)):
        s.append(0.)
    ss = []
    for t in range(0, len(d)):
      s[t] += ifloat(d[t])
      ss.append(str(s[t]))
    print(",".join(ss))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'i'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = ifloat(line.split(",")[0])
    if(d != 0.):
      print(1. / d)
      sys.stdout.flush()
elif(sys.argv[1][0] == 'l'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = line[:- 1].split(",")
    b = []
    for t in sys.argv[2:]:
      b.append(d[int(t)])
    print(",".join(b))
    sys.stdout.flush()
elif(sys.argv[1][0] == 't'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print(ifloat(line.split(",")[0]) * float(sys.argv[2]))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'T'):
  tt = 1
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print(ifloat(line.split(",")[0]) * pow(2., tt / float(sys.argv[2])))
    tt += 1
    sys.stdout.flush()
elif(sys.argv[1][0] == 'F'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    b = hex(int(ifloat(line.split(",")[0]) * pow(2., int(sys.argv[2])) ))
    if(b[0] == '-'): print(b[0] + b[3:] + "*2^-" + hex(int(sys.argv[2]))[2:])
    else: print(b[2:] + "*2^-" + hex(int(sys.argv[2]))[2:])
    sys.stdout.flush()
elif(sys.argv[1][0] == 'k'):
  t = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    if(t % int(sys.argv[2]) == 0):
      print(line[:- 1])
      sys.stdout.flush()
      t = 0
    t += 1
elif(sys.argv[1][0] == 'P'):
  from PIL import Image
  mC  = []
  ctr = 0
  for line in sys.stdin:
    if(len(line.split("[")) <= 1): continue
    ff = line.split("[")[1].split("]")[0].split(",")
    print(ff)
    sq = int(pow(float(len(ff)), .5))
    im = Image.new("RGB", (sq, sq), (256, 256, 256))
    x = y = 0
    for f in ff:
      v = int(float(f) * 127. + 128)
      im.putpixel((x, y), (v, v, v))
      x += 1
      if(sq <= x):
        x = 0
        y += 1
        if(sq <= y):
          break
      im.save("./rand_png-" + str(ctr) + ".png")
    ctr += 1
elif(sys.argv[1][0] == 'm'):
  import numpy
  import mido
  from mido import Message, MidiFile, MidiTrack, MetaMessage
  tbl = []
  mid = MidiFile()
  tbl0 = [0, 2, 4, 5, 7, 9, 11]
  for u in range(0, 2 * len(tbl0)):
    # Thanks to google with search word midi C value, 60 is one of a C.
    tbl.append(60 + tbl0[u % len(tbl0)] + int(u / len(tbl0)) * 12)
  mC = []
  ctr = 0
  bw  = []
  track = []
  for line in sys.stdin:
    if(len(line.split("[")) <= 1): continue
    ff = line.split("[")[1].split("]")[0].split(",")
    if(len(track) <= 0):
      for s in range(0, len(ff)):
        # Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
        trk = MidiTrack()
        trk.append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(70)))
        # cf.https://ja.wikipedia.org/wiki/General_MIDI
        #trk.append(Message('program_change', program = 117))
        track.append(trk)
        mid.tracks.append(trk)
    print(ff, bw)
    if(len(bw) <= 0):
      bw = ff
      continue
    flg = True
    for w in ff:
      if(abs(float(w)) > 1. / 20):
        flg = False
        break
    for w in bw:
      if(abs(float(w)) > 1. / 20):
        flg = False
        break
    if(flg): continue
    idx = 0
    bb  = []
    for w in range(0, len(ff)):
      if(len(bb) <= idx): bb.append(int(len(tbl) / 2))
      bb[idx] += abs(numpy.arctan(abs(numpy.tan(float(ff[w]) * 6))) * 6) - 3
      f = tbl[int(bb[idx]) % int(len(tbl) / len(ff)) + idx * int(len(tbl) / len(ff))]
      idx += 1
      track[w].append(Message('note_on', note=f, velocity=127, time=0))
      track[w].append(Message('note_off', note=f, time=(120 * int(abs(numpy.arctan(abs(numpy.tan(float(bw[w])))) * 3) + 1)) ))
    bw = []
  mid.save('rand_correct.mid')
elif(sys.argv[1][0] == 'h'):
  for line in sys.stdin:
    if(len(line.split("[")) <= 1): continue
    for w in line.split("[")[1].split("]")[0].split(","):
      print(float(w))
elif(sys.argv[1][0] == 'e'):
  import numpy
  mC = []
  loop = - 1
  if(2 < len(sys.argv)):
    loop = int(sys.argv[2])
  for line in sys.stdin:
    if(len(line.split("[")) <= 1): continue
    ff = line.split("[")[1].split("]")[0].split(",")
    if(loop <= 0):
      r = loop
      loop = 0
      for v in ff:
        loop += abs(r * float(v))
      loop = int(loop)
      continue
    if(len(mC) < len(ff)):
      mC.append(ff)
      continue
    ffu = ff
    for vvv in range(0, loop):
      ff = ffu
      ffu = []
      for u in range(0, len(mC)):
        buf = 0.
        for v in range(0, len(ff)):
          buf += float(ff[v]) * float(mC[u][v])
        ffu.append(numpy.tan(buf))
      ffuu = []
      for w in ffu[1:]:
        ffuu.append(str(float(w) * float(ffu[0])))
      print(len(ffuu), ": [", ", ".join(ffuu), "]")
    mC = []
elif(sys.argv[1][0] == 'E'):
  for line in sys.stdin:
    if(len(line.split("[")) <= 1): continue
    ff = line.split("[")[1].split("]")[0].split(",")
    for f in ff:
      f = str(float(f) * 1e4)
    print(len(ff), ": [", ", ".join(ff), "]")
elif(sys.argv[1][0] == 'v'):
  a = []
  for line in sys.stdin:
    a.append(line[:- 1])
  for t in range(0, len(a)):
    print(a[- 1 - t])
elif(sys.argv[1][0] == 'b'):
  a = []
  for line in sys.stdin:
    a.append(float(line[:- 1]))
  l = int(pow(len(a), .5))
  for t in range(0, l):
    s = 0.
    for aa in a[t * l : (t + 1) * l]:
      s += aa
    b  = sorted(a[t * l : (t + 1) * l])
    s /= len(b)
    c  = 0.
    for aa in b:
      c += (aa - s) * (aa - s)
    c /= len(b)
    print(s, c, b[int(len(b) / 2)], b[int(len(b) / 4)], b[int(len(b) * 3 / 4)])
  print("---")
  s = 0.
  for aa in a:
    s += aa
  a  = sorted(a)
  s /= len(a)
  c  = 0.
  for aa in a:
    c += (aa - s) * (aa - s)
  c /= len(a)
  print(s, c, a[int(len(a) / 2)], a[int(len(a) / 4)], a[int(len(a) * 3 / 4)])
elif(sys.argv[1][0] == 'j'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = ifloat(line.split(",")[0])
    print(d * getrand(int(sys.argv[2])))
    sys.stdout.flush()
elif(sys.argv[1][0] == '0'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print(line[:- 1])
    print(0)
    sys.stdout.flush()
elif(sys.argv[1][0] == '-'):
  t = 1
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print(t * ifloat(line[:- 1]))
    t = - t
    sys.stdout.flush()
elif(sys.argv[1][0] == 'I'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print("num_t(", int(ifloat(line[:- 1])), ") ,")
    sys.stdout.flush()
elif(sys.argv[1][0] == ','):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print("num_t(", line[:- 1], ") ,")
    sys.stdout.flush()
elif(sys.argv[1][0] == '<'):
  for fn in sys.argv[2:]:
    for line in open(fn, mode = "r"):
      print("\"" + line[:- 1] + "\\n\"")
    print(",")
    sys.stdout.flush()
elif(sys.argv[1][0] == 'o'):
  a = []
  M = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    a.append(line[:- 1].split(",")[0])
    try:
      e = 0
      tbl = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, \
        '8': 8, '9': 9, 'a': 10, 'b': 11, 'c': 12, 'd': 13, 'e': 14, 'f': 15, \
        ' ': -1, '\t': -1, '\n': -1, '-': 16}
      m = False
      for ff in line[:- 1].split(",")[0].split("*")[1][2:]:
        if(tbl[ff] < 0): continue
        if(tbl[ff] == 16):
          m = True
          continue
        e *= 16
        e += tbl[ff]
      if(m): e = - e
      M = max(M, e)
    except:
      pass
  for line in a:
    print(ifloat(line, M))
elif(sys.argv[1][0] == 'z'):
  bd = []
  for t in range(0, int(sys.argv[2])):
    bd.append("0")
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print(line[:- 1].split(",")[0], ",", ",".join(bd))
    d = [line[:- 1].split(",")[0]]
    d.extend(bd[:- 1])
    bd = d
    sys.stdout.flush()
elif(sys.argv[1][0] == 'A'):
  bd = []
  for t in range(0, int(sys.argv[2])):
    bd.append(0)
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    for t in range(1, len(bd) - 1):
      bd[- t] = bd[- t - 1]
    bd[0] = ifloat(line[:- 1].split(",")[0])
    dd = 0
    da = 0
    for t in range(0, len(bd)):
      dd += bd[t] * float(len(bd) - t)
      da += float(len(bd) - t)
    print(dd / da)
elif(sys.argv[1][0] == 'N'):
  bd = 0.
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d  = ifloat(line.split(",")[0])
    print((bd + d) / 2.)
    print(d)
    bd = d
    sys.stdout.flush()
elif(sys.argv[1][0] == 'M'):
  for x in range(0, 729):
    subprocess.call(["sh", "-c", "p2prng | python3 " + sys.argv[0] + " l 1 | head -n " + str(int(sys.argv[2])) + " | catgr 5 | python3 " + sys.argv[0] + " E | python3 " + sys.argv[0] + " e | python3 " + sys.argv[0] + " e | python3 " + sys.argv[0] + " e | tail -n 20"])
elif(sys.argv[1][0] == 'f'):
  d = []
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d.append(line.split(",")[0])
    if(len(d) % int(sys.argv[2]) == 0):
      print(len(d), ": [", ",".join(d), "]")
      sys.stdout.flush()
      d = []
elif(sys.argv[1][0] == 'u'):
  import numpy
  d = []
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    df = line.split(",")
    d.append([])
    for dd in df:
      d[- 1].append(ifloat(dd))
    d = d[max(- len(d), - len(df)):]
    if(len(df) <= len(d)):
      fd = []
      fe = []
      for t in range(0, len(d)):
        fd.append(numpy.fft.fft(d[t]))
        for s in range(0, len(fd[t])):
          fd[t][s] *= - 2.j * numpy.pi * s / float(len(fd[- 1]))
        fd[t] = numpy.fft.ifft(fd[t]).real
      for t in range(0, len(d[0])):
        fe.append([])
        for s in range(0, len(d)):
          fe[t].append(d[s][t])
        for s in range(0, len(fe[t])):
          fe[t][s] *= - 2.j * numpy.pi * s / float(len(fe[- 1]))
        fe[t] = numpy.fft.ifft(fe[t]).real
      ff = []
      for t in range(0, len(d[- 1])):
        if(d[- 1][t] < 0):
          ff.append(str(- (fd[- 1][t] * fd[- 1][t] + fe[- 1][t] * fe[- 1][t] + d[- 1][t] * d[- 1][t]) / (2. * numpy.pi * 2. * numpy.pi + 1) ))
        else:
          ff.append(str(  (fd[- 1][t] * fd[- 1][t] + fe[- 1][t] * fe[- 1][t] + d[- 1][t] * d[- 1][t]) / (2. * numpy.pi * 2. * numpy.pi + 1) ))
      print(",".join(ff))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'B'):
  p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = line[:- 1].split(",")[0]
    p.stdin.write((d + "\n").encode("utf-8"))
    p.stdin.flush()
    D = p.stdout.readline().decode("utf-8")[:- 1].split(",")[0]
    print(D, ", ", d)
    sys.stdout.flush()
elif(sys.argv[1][0] == 'g'):
  avg = 0.
  pd  = []
  for t in range(0, int(sys.argv[2])):
    pd.append(0.)
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d    = ifloat(line.split(",")[0])
    if(d == 0.):
      print(d * pd[0], ",", d - pd[0], ",", 0.)
    else:
      print(d * pd[0], ",", d - pd[0], ",", pd[0] / d + 1.)
    avg += d
    pd = pd[1:]
    pd.append(- avg)
    sys.stdout.flush()
elif(sys.argv[1][0] == 'G'):
  f = []
  for ff in sys.argv[2:]:
    f.append(open(ff, 'r', encoding = "utf-8"))
  while(True):
    d = 0.
    for g in f:
      l  = g.readline()
      if(l == ""): exit(0)
      d += ifloat(l.split(",")[0])
    d /= len(f)
    print(d)
    sys.stdout.flush()
elif(sys.argv[1][0] == 'L'):
  f = []
  for ff in sys.argv[2:]:
    f.append(open(ff, 'r', encoding = "utf-8"))
  while(True):
    d = []
    for g in f:
      l = g.readline()[:- 1]
      if(l == ""): exit(0)
      d.extend(l.split(","))
    print(",".join(d))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'x'):
  for line in sys.stdin:
    for c in line:
      if(c == '1'):
        print(1)
      elif(c == '0'):
        print(- 1)
elif(sys.argv[1][0] == 'p'):
  p0 = subprocess.Popen([sys.argv[2]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  p1 = subprocess.Popen([sys.argv[2]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  q0 = subprocess.Popen([sys.argv[3]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  q1 = subprocess.Popen([sys.argv[3]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  r0 = subprocess.Popen([sys.argv[4]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  r1 = subprocess.Popen([sys.argv[4]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  t = 1
  M = D0 = bD = S = SS = S0 = S1 = b0 = b1 = 0
  for line in io.open(sys.stdin.fileno(), 'r', encoding = "utf-8", closefd = False):
    strd = line[:- 1].split(",")[0].split(" ")[- 1]
    if(len(strd) <= 0):
      strd = line[:- 1].split(",")[0].split(" ")[- 2]
    D0 = ifloat(strd)
    D  = D0 * M
    if(t < 0):
      if(strd[0] == "-"):
        stre = strd[1:]
      else:
        stre = "-" + strd
    else:
      stre = strd
    p0.stdin.write((strd + "\n").encode("utf-8"))
    p1.stdin.write((stre + "\n").encode("utf-8"))
    p0.stdin.flush()
    p1.stdin.flush()
    pr0 = p0.stdout.readline().decode("utf-8")[:- 1].split(",")
    pr1 = p1.stdout.readline().decode("utf-8")[:- 1].split(",")
    q0.stdin.write((pr0[0] + "," + pr0[1] + "\n").encode("utf-8"))
    q1.stdin.write((pr1[0] + "," + pr1[1] + "\n").encode("utf-8"))
    q0.stdin.flush()
    q1.stdin.flush()
    qr0 = q0.stdout.readline().decode("utf-8")[:- 1].split(",")
    qr1 = q1.stdout.readline().decode("utf-8")[:- 1].split(",")
    r0.stdin.write((qr0[0] + "\n").encode("utf-8"))
    r1.stdin.write((qr1[0] + "\n").encode("utf-8"))
    r0.stdin.flush()
    r1.stdin.flush()
    rr0 = r0.stdout.readline().decode("utf-8")[:- 1].split(",")
    rr1 = r1.stdout.readline().decode("utf-8")[:- 1].split(",")
    # N.B. ok:
    # print(- S0 * (ifloat(rr0[0]) - b0), ",", - S1 * (ifloat(rr1[0]) - b1))
    t = - t
    M0  = ifloat(pr0[1]) * ifloat(qr0[2]) * ifloat(rr0[1])
    M1  = ifloat(pr1[1]) * ifloat(qr1[2]) * ifloat(rr1[1])
    # ok: (- s0 * S0 * M0 * d + s0 * S0 * b0 - s1 * S1 * M1 * t * d + s1 * S1 * b1 * t)
    # ==  (- (s0 * S0 * M0 + s1 * t * S0 * M1) +
    #       (s0 * S0 * b0 + s1 * S1 * b1 * t))
    S0 += ifloat(rr0[0]) - b0
    S1 += ifloat(rr1[0]) - b1
    s0  = S1 * b1 * t
    s1  = S0 * b0
    if(0 < s0 * s1):
      s0  = abs(s0)
      s1  = abs(s1)
    else:
      if(abs(s0) < abs(s1)):
        s0 = - abs(s0)
        s1 =   abs(s1)
      else:
        s0 =   abs(s0)
        s1 = - abs(s1)
    N   = pow(s0 * s0 + s1 * s1, .5)
    if(N != 0):
      M = - (s0 * S0 * M0 + s1 * S1 * M1) / N
    else:
      M = 0
    b0   = ifloat(rr0[0])
    b1   = ifloat(rr1[0])
    SS1  = SS + D0
    # N.B. 1x all invariant is controlled cond,
    #      2x only single state,  1x null state, 
    #      2-way 3x making invariant as measurement insertion.
    #      their measurement condition starts binary states either,
    #      ends if we can write down them as a binary tree.
    # N.B. we make the hypothesis the original stream is deterministic
    #      single function with long internal state generated one.
    # N.B. in such of the case, we can shirk them to 3 of the numerical pillar
    #      start with, the internal states can have many much of them
    #      however after words they can be treated as such one.
    # N.B. so the binary tree copied structure says the relation to 3 of their
    #      pillars and the produced stream relation.
    # N.B. this might collect all condition, but isn't checked carefully.
    # N.B. however, the PRNG can blend new states in any which case adding to
    #      original stream the predictor must get them by the stream.
    #      so any occasion, PRNG has slight profitable condition.
    print(D, ",", bD * D0, ",", SS * D0, ",", D0, ",", ifloat(pr0[0]), ",", ifloat(pr1[0]), ",", ifloat(qr0[0]), ",", ifloat(qr1[0]), ",", ifloat(rr0[0]), ",", ifloat(rr1[0]), ",", M, ",", D0, ",", SS1, ",", 1., ",", ifloat(pr0[1]), ",", ifloat(pr1[1]), ",", ifloat(qr0[2]), ",", ifloat(qr1[2]), ",", ifloat(rr0[1]), ",", ifloat(rr1[1]), ",", strd, ",", stre)
    bD   = D0
    SS   = SS1
    sys.stdout.flush()
elif(sys.argv[1] == 'q'):
  # Beating prediction stream:
  p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  M = t = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = 'utf-8', closefd = False):
    d = ifloat(line[:- 1].split(",")[0])
    p.stdin.write((str(d) + "\n").encode("utf-8"))
    p.stdin.flush()
    if(M * pow(- 1, t) < 0):
    # N.B. following don't affect better to scatter.
    #if(M * getrand(3) < 0):
      print(  d)
    else:
      print(- d)
    M = ifloat(p.stdout.readline().decode("utf-8")[:- 1].split(",")[0])
    t += 1
    t  = t % 2
    sys.stdout.flush()
elif(sys.argv[1] == '2'):
  # N.B. Stack 2 layers with hypothesis first layer attack can cause
  #      original stream continuity shift.
  p = subprocess.Popen(["python3", sys.argv[0], "p", sys.argv[2], sys.argv[3], sys.argv[4]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  q = subprocess.Popen([sys.argv[4]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  r = subprocess.Popen(["python3", sys.argv[0], "p", sys.argv[2], sys.argv[3], sys.argv[4]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = 'utf-8', closefd = False):
    p.stdin.write(line.encode("utf-8"))
    q.stdin.write(line.encode("utf-8"))
    p.stdin.flush()
    q.stdin.flush()
    rq = q.stdout.readline().decode("utf-8")[:- 1].split(",")
    r.stdin.write((rq[0] + "\n").encode("utf-8"))
    r.stdin.flush()
    rp = p.stdout.readline().decode("utf-8")[:- 1].split(",")
    rr = r.stdout.readline().decode("utf-8")[:- 1].split(",")
    ra = []
    for t in range(0, 10):
      ra.append(rp[t])
      ra.append(rr[t])
    for t in range(10, 20):
      ra.append(rp[t])
      ra.append(str(ifloat(rr[t]) * ifloat(rq[1])))
    ra.append(rp[20])
    ra.append(rr[20])
    ra.append(rp[21])
    ra.append(rr[21])
    print(",".join(ra))
    sys.stdout.flush()
elif(sys.argv[1] == 'Z'):
  # N.B. normalize summation output on each column.
  M = []
  d = []
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = 'utf-8', closefd = False):
    d.append(line[:- 1].split(","))
    if(len(M) < len(d[- 1])):
      dM = len(d[- 1]) - len(M)
      for t in range(0, dM):
        M.append(0.)
    for t in range(0, len(M)):
      if(M[t] < abs(ifloat(d[- 1][t]))):
        M[t] = abs(ifloat(d[- 1][t]))
  for t in range(0, len(M)):
    if(M[t] == 0): M[t] = 1.
  for line in d:
    s = []
    for t in range(0, len(line)):
      s.append(str(ifloat(line[t]) / M[t]))
    print(",".join(s))
elif(sys.argv[1] == 'y'):
  # Condorcet jury with original intensity.
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = 'utf-8', closefd = False):
    d = line.split(",")
    c = 0
    a = []
    for t in d:
      a.append(ifloat(t))
      if(t[0] == '-' or t[1] == '-'):
        c -= 1
      else:
        c += 1
    a = sorted(a)
    # N.B. twisted works well because output is targetted into control case.
    if(c == 0):
      if(len(a) % 2 == 0):
        print((a[int(len(a) / 2)] + a[int(len(a) / 2) - 1]) / 2.)
      else:
        print(a[int(len(a) / 2)])
    elif(0 < c):
      print(a[0])
    else:
      print(a[- 1])
    sys.stdout.flush()
elif(sys.argv[1] == 'Q'):
  t = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = 'utf-8', closefd = False):
    d = line.split(",")
    n2p = 0
    n2n = 0
    for s in range(1, len(d)):
      n2n += pow(ifloat(d[s]), 2.)
      if(t % (len(d) - 1) + 1 != s):
        n2p += pow(ifloat(d[s]), 2.)
    if(n2n == 0.):
      print(0.)
      continue
    # N.B. Cyclic out with complemental weight.
    if(ifloat(d[t % (len(d) - 1) + 1]) * pow(n2p / n2n, .5) * pow(- 1, t) < 0):
    # N.B. following don't affect better to scatter.
    #if(p * getrand(3) < 0):
      print(  ifloat(d[0]))
    else:
      print(- ifloat(d[0]))
    t += 1

