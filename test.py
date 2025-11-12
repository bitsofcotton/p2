import io
import sys

A = []
L = []
for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
  d = line[:- 1].split(",")
  for t in range(0, len(d)):
    d[t] = float(d[t])
  A.append(d)
  if(len(A) < 4): continue
  S0 = []
  for t in range(0, len(A[0])):
    S0.append(A[0][t])
  for u in range(1, len(A) - 2):
    for t in range(0, len(A[u])):
      S0[t] += A[u][t]
  S = []
  for t in range(0, len(A[0])):
    S.append(A[0][t] - S0[t] / (len(A) - 2.))
  for u in range(1, len(A)):
    for t in range(0, len(A[u])):
      S[t] += A[u][t] - S0[t] / (len(A) - 2.)
  for t in range(0, int(len(S) / 2)):
    S[t] = (S[t] + S[t + int(len(S) / 2)]) * S[t + int(len(S) / 2)]
  if(len(L)):
    U = []
    for t in range(0, len(L)):
      U.append(str(S[t] * L[t]))
    print(",".join(U))
  L = S
  sys.stdout.flush()

