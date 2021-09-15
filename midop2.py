import mido
from mido import Message, MidiFile, MidiTrack, MetaMessage
import subprocess
import sys
import random
import numpy as np

tbl0 = [0, 2, 4, 5, 7, 9, 11]
#tbl0 = [0, 7, 11]
tbl = []
for u in range(0, 5 * len(tbl0)):
  tbl.append(64 - 12 * 2 + tbl0[u % len(tbl0)] + int(u / len(tbl0)) * 12)
tbl2 = []
for t in range(0, len(tbl)):
  tbl2.append(tbl[(int(len(tbl) / 2) + t) % len(tbl)])
tbl = tbl2

# Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
mid    = MidiFile()
tracks = []
for t in range(0, 3):
  tracks.append(MidiTrack())
  mid.tracks.append(tracks[- 1])
  tracks[- 1].append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(120)))

flg = False
mA  = []
mC  = []
ms  = 0
cnt = 0
ucnt = 0
# XXX: these doesn't include any of empathys.
#      it's only the categorized (chilled?) heat.
for line in sys.stdin:
  if(len(line.split("[")) <= 1): continue
  ff = line.split("[")[1].split("]")[0].split(",")
  if(len(sys.argv) <= 1):
    print(ff)
    for w in ff:
      f = tbl[ucnt % len(tracks)]
      if(int(float(w)) < 0):
        tracks[ucnt % len(tracks)].append(Message('note_on',  note=f, velocity=127, time=0))
        tracks[ucnt % len(tracks)].append(Message('note_off', note=f, time=120))
      else:
        tracks[ucnt % len(tracks)].append(Message('note_on',  note=f, velocity=7, time=0))
        tracks[ucnt % len(tracks)].append(Message('note_off', note=f, time=120))
    ucnt += 1
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
      ff[0] = float(s) / float(sys.argv[1]) * 2. - 1.
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
      for w in ffu:
        f = tbl[ucnt % len(tracks)]
        if(int(float(w)) < 0):
          tracks[ucnt % len(tracks)].append(Message('note_on',  note=f, velocity=127, time=0))
          tracks[ucnt % len(tracks)].append(Message('note_off', note=f, time=120))
        else:
          tracks[ucnt % len(tracks)].append(Message('note_on',  note=f, velocity=0, time=0))
          tracks[ucnt % len(tracks)].append(Message('note_off', note=f, time=120))
      ucnt += 1
mid.save('rand_correct.mid')

