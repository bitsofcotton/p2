import sys

for line in sys.stdin:
  if(len(line.split("[")) <= 1): continue
  ff = line.split("[")[1].split("]")[0].split(",")
  if(len(sys.argv) <= 1):
    for w in ff:
      print(w)
    sys.stdout.flush()

