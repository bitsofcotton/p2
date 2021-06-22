import mido
from mido import Message, MidiFile, MidiTrack, MetaMessage
import subprocess
import sys
import random

tbl = []
for u in range(0, 5 * 12):
  tbl.append(36 + u)

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
    c = int(random.SystemRandom().uniform(0, 120 * 4 / 8))
    if(c != 0):
      track.append(Message('note_on',  note=f, velocity=0, time=0))
      track.append(Message('note_off', note=f, time= c * 8))
mid.save('rand_correct.mid')

