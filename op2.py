#! /usr/bin/env python3
import sys
import numpy as np
import mido
from mido import Message, MidiFile, MidiTrack, MetaMessage
from PIL import Image

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

tbl    = []
mid    = MidiFile()
tracks = []
if(sys.argv[1] == 'm'):
  tbl0 = [0, 2, 4, 5, 7, 9, 11]
  for u in range(0, 2 * len(tbl0)):
    tbl.append(64 + tbl0[u % len(tbl0)] + int(u / len(tbl0)) * 12)
  # Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
  for t in range(0, 1):
    tracks.append(MidiTrack())
    mid.tracks.append(tracks[- 1])
    tracks[- 1].append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(70)))
    # cf. https://ja.wikipedia.org/wiki/General_MIDI
    #tracks[- 1].append(Message('program_change', program = 117))

flg = False
mC  = []
ctr = 0
cnt = 0
ctr = 0
# XXX: these doesn't include any of empathys.
#      it's only the categorized (chilled?) heat.
for line in sys.stdin:
  if(len(line.split("[")) <= 1): continue
  ff = line.split("[")[1].split("]")[0].split(",")
  if(len(sys.argv) <= 2):
    if(sys.argv[1] == 'p'):
      print(ff)
      savePng(ff, ctr)
      ctr += 1
    elif(sys.argv[1] == 'f'):
      for w in ff[1:]:
        print(float(w) * float(ff[0]))
    else:
      print(ff)
      for w in ff[1:]:
        #f = tbl[ctr % len(tracks)]
        f = tbl[int(abs(np.arctan(np.tan(float(w)))) + np.arctan(np.tan(abs(float(ff[0])))) * len(tbl)) % len(tbl)]
        if(0 < float(w)):
          tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=127, time=0))
          tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
        else:
          tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=0, time=0))
          tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
      ctr += 1
  else:
    if(len(mC) < len(ff)):
      mC.append(ff)
      continue
    ffu = ff
    for vvv in range(0, len(ff)):
      ff  = ffu
      ffu = []
      for u in range(0, len(mC)):
        buf = 0.
        for v in range(0, len(ff)):
          buf += float(ff[v]) * float(mC[u][v]) * 1e4
        ffu.append(np.tan(buf))
      if(sys.argv[1] == 'p'):
        print(ffu)
        savePng(ffu, ctr)
        ctr += 1
      elif(sys.argv[1] == 'e'):
        ffuu = []
        for w in ffu[1:]:
          ffuu.append(str(float(w) * float(ffu[0])))
        print(len(ffuu), ": [", ", ".join(ffuu), "]")
      elif(sys.argv[1] == 'f'):
        for w in ffu[1:]:
          print(float(w) * float(ffu[0]))
      else:
        print(ffu)
        flg = True
        for w in ffu[1:]:
          if(w < 0):
            flg = False
        if(flg or float(ffu[0]) == 0.): continue
        for w in ffu[1:]:
          #f = tbl[ctr % len(tracks)]
          f = tbl[int(abs(float(w)) + abs(float(ffu[0]))) % len(tbl)]
          if(w < 0):
            tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=127, time=0))
            tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
          else:
            tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=0, time=0))
            tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
        ctr += 1
    mC = []
if(sys.argv[1] == 'm'):
  mid.save('rand_correct.mid')

