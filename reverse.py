import sys
import io

arr = []
for line in io.open(sys.stdin.fileno(), 'rb', closefd = False):
  arr.append(line[:- 1].decode("utf-8"))
for t in range(0, len(arr)):
  print(arr[- t - 1])

