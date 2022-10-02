import sys
import subprocess
import mido
import random
from mido import MidiFile, MidiTrack, MetaMessage

prng = []
for line in sys.stdin:
  prng.append(abs(int(float(line) )))
n = int(float(len(prng)))
p = subprocess.Popen(['sh', '-c', sys.argv[1]])
m = MidiFile('rand_correct.mid')
m = len(m.tracks)
n = int(n / m)
for t in range(0, n):
  p = subprocess.Popen(['sh', '-c', sys.argv[1]])
  p.wait()
  q = subprocess.Popen(['mv', 'rand_correct.mid', 'r' + str(t) + '.mid'])
  q.wait()
mid   = MidiFile()
for t in range(0, m):
  track = MidiTrack()
  mid.tracks.append(track)
  track.append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(70)))
for t in range(0, n):
  for tt in range(0, m):
    mm = MidiFile('r' + str(prng[(t * m + tt) % len(prng)] % n) + '.mid')
    for i, track in enumerate(mm.tracks):
      if(i != tt): continue
      for msg in track:
        mid.tracks[tt].append(msg)
mid.save('rand_correct_concat.mid')

