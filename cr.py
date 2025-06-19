#! /usr/bin/env python3
import sys
import io
import struct
import hashlib
import subprocess

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

if(len(sys.argv) < 2):
  print("not much arguments")
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
elif(sys.argv[1][0] == 'f'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print(ifloat(line.split(",")[0]))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'F'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    b = hex(int(ifloat(line.split(",")[0]) * pow(2., int(sys.argv[2])) ))
    if(b[0] == '-'): print(b[0] + b[3:] + "*2^-" + hex(int(sys.argv[2]))[2:])
    else: print(b[2:] + "*2^-" + hex(int(sys.argv[2]))[2:])
    sys.stdout.flush()
elif(sys.argv[1][0] == 'v'):
  a = []
  for line in sys.stdin:
    a.append(line[:- 1])
  for t in range(0, len(a)):
    print(a[- 1 - t])
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
elif(sys.argv[1][0] == 'e'):
  import numpy
  mC = []
  loop = - 1
  if(2 < len(sys.argv)):
    loop = int(sys.argv[2])
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
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
        if(buf < 0):
          buf = abs(buf)
          ffu.append(- (buf - numpy.floor(buf)))
        else:
          ffu.append(   buf - numpy.floor(buf))
      ffuu = []
      for w in ffu[1:]:
        ffuu.append(str(float(w) * float(ffu[0])))
      print(len(ffuu), ": [", ", ".join(ffuu), "]")
      sys.stdout.flush()
    mC = []
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
elif(sys.argv[1][0] == 'E'):
  a  = []
  M  = 0.
  pt = int(sys.argv[2])
  p  = subprocess.Popen(sys.argv[3:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    a.append(ifloat(line[:- 1].split(",")[0]))
    D = a[- 1] * M
    if(pt * pt <= len(a)):
      b  = []
      for t in range(0, pt):
        b.append(0)
      for aa in a:
        b[int((aa + 1.) / 2. * pt)] += aa
      c  = []
      for t in range(0, len(b)):
        c.append(str(b[t] / pt / pt))
      p.stdin.write((",".join(c) + "\n").encode("utf-8"))
      p.stdin.flush()
      M = ifloat(p.stdout.readline().decode("utf-8")[:- 1].split(",")[1])
      a = []
    print(D, ",", M)
    sys.stdout.flush()
elif(sys.argv[1][0] == 'H'):
  p = []
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = 'utf-8', closefd = False):
    d = line[:- 1].split(",")
    if(len(p) < len(d)):
      for t in range(len(p), len(d)):
        p.append(subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE))
    for t in range(0, len(d)):
      p[t].stdin.write((d[t] + "\n").encode("utf-8"))
      p[t].stdin.flush()
    D = M = F = 0
    for t in range(0, len(d)):
      buf = p[t].stdout.readline().decode("utf-8").split(",")
      D += ifloat(buf[0])
      if(0 < ifloat(d[t])): F += 1
      elif(ifloat(d[t]) < 0): F -= 1
      M += ifloat(buf[1])
    print(D / len(p), ",", M / len(p), ",", F / len(p))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'D'):
  p = subprocess.Popen(["sh", "-c", sys.argv[2]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  q = subprocess.Popen(["sh", "-c", sys.argv[3]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  d = 0.
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = 'utf-8', closefd = False):
    p.stdin.write(line.encode("utf-8"))
    q.stdin.write(line.encode("utf-8"))
    p.stdin.flush()
    q.stdin.flush()
    D = p.stdout.readline().decode("utf-8")[:- 1].split(",")
    D.extend(q.stdout.readline().decode("utf-8")[:- 1].split(","))
    D.extend(line[:- 1].split(","))
    print(",".join(D))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'Z'):
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
elif(sys.argv[1][0] == 'X'):
  d = []
  M = 0
  m = 0
  for line in sys.stdin:
    d.append(ifloat(line[:- 1].split(",")[0]))
    M = max(M, d[- 1])
    m = min(m, d[- 1])
  for l in d:
    print((l - (m + M) / 2.) / (M - m) * 2.)
elif(sys.argv[1][0] == 'x'):
  for line in sys.stdin:
    for c in line:
      if(c == '1'):
        print(1)
      elif(c == '0'):
        print(- 1)
elif(sys.argv[1][0] == 'w'):
  bd = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = ifloat(line.split(",")[0])
    if(float(sys.argv[2]) < abs(d - bd)):
      print(d)
      sys.stdout.flush()
      bd = d

