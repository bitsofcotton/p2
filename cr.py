#! /usr/bin/env python3
import sys
import io
import numpy
import struct
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
        ' ': -1, '\t': -1, '\n': -1, '-': 16}
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

def getrand(mm):
  m = abs(mm)
  # if mm < 0, shuffles random methods.
  if(mm < 0):
    return getrand(abs(getrand(m) * 6 * 2))
  # if 6 <= m, divide them.
  if((m / 6) % 2 == 1):
   return getrand(abs(m) % 6) / getrand(abs(m) % 6)
  global rr, sr
  if(m % 6 == 0):
    return rr.uniform(- 1., 1.)
  elif(m % 6 == 1):
    return rr.gauss(0., 1.)
  elif(m % 6 == 2):
    return rr.randint(0, 255) - 127.5
  elif(m % 6 == 3):
    return sr.uniform(- 1., 1.)
  elif(m % 6 == 4):
    return sr.gauss(0., 1.)
  return sr.randint(0, 255) - 127.5

if(len(sys.argv) < 2):
  print("not much arguments")
elif(sys.argv[1][0] == 'r'):
  while(True):
    print(getrand(int(sys.argv[2])))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'C'):
  for t in range(0, abs(int(sys.argv[2]))):
    if(int(sys.argv[2]) < 0):
      print(numpy.cos(t / float(int(sys.argv[2])) * 2. * numpy.pi * int(sys.argv[3])))
    else:
      if(int(sys.argv[3]) < 0):
        print(- pow((t - abs(int(sys.argv[2])) / 2.), - int(sys.argv[3])))
      else:
        print(  pow((t - abs(int(sys.argv[2])) / 2.),   int(sys.argv[3])))
elif(sys.argv[1][0] == 'n'):
  for t in range(0, abs(int(sys.argv[2]))):
    if(int(sys.argv[2]) < 0):
      print(- ((t % abs(int(sys.argv[3]))) - abs(int(sys.argv[3])) / 2.))
    else:
      print(   (t % abs(int(sys.argv[3]))) - abs(int(sys.argv[3])) / 2.)
elif(sys.argv[1][0] == 'R'):
  while(True):
    a = []
    idx = 0
    for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
      a.extend(struct.pack('f', ifloat(line.split(",")[0])))
      if(abs(int(sys.argv[2])) <= idx): break
      idx += 1
    m = hashlib.sha256()
    m.update(bytearray(a))
    a = m.digest()
    for byte in a:
      print(byte - 127.5)
    sys.stdout.flush()
elif(sys.argv[1][0] == 'c'):
  while(True):
    a = []
    idx = 0
    for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
      a.append(ifloat(line.split(",")[0]))
      if(abs(int(sys.argv[2])) <= idx): break
      idx += 1
    a = numpy.fft.ifft(a)
    for aa in a:
      print(aa.real)
elif(sys.argv[1][0] == 'w'):
  cnt = bd = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = ifloat(line.split(",")[0])
    if(float(sys.argv[2]) < abs(d - bd)):
      if(int(sys.argv[3]) < cnt):
        print(d)
        sys.stdout.flush()
        cnt = 0
      cnt += 1
      bd   = d
elif(sys.argv[1][0] == 'S'):
  t = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    if(t < int(sys.argv[2])):
      pass
    else:
      print(line[:- 1])
      sys.stdout.flush()
      t = int(sys.argv[2])
    t += 1
elif(sys.argv[1][0] == 'a'):
  d = [0.]
  M = [0.]
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    MM = M[0]
    for MMM in M[1:]:
      MM += MMM
    d.append(ifloat(line.split(",")[0]))
    print(MM * d[- 1])
    # N.B. average shift they kills some normal jammers.
    #      this takes return to origin, then, return to average.
    d  = d[- int(sys.argv[2]):]
    dd = d[0]
    for ddd in d[1:]:
      dd += ddd
    M.append(dd)
    M  = M[- int(sys.argv[3]):]
    sys.stdout.flush()
elif(sys.argv[1][0] == 'd'):
  bd = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d  = ifloat(line.split(",")[0])
    print(d - bd)
    bd = d
    sys.stdout.flush()
elif(sys.argv[1][0] == 'u'):
  bd = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = ifloat(line.split(",")[0])
    if(d != bd):
      print(d)
      bd = d
    sys.stdout.flush()
elif(sys.argv[1][0] == 's'):
  s = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    s += ifloat(line.split(",")[0])
    print(s)
    sys.stdout.flush()
elif(sys.argv[1][0] == 'i'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = ifloat(line.split(",")[0])
    if(d != 0.):
      print(1. / d)
      sys.stdout.flush()
elif(sys.argv[1][0] == 'f'):
  bd = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    d = ifloat(line.split(",")[0])
    print(d * bd)
    bd = d
    sys.stdout.flush()
elif(sys.argv[1][0] == 'l'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print(line.split(",")[int(sys.argv[2])])
    sys.stdout.flush()
elif(sys.argv[1][0] == 't'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    print(ifloat(line.split(",")[0]) * float(sys.argv[2]))
    sys.stdout.flush()
elif(sys.argv[1][0] == 'F'):
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    b = hex(int(ifloat(line.split(",")[0]) * pow(2., int(sys.argv[2])) ))
    if(b[0] == '-'): print(b[0] + b[3:] + "*2^-" + hex(int(sys.argv[2]))[2:])
    else: print(b[2:] + "*2^-" + hex(int(sys.argv[2]))[2:])
    sys.stdout.flush()
elif(sys.argv[1][0] == 'k'):
  t = 0
  for line in io.open(sys.stdin.fileno(), 'r', buffering = 1, encoding = "utf-8", closefd = False):
    if(t % int(sys.argv[2]) == 0):
      print(line[:- 1])
      sys.stdout.flush()
      t = 0
    t += 1

