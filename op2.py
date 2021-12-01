import sys
import numpy as np
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
  for u in range(0, 2 * len(tbl0)):
    tbl.append(64 + tbl0[u % len(tbl0)] + int(u / len(tbl0)) * 12)
  # Thanks to : https://qiita.com/tjsurume/items/75a96381fd57d5350971 via search engine
  for t in range(0, 4):
    tracks.append(MidiTrack())
    mid.tracks.append(tracks[- 1])
    tracks[- 1].append(MetaMessage('set_tempo', tempo=mido.bpm2tempo(70)))
    # cf. https://ja.wikipedia.org/wiki/General_MIDI
    #tracks[- 1].append(Message('program_change', program = 117))

flg = False
mA  = []
mC  = []
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
      for w in ff[1:]:
        #f = tbl[ctr % len(tracks)]
        f = tbl[int(abs(float(w)) + abs(float(ff[0]))) % len(tbl)]
        if(float(w) < 0):
          tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=127, time=0))
          tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
        else:
          tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=7, time=0))
          tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
      ctr += 1
  else:
    if(len(mC) < len(ff)):
      mC.append(ff)
      continue
    elif(len(mA) < len(ff)):
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
      if(sys.argv[1] == 'p'):
        print(ffu)
        savePng(ffu, s)
      elif(sys.argv[1] == 'e'):
        ffuu = []
        for w in ffu[1:]:
          ffuu.append(str(float(w) * float(ffu[0])))
        print(len(ffuu), ": [", ", ".join(ffuu), "]")
      else:
        print(ffu)
        for w in ffu[1:]:
          #f = tbl[ctr % len(tracks)]
          f = tbl[int(abs(float(w)) + abs(float(ffu[0]))) % len(tbl)]
          if(float(w) < 0):
            tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=127, time=0))
            tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
          else:
            tracks[ctr % len(tracks)].append(Message('note_on',  note=f, velocity=0, time=0))
            tracks[ctr % len(tracks)].append(Message('note_off', note=f, time=120))
        ctr += 1
      break
if(sys.argv[1] == 'm'):
  mid.save('rand_correct.mid')

