#! /usr/bin/env python3
import io
import sys
import random
import subprocess

def ifloat(x):
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

def ifloatout(x):
  b = hex(int(x))
  if(b[0] == '-'): return b[0] + b[3:] + "*2^0"
  return b[2:] + "*2^0"

D = M = t = 0
p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
q = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  D = M * ifloat(line.split(",")[0]) * abs(float(sys.argv[1]))
  if(M != 0. and float(sys.argv[1]) < 0): D *= random.uniform(- 1, 1) / M / M
  p.stdin.write(line.encode("utf-8"))
  p.stdin.flush()
  pp = p.stdout.readline().decode("utf-8")
  q.stdin.write(pp.encode("utf-8"))
  q.stdin.flush()
  qq = q.stdout.readline().decode("utf-8")
  M  = ifloat(pp[:- 1].split(",")[1]) * ifloat(qq[:- 1].split(",")[1])
  if(60 < t): print(ifloatout(D), ",", ifloatout(M))
  sys.stdout.flush()
  t += 1

