import mido
from mido import Message, MidiFile, MidiTrack, MetaMessage
import subprocess
import sys

"""
tbl = [36, 38, 40, 41, 43, 45, 47]
for u in range(1, 5):
  for s in range(0, 7):
    tbl.append(tbl[s] + 12 * u)
"""

tbl = []
for u in range(0, 5 * 12):
  tbl.append(36 + u)
rng = int(sys.argv[1]) * int(sys.argv[2])

# Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
mid   = MidiFile()
track = MidiTrack()
mid.tracks.append(track)
track.append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(100)))

p = subprocess.Popen(['./p'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
t = s = bb = 0
for t in range(0, rng * int(sys.argv[1])):
  # convert unpredictable to a little predictable ones.
  try:
    b  = int(pow(1.5, float(sys.stdin.readline().split(",")[0].split(" ")[0]) / 2000.) * 100)
  except:
    continue
  # XXX: This only places note on corrected random way.
  #      So this is not a music in certain definition.
  p.stdin.write((str(b % len(tbl)) + "\n").encode("utf-8"))
  p.stdin.flush()
  w  = p.stdout.readline().decode("utf-8").split(",")
  fl = False
  if(bb == w[1]):
    s += 1
    fl = True
  bb = w[1]
  f  = tbl[int(float(w[0])) % len(tbl)]
  if(not fl and (t - s) % int(sys.argv[1]) == 0):
    track.append(Message('note_on',  note=f, velocity=127, time=0))
    track.append(Message('note_off', note=f, time=120))
  print(f)
  t += 1
mid.save('rand_correct.mid')

