import sys
import io
import subprocess

pp = ""
for t in range(0, int(sys.argv[1])):
  pp += "python3 cut.py 0 1 1 p | "
pp += "python3 cut.py 0 1 1 d | "
pp += "python3 cut.py 0 1 " + str(int(sys.argv[1]) + 1)
# N.B. this is also valid because step.py # increases, distribution relaxes.
pp += " | ../p0/p0 -120 "
# N.B. we correct last noise part by p0.
#pp += " | ../p2/catgp -512 | ../p0/p0 -120 "
# N.B. we need status condition size (matrix size) or larger to catgp variable.
#pp += " | ../p2/catgp -256 | ../p0/p0 -60 "
# N.B. feed original matrix size to this step.py causes one function at all:
#pp += " | ../p1/p1 -256 | ../p0/p0 -60 "
p   = subprocess.Popen(['/bin/sh', '-c', pp], stdin = subprocess.PIPE, stdout = subprocess.PIPE)

t = 0
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  p.stdin.write(line)
  p.stdin.flush()
  if(0 < t and t % (int(sys.argv[1]) + 1) == 0):
    print(p.stdout.readline().decode('utf-8')[:- 1])
  sys.stdout.flush()
  t += 1

