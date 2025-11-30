import io
import sys

a = []
for line in io.open(sys.stdin.fileno(), encoding = 'utf-8', closefd = False):
  a.append(line[:- 1].split(","))
  if(int(sys.argv[1]) <= len(a)):
    s = []
    for t in a[0]:
      s.append(float(t))
    for aa in a[1:]:
      for t in range(0, len(aa)):
        s[t] += float(aa[t])
    for aa in a:
      ss = []
      for t in range(0, len(s)):
        if(s[t] < 0):
          ss.append(str(- float(aa[t])))
        else:
          ss.append(aa[t])
      print(",".join(ss))
    a = []
    sys.stdout.flush()

