import sys
import subprocess
import io

p = subprocess.Popen(['./catgp2', '12', str(abs(int(sys.argv[1]))), '.99', '14', '30'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(['../p0/p02', "30", str(abs(int(sys.argv[1])))], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
r = subprocess.Popen(['../p1/p12', "12", "-2", "1", str(abs(int(sys.argv[1])))], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
p.stdin.write("2000\n".encode("utf-8"))
p.stdin.flush()
bd = bbd = s = S = M = t = 0
pM = qM = rM = sM = 1e-20
t -= 1
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
 for line in stdin:
  t += 1
  try:
    if(t % 2 == 0):
      bbd = bd
      bd  = float(line.decode("utf-8").split(",")[0])
      s  += (bd - bbd) * M
      print(s)
      continue
    d = float(line.decode("utf-8").split(",")[0])
  except:
    continue
  s += (d - bd) * M
  print(s)
  if(bd != 0):
    dd = (d + bd) / 2.
    p.stdin.write((str(dd) + "\n").encode("utf-8"))
    q.stdin.write((str(dd) + "\n").encode("utf-8"))
    r.stdin.write((str(dd) + "\n").encode("utf-8"))
    p.stdin.flush()
    q.stdin.flush()
    r.stdin.flush()
    p0 = p.stdout.readline().decode("utf-8").split(",")
    q0 = q.stdout.readline().decode("utf-8").split(",")
    r0 = r.stdout.readline().decode("utf-8").split(",")
    pp = float(p0[0])
    qq = float(q0[0])
    rr = float(r0[0])
    ss = d - bbd
    pM = max(abs(pp), pM)
    qM = max(abs(qq), qM)
    rM = max(abs(rr), rM)
    sM = max(abs(ss), sM)
    M  = pp / pM + qq / qM + rr / rM + ss / sM
  print(s)
  sys.stdout.flush()

