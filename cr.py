#! /usr/bin/env python3
import sys
import io
import numpy
import random
import hashlib

# mersenne twister:
rr = random.Random()
# /dev/urandom:
sr = random.SystemRandom()

def ifloat(x):
  try:
    return float(x)
  except:
    try:
      b = x.split("*")
      n = e = 0.
      tbl = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, \
        '8': 8, '9': 9, 'a': 10, 'b': 11, 'c': 12, 'd': 13, 'e': 14, 'f': 15, \
        ' ': -1, '\t': -1, '-': 16}
      m = False
      for ff in b[0]:
        if(tbl[ff] < 0): continue
        if(tbl[ff] == 16):
          m = True
          continue
        n *= 16
        n += tbl[ff]
      if(m): n = - n
      m = False
      for ff in b[1][2:]:
        if(tbl[ff] < 0): continue
        if(tbl[ff] == 16):
          m = True
          continue
        e *= 16
        e += tbl[ff]
      if(m): e = - e
      return n * pow(2., e)
    except:
      pass
  return 0.

def ifloatout(x, flag):
  if(flag < 0): return str(x)
  b = hex(int(x * pow(2., flag)))
  if(b[0] == '-'): return b[0] + b[3:] + "*2^-" + hex(int(flag))[2:]
  return b[2:] + "*2^-" + hex(int(flag))[2:]

def getrand(mm):
  m = abs(mm)
  # if mm < 0, shuffles random methods.
  if(mm < 0):
    return getrand(abs(getrand(m) * 16))
  global rr, sr
  bw = 0
  # sum up prng nums.
  if(m % 6 == 0):
    bw = rr.uniform(- 1., 1.)
  elif(m % 6 == 1):
    bw = rr.gauss(0., 1.)
  elif(m % 6 == 2):
    bw = sr.uniform(- 1., 1.)
  elif(m % 6 == 3):
    bw = sr.gauss(0., 1.)
  elif(m % 6 == 4):
    bw = rr.randint(0, 255) - 127.5
  else:
    bw = sr.randint(0, 255) - 127.5
  if((m / 6) % 2 == 1):
    return bw / getrand(abs(m) % 6)
  return bw

if(4 < len(sys.argv) and sys.argv[4][0] == 'r'):
  if(int(sys.argv[2]) < 0):
    while(True):
      s = getrand(int(sys.argv[1]))
      for idx in range(0, abs(int(sys.argv[3]))):
        if(int(sys.argv[3]) < 0):
          s += getrand(int(sys.argv[1]))
        else:
               getrand(int(sys.argv[1]))
      print(s)
      sys.stdout.flush()
  else:
    for idx in range(0, int(sys.argv[2])):
      s = getrand(int(sys.argv[1]))
      for idx2 in range(0, abs(int(sys.argv[3]))):
        if(int(sys.argv[3]) < 0):
          s += getrand(int(sys.argv[1]))
        else:
               getrand(int(sys.argv[1]))
      print(s)
      sys.stdout.flush()
elif(4 < len(sys.argv) and sys.argv[4][0] == 'R'):
  if(int(sys.argv[2]) < 0):
    while(True):
      a = []
      for idx in range(0, abs(int(sys.argv[3]))):
        if(int(sys.argv[1]) == 0):
          a.append(rr.randint(0, 255))
        else:
          a.append(sr.randint(0, 255))
      m = hashlib.sha256()
      m.update(bytearray(a))
      a = m.digest()
      for byte in a:
        print(byte - 127.5)
      sys.stdout.flush()
  else:
    for idx in range(0, int(sys.argv[2])):
      a = []
      for idx in range(0, abs(int(sys.argv[3]))):
        if(int(sys.argv[1]) == 0):
          a.append(rr.randint(0, 255))
        else:
          a.append(sr.randint(0, 255))
      m = hashlib.sha256()
      m.update(bytearray(a))
      a = m.digest()
      for byte in a:
        print(byte - 127.5)
      sys.stdout.flush()
elif(4 < len(sys.argv) and sys.argv[4][0] == 'c'):
  for u in range(0, abs(int(sys.argv[2]))):
    a = []
    for t in range(0, abs(int(sys.argv[1]))):
      a.append(numpy.cos(t) * pow(2., 16))
      a[- 1] -= numpy.floor(a[- 1] * 1e2) / 1e2
    a = numpy.fft.ifft(a)
    for aa in a[1:]:
      print(aa.real)
elif(4 < len(sys.argv) and sys.argv[4][0] == 'C'):
  for t in range(0, abs(int(sys.argv[1]))):
    if(int(sys.argv[1]) < 0):
      print(numpy.cos(t / float(int(sys.argv[1])) * 2. * numpy.pi * int(sys.argv[2])))
    else:
      if(int(sys.argv[2]) < 0):
        print(- pow((t - abs(int(sys.argv[1])) / 2.), - int(sys.argv[2])))
      else:
        print(  pow((t - abs(int(sys.argv[1])) / 2.),   int(sys.argv[2])))
elif(4 < len(sys.argv) and sys.argv[4][0] == 'n'):
  for t in range(0, abs(int(sys.argv[1]))):
    if(1 < int(sys.argv[3]) and t % abs(int(sys.argv[3])) != 0): continue
    if(int(sys.argv[1]) < 0):
      print(- ((t % abs(int(sys.argv[2]))) - abs(int(sys.argv[2])) / 2.))
    else:
      print(   (t % abs(int(sys.argv[2]))) - abs(int(sys.argv[2])) / 2.)
elif(4 < len(sys.argv) and sys.argv[4][0] == 'w'):
  cnt = bd = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = float(line[:- 1].split(",")[0])
    if(float(sys.argv[1]) < abs(d - bd)):
      if(int(sys.argv[2]) < cnt):
        print(d)
        sys.stdout.flush()
        cnt = 0
      cnt += 1
      bd   = d
elif(4 < len(sys.argv) and sys.argv[4][0] == 'S'):
  t = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    if(t < int(sys.argv[3])):
      pass
    else:
      print(line[:- 1])
    sys.stdout.flush()
    t += 1
else:
  t = s = bd = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    ll = line[:- 1].split(",")[int(sys.argv[1])]
    if(len(sys.argv) < 4 or t % int(sys.argv[3]) == 0):
      fint = - 1
      if(len(sys.argv) < 3):
        print(ll)
        sys.stdout.flush()
        continue
      elif(0 <= float(sys.argv[2])):
        d = ifloat(ll) * float(sys.argv[2])
      else:
        d = ifloat(ll)
        fint = abs(float(sys.argv[2]))
      if(4 < len(sys.argv)):
        if(sys.argv[4][0] == 'd'):
          print(ifloatout(d - bd, fint), ",", ", ".join(line[:- 1].split(",")[int(sys.argv[1]) + 1:]))
        elif(sys.argv[4][0] == 's'):
          s += d
          print(ifloatout(s, fint), ",", ", ".join(line[:- 1].split(",")[int(sys.argv[1]) + 1:]))
        elif(sys.argv[4][0] == 'u'):
          if(d != bd):
            print(ifloatout(d, fint), ",", ", ".join(line[:- 1].split(",")[int(sys.argv[1]) + 1:]))
        elif(sys.argv[4][0] == 'i'):
          if(d != 0.):
            print(ifloatout(1. / d, fint), ",", ", ".join(line[:- 1].split(",")[int(sys.argv[1]) + 1:]))
        else:
          exit(0)
        bd = d
      else:
        print(ifloatout(d, fint), ",", ", ".join(line[:- 1].split(",")[int(sys.argv[1]) + 1:]))
      sys.stdout.flush()
    t += 1

