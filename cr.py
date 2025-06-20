#! /usr/bin/env python3
import sys
import io
import struct
import hashlib
import subprocess

if(len(sys.argv) < 2):
  print("not much arguments")
elif(sys.argv[1][0] == 'R'):
  while(True):
    a = []
    idx = 0
    for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
      a.extend(struct.pack('f', float(line.split(",")[0])))
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
    d = line.split(",")
    for t in range(0, len(d)):
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
      d[t] = str(n * pow(2., e - offset))
    print(",".join(d))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'F'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = line.split(",")
    for t in range(0, len(d)):
      b = hex(int(float(d[t][0]) * pow(2., int(sys.argv[2])) ))
      if(b[0] == '-'): d[t] = b[0] + b[3:] + "*2^-" + hex(int(sys.argv[2]))[2:]
      else: d[t] = b[2:] + "*2^-" + hex(int(sys.argv[2]))[2:]
    print(",".join(d))
    sys.stdout.flush()
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
    J = []
    for t in range(0, len(d)):
      J.extend(p[t].stdout.readline().decode("utf-8")[:- 1].split(","))
    print(",".join(J))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'D'):
  p = subprocess.Popen(["sh", "-c", sys.argv[2]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
  q = subprocess.Popen(["sh", "-c", sys.argv[3]], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
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

