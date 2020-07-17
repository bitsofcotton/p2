import mido
from mido import Message, MidiFile, MidiTrack, MetaMessage
import subprocess
import sys

tbl = [36, 38, 40, 41, 43, 45, 47]
for u in range(1, 5):
  for s in range(0, 7):
    tbl.append(tbl[s] + 12 * u)
rng = 20000

# Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
mid   = MidiFile()
track = MidiTrack()
mid.tracks.append(track)
track.append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(100)))

p = subprocess.Popen(['./p'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
t = 0
b = 0
for line in sys.stdin:
 for l in line:
  if(l == '\n' or l == '.' or l == '-' or l == ' '):
    continue
  t += 1
  b += int(l)
  if(t % 6 != 0):
    b *= 10
    continue
  # XXX: This only places note on corrected random way.
  #      So this is not a music in certain definition.
  mul = int(sys.argv[1])
  p.stdin.write((str(b % (len(tbl) * mul)) + "\n").encode("utf-8"))
  p.stdin.flush()
  f = tbl[int((int(float(p.stdout.readline().decode("utf-8").split(",")[0]) / int(sys.argv[2])) % (len(tbl) * mul)) / mul)]
  #f = tbl[b % len(tbl)]
  if(36 + 12 * 2 <= f):
    track.append(Message('note_on',  note=f, velocity=127, time=0))
    track.append(Message('note_off', note=f, time=120))
  else:
    track.append(Message('note_on',  note=0, velocity=0, time=0))
    track.append(Message('note_off', note=0, time=120))
  print(f)
  b = 0
  if(rng < t):
    break
 if(rng < t):
   break
mid.save('rand_correct.mid')

