import sys
import io

arr = []
with io.open(sys.stdin.fileno(), 'rb', closefd=False) as stdin:
  for line in stdin:
    arr.append(line[:- 1])
for t in range(0, len(arr)):
  print(arr[- t - 1])

