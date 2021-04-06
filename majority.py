import sys
import subprocess
import io
import numpy

p = subprocess.Popen(['./catgp', '12', '.99', '14', '30'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(['../p0/p0', "30"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
r = subprocess.Popen(['../p0/p0', "-30"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
s = subprocess.Popen(['../p1/p1', "12", "-2", "1"], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
p.stdin.write("2000\n".encode("utf-8"))
p.stdin.flush()
bd = S  = M  = 0
pM = qM = rM = sM = tM = 1e-20
pp = qq = rr = ss = tt = 0
Sp = Sq = Sr = Ss = St = 0
Bp = Bq = Br = Bs = Bt = 0
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
 for line in stdin:
  try:
    d = float(line.decode("utf-8").split(",")[0])
  except:
    continue
  S += (d - bd) * M
  print(S)
  if(bd != 0):
    p.stdin.write((str(d) + "\n").encode("utf-8"))
    q.stdin.write((str(d) + "\n").encode("utf-8"))
    r.stdin.write((str(d) + "\n").encode("utf-8"))
    s.stdin.write((str(d) + "\n").encode("utf-8"))
    p.stdin.flush()
    q.stdin.flush()
    r.stdin.flush()
    s.stdin.flush()
    p0 = p.stdout.readline().decode("utf-8").split(",")
    q0 = q.stdout.readline().decode("utf-8").split(",")
    r0 = r.stdout.readline().decode("utf-8").split(",")
    s0 = s.stdout.readline().decode("utf-8").split(",")
    if(pp * (d - bd) > 0):
      Sp = 0
    else:
      Sp += float(p0[1]) - Bp
      Bp  = float(p0[1])
    if(qq * (d - bd) > 0):
      Sq = 0
    else:
      Sq += float(q0[1]) - Bq
      Bq  = float(q0[1])
    if(rr * (d - bd) > 0):
      Sr = 0
    else:
      Sr += float(r0[1]) - Br
      Br  = float(r0[1])
    if(ss * (d - bd) > 0):
      Ss = 0
    else:
      Ss += float(s0[1]) - Bs
      Bs  = float(s0[1])
    pp = float(p0[0]) + Sp
    qq = float(q0[0]) + Sq
    rr = float(r0[0]) + Sr
    ss = float(s0[0]) + Ss
    tt = d - bd
    pM = max(abs(pp), pM)
    qM = max(abs(qq), qM)
    rM = max(abs(rr), rM)
    sM = max(abs(ss), sM)
    tM = max(abs(tt), tM)
    M  = (pp * tM / pM + qq * tM / qM + rr * tM / rM + ss * tM / sM + tt) / 5.
    if(not numpy.isfinite(M)): M = 0
  bd = d
  sys.stdout.flush()

