import mido
from mido import Message, MidiFile, MidiTrack, MetaMessage
import subprocess
import sys
import random

tbl0 = [0, 2, 4, 5, 7, 9, 11]
tbl = []
for u in range(0, 5 * len(tbl0)):
  tbl.append(36 + tbl0[u % len(tbl0)] + int(u / len(tbl0) * 12))
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
for line in sys.stdin:
  if(len(line.split("[")) <= 1): continue
  ff = line.split("[")[1][:- 2].split(",")
  ff.extend(ff)
  print(ff)
  for w in ff:
    f = tbl[int(float(w)) % len(tbl)]
    track.append(Message('note_on',  note=f, velocity=127, time=0))
    track.append(Message('note_off', note=f, time=120))
mid.save('rand_correct.mid')

