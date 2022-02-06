#! /usr/bin/env python3
import io
import sys
import numpy
import subprocess

MA = float(sys.argv[1])
p = subprocess.Popen(sys.argv[2:], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
M = M0 = ML = S = bS = 0.
for line in io.open(sys.stdin.fileno(), encoding = "utf-8", closefd = False):
  S  = float(line.split(",")[0])
  D  = (S - bS) * (M - bS)
  if(M0 < abs(S)): M0 = abs(S) * 2.
  d  = numpy.arctan(S * MA / M0)
  d  = 1. / d
  if(ML < abs(d)): ML = abs(d) * 2.
  d *= MA / ML
  d  = numpy.arctan(d)
  p.stdin.write((str(d) + "\n").encode("utf-8"))
  p.stdin.flush()
  M  = float(p.stdout.readline().decode("utf-8").split(",")[1])
  M  = numpy.tan(M)
  M /= MA / ML
  M  = 1. / M
  M  = numpy.tan(M)
  M /= MA / M0
  if(abs(S) * 2. < abs(M)): M = 0.
  bS = S
  print(D, ",", M)
  sys.stdout.flush()

