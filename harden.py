import os
import numpy
import io
import sys

m = []
n = int(sys.argv[1])

with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    d = float(line.decode("utf-8").split(",")[0])
    if(len(m) == 0):
      m.append([])
    m[- 1].append(d)
    if(len(m[- 1]) == n):
      if(n + 2 <= len(m)):
        M = numpy.matrix(m[:- 2])
        A = numpy.matrix(m[- 2])
        x = numpy.matrix(m[- 1])
        print(numpy.inner(A, x * M)[0, 0])
        sys.stdout.flush()
        m = []
      else:
        m.append([])

