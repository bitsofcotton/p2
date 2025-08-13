import sys
import subprocess

b = []
for line in sys.stdin:
  b.append(line[:- 1].split(","))
  for t in range(0, len(b[- 1])): b[- 1][t] = float(b[- 1][t])
  if(abs(int(sys.argv[1])) * 2 + 2 < len(b)):
    p = subprocess.Popen(["p", "Wc", str(int(sys.argv[1]))], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    if(0 < int(sys.argv[1])):
      w = []
      for idx in range(1, len(b)):
        ww = []
        for iidx in range(0, len(b[- 1])):
          ww.append(b[idx][iidx] - b[idx - 1][iidx])
        w.append(ww)
      M = 0.
      wm2 = []
      for bb in b[- 2]: wm2.append(bb)
      for idx in range(0, len(w)):
        for iidx in range(0, len(w[idx])):
          w[idx][iidx] += wm2[iidx]
          M = max(M, abs(w[idx][iidx]))
      for idx in range(0, len(w)):
        for iidx in range(0, len(w[idx])):
          w[idx][iidx] /= M
          w[idx][iidx]  = str(w[idx][iidx])
      for idx in range(0, len(w)):
        p.stdin.write((",".join(w[idx]) + "\n").encode("utf-8"))
        p.stdin.flush()
        dd = p.stdout.readline().decode("utf-8")[:- 1].split(",")
      p.stdin.close()
      dd = dd[0:len(wm2)]
      for idx in range(0, len(dd)): dd[idx] = str(float(dd[idx]) )
      bd = []
      for idx in range(0, len(b[- 1])): bd.append(str((b[- 1][idx] + wm2[idx]) / M))
    else:
      bb = []
      for idx in range(0, len(b)):
        bbb = []
        for iidx in range(0, len(b[idx])):
          bbb.append(str(b[idx][iidx]))
        bb.append(bbb)
      for idx in range(0, len(bb)):
        p.stdin.write((",".join(bb[idx]) + "\n").encode("utf-8"))
        p.stdin.flush()
        dd = p.stdout.readline().decode("utf-8")[:- 1].split(",")
      p.stdin.close()
      dd = dd[0:len(b[- 2])]
      bd = []
      for idx in range(0, len(b[- 1])): bd.append(str(b[- 1][idx]))
    print(",".join(bd), ",", ",".join(dd))
    b = b[- abs(int(sys.argv[1])) * 2 - 2:]
    sys.stdout.flush()

