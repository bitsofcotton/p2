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
  tbl.append(64 - 12 * 3 + tbl0[u % len(tbl0)] + int(u / len(tbl0) * 12))
tbl2 = []
for t in range(0, len(tbl)):
  tbl2.append(tbl[(int(len(tbl) / 2) + t) % len(tbl)])
tbl = tbl2

# Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
mid   = MidiFile()
track = MidiTrack()
mid.tracks.append(track)
track.append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(120)))

flg = False
mA  = []
mC  = []
ms  = 0
for line in sys.stdin:
  if(len(line.split("[")) <= 1): continue
  ff = line.split("[")[1].split("]")[0].split(",")
  if(len(sys.argv) <= 1):
    ff.extend(ff)
    print(ff)
    for w in ff:
      f = tbl[int(float(w)) % len(tbl)]
      track.append(Message('note_on',  note=f, velocity=127, time=0))
      track.append(Message('note_off', note=f, time=120))
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
      n2  = 0.
      for u in range(0, len(mA)):
        ffu.append(0.)
        for v in range(0, len(mA[u])):
          ffu[- 1] += float(tt[v]) * float(mA[u][v])
        n2 += ffu[- 1] * ffu[- 1]
      n2  = pow(n2, .5)
      for w in ffu:
        f = tbl[int(np.arctan(float(w) / n2) / np.pi * len(tbl)) % len(tbl)]
        track.append(Message('note_on',  note=f, velocity=127, time=0))
        track.append(Message('note_off', note=f, time=120))
    mA = []
    mC = []
mid.save('rand_correct.mid')

