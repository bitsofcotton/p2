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
        if(tbl[ff] < 0): continue
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
  # N.B.: only to ease our mind, scatter initialized states.
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
  s = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    s += ifloat(line.split(",")[0])
    print(s)
    sys.stdout.flush()
elif(sys.argv[1][0] == 'i'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = ifloat(line.split(",")[0])
    if(d != 0.):
      print(1. / d)
      sys.stdout.flush()
elif(sys.argv[1][0] == 'l'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print(line[:- 1].split(",")[int(sys.argv[2])])
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

