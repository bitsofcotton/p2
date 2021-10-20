import sys
import numpy as np

if(len(sys.argv) <= 1 or (sys.argv[1] != 'm' and sys.argv[1] != 'p' and sys.argv[1] != 'h')):
  print(sys.argv[0], " ", "(m|p|h)", "<n>?")
  exit(0)
if(sys.argv[1] == 'h'):
  for line in sys.stdin:
    if(len(line.split("[")) <= 1): continue
    ff = line.split("[")[1].split("]")[0].split(",")
    for w in ff:
      print(w)
    sys.stdout.flush()
  exit(0)

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
  #tbl0 = [0, 7, 11]
  for u in range(0, 5 * len(tbl0)):
    tbl.append(64 - 12 * 2 + tbl0[u % len(tbl0)] + int(u / len(tbl0)) * 12)
  tbl2 = []
  for t in range(0, len(tbl)):
    tbl2.append(tbl[(int(len(tbl) / 2) + t) % len(tbl)])
  tbl = tbl2
  # Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
  for t in range(0, 1):
    tracks.append(MidiTrack())
    mid.tracks.append(tracks[- 1])
    tracks[- 1].append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(70)))
    # cf. https://ja.wikipedia.org/wiki/General_MIDI
    tracks[- 1].append(Message('program_change', program = 117))

flg = False
mA  = []
mC  = []
ms  = 0
ctr = 0
cnt = 0
ctr = 0
# XXX: these doesn't include any of empathys.
#      it's only the categorized (chilled?) heat.
for line in sys.stdin:
  if(len(line.split("[")) <= 1): continue
  ff = line.split("[")[1].split("]")[0].split(",")
  if(len(sys.argv) <= 2):
    print(ff)
    if(sys.argv[1] == 'p'):
      savePng(ff, ctr)
      ctr += 1
    else:
      for w in ff:
        f = tbl[ctr % len(tracks)]
        if(float(w) < 0):
          tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=127, time=0))
          tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
        else:
          tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=7, time=0))
          tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
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
    for s in range(0, int(sys.argv[2])):
      ff[0] = float(s) / float(sys.argv[2]) * 2. - 1.
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
      print(ffu)
      if(sys.argv[1] == 'p'):
        savePng(ffu, s)
      else:
        for w in ffu:
          f = tbl[ctr % len(tracks)]
          if(float(w) < 0):
            tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=127, time=0))
            tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
          else:
            tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=0, time=0))
            tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
        ctr += 1
if(sys.argv[1] == 'm'):
  mid.save('rand_correct.mid')

