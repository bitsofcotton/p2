import sys
import subprocess
import io

p = subprocess.Popen(['/home/kazunobu/Created/Work2/p2/catgp2', '12', str(int(sys.argv[1])), '.99', '14', '30'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(['/home/kazunobu/Created/Work2/p0/p02', "30", str(int(sys.argv[1]))], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
r = subprocess.Popen(['/home/kazunobu/Created/Work2/p1/p12', "12", "-2", "1", str(int(sys.argv[1]))], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
p.stdin.write("2000\n")
p.stdin.flush()
bd = bdd = s = M = t = 0
pM = qM = rM = sM = 1e-20
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
 for line in stdin:
  t += 1
  try:
    if(t % 2 == 0):
      bdd = float(line.split(",")[0])
      continue
    d  = float(line.split(",")[0])
  except:
    continue
  s += (d - bd) * M
  if(bd != 0):
    dd = (d + bdd) / 2.
    p.stdin.write(str(dd) + "\n")
    q.stdin.write(str(dd) + "\n")
    r.stdin.write(str(dd) + "\n")
    p.stdin.flush()
    q.stdin.flush()
    r.stdin.flush()
    p0 = p.stdout.readline().split(",")
    q0 = q.stdout.readline().split(",")
    r0 = r.stdout.readline().split(",")
    pp = float(p0[0])
    qq = float(q0[0])
    rr = float(r0[0])
    ss = d - bd
    pM = max(abs(pp), pM)
    qM = max(abs(qq), qM)
    rM = max(abs(rr), rM)
    sM = max(abs(ss), sM)
    M  = pp / pM + qq / qM + rr / rM + ss / sM
  bd = d
  print s
  sys.stdout.flush()

