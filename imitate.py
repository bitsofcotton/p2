import sys

for line in sys.stdin:
  # (d - d-) / d- == D
  # Dd- - d + d- = 0.
  # d-(D+1)=d
  D = float(line.split(",")[0])
  r = D + 1.
  if(sys.argv[1] == '+'):
    print(D)
    print(r * D)
  elif(sys.argv[1] == '-'):
    print(D / r)
    print(D)
  sys.stdout.flush()

