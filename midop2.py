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

p = subprocess.Popen(['./catgp2', '8', '8', '.8', '20', '40', '80', '160', '320'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
flg = False
p.stdin.write((str(10000) + "\n").encode("utf-8"))
for t in range(0, int(sys.argv[1])):
  # convert unpredictable to a little predictable ones.
  try:
    b = float(sys.stdin.readline().split(",")[0].split(" ")[0])
  except:
    continue
  # XXX: This only places note on corrected random way.
  #      So this is not a music in certain definition.
  p.stdin.write((str(b % len(tbl)) + "\n").encode("utf-8"))
  p.stdin.flush()
  w = float(p.stdout.readline().decode("utf-8").split(",")[2]) / float(sys.argv[2])
  if(w != 0.):
    flg = True
  if(flg):
    f = tbl[int(w) % len(tbl)]
    track.append(Message('note_on',  note=f, velocity=127, time=0))
    track.append(Message('note_off', note=f, time=120))
    c = int(random.SystemRandom().uniform(0, 120 * 4 / 8))
    if(c != 0):
      track.append(Message('note_on',  note=f, velocity=0, time=0))
      track.append(Message('note_off', note=f, time= c * 8))
    print(w)
    print(f)
mid.save('rand_correct.mid')

