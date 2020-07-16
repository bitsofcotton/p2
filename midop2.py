import mido
from mido import Message, MidiFile, MidiTrack, MetaMessage
import subprocess
import sys

tbl   = [36, 38, 40, 41, 43, 45, 47]
for s in range(0, 7):
  tbl.append(tbl[s] + 12)
for s in range(0, 7):
  tbl.append(tbl[s] + 24)
rng   = 8000

# Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
mid   = MidiFile()
track = MidiTrack()
mid.tracks.append(track)
track.append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(110)))

p = subprocess.Popen(['./p'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
t = 0
b = 0
for line in sys.stdin:
 for l in line:
  if(l == '\n' or l == '.' or l == '-'):
    continue
  t += 1
  b += int(l)
  if(t % 2 != 0):
    b *= 10
    continue
  # XXX: This only places note randomly with corrected manner.
  #      So this is not a music in certain definition.
  if(len(tbl) <= b):
   try:
    p.stdin.write((str(b % len(tbl)) + "\n").encode("utf-8"))
    p.stdin.flush()
    f = tbl[int(float(p.stdout.readline().decode("utf-8").split(",")[0])) % len(tbl)]
    track.append(Message('note_on',  note=f, velocity=127, time=80))
    track.append(Message('note_off', note=f, time=80))
    print(f)
   except:
    pass
  if(rng < t):
    break
 if(rng < t):
   break
mid.save('rand_correct.mid')

