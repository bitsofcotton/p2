#! /usr/bin/env python3
import sys
import numpy
import mido
from mido import Message, MidiFile, MidiTrack, MetaMessage
from PIL import Image

tbl   = []
mid   = MidiFile()
track = []
if(sys.argv[1] == 'm'):
  tbl0 = [0, 2, 4, 5, 7, 9, 11]
  for u in range(0, 2 * len(tbl0)):
    # Thanks to google with search word midi C value, 60 is one of a C.
    tbl.append(60 + tbl0[u % len(tbl0)] + int(u / len(tbl0)) * 12)
  # Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
  track = MidiTrack()
  mid.tracks.append(track)
  track.append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(70)))
  # cf. https://ja.wikipedia.org/wiki/General_MIDI
  #track.append(Message('program_change', program = 117))

mC  = []
ctr = 0
# XXX: these doesn't include any of empathys.
#      it's only the categorized (chilled?) heat.
for line in sys.stdin:
  if(len(line.split("[")) <= 1): continue
  ff = line.split("[")[1].split("]")[0].split(",")
  if(sys.argv[1] == 'p'):
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
  elif(sys.argv[1] == 'm'):
    print(ff)
    idx = 0
    ctrnote = []
    for w in ff[1:]:
      f    = tbl[int(numpy.arctan(abs(numpy.tan(float(w) * float(ff[0])))) * len(tbl)) % int(len(tbl) / (len(ff) - 1)) + idx * int(len(tbl) / (len(ff) - 1))]
      idx += 1
      if(0 < float(w)):
        track.append(Message('note_on',  note=f, velocity=127, time=0))
        ctrnote.append(f)
      else:
        track.append(Message('note_on',  note=f, velocity=0, time=0))
        ctrnote.append(f)
    if(len(ctrnote) < 1): continue
    track.append(Message('note_off', note=ctrnote[- 1], time=120))
    for cc in ctrnote[:- 1]:
      track.append(Message('note_off', note=cc, time=0))
  elif(sys.argv[1] == 'f'):
    for w in ff[1:]:
      print(float(w) * float(ff[0]))
  elif(sys.argv[1] == 'e' or sys.argv[1] == 'E'):
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
          if(sys.argv[1] == 'E'):
            buf += float(ff[v]) * float(mC[u][v]) * 1e4
          else:
            buf += float(ff[v]) * float(mC[u][v])
        ffu.append(numpy.tan(buf))
      ffuu = []
      for w in ffu[1:]:
        ffuu.append(str(float(w) * float(ffu[0])))
      print(len(ffuu), ": [", ", ".join(ffuu), "]")
    mC = []
  else:
    print("not supported.")
    exit(0)
  ctr += 1
if(sys.argv[1] == 'm'):
  mid.save('rand_correct.mid')

