import sys
import subprocess

b = []
S = []
for line in sys.stdin:
  b.append(line[:- 1].split(","))
  for t in range(0, len(b[- 1])): b[- 1][t] = float(b[- 1][t])
  if(len(S) <= 0): S = b[0]
  else:
    for t in range(0, len(b[- 1])): S[t] += b[- 1][t]
  if(2 < len(b)):
    SS = []
    for t in range(0, len(S)): SS.append(S[t] - b[- 1][t] - b[-2][t])
    bb = []
    for t in range(0, len(S)): bb.append(b[- 1][t] + b[-2][t])
    outs = []
    for t in range(0, int(len(S) / 2)):
      outs.append(str(S[t] * bb[int(len(S) / 2) + t]))
    print(",".join(outs))
    b = b[- 2:]

