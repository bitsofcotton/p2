import sys
import csv

r0 = open(sys.argv[1], "rb")
r1 = open(sys.argv[2], "rb")
while(True):
  l0 = r0.readline().decode("utf-8")
  l1 = r1.readline().decode("utf-8")
  try:
    print((float(l0.split(",")[1]) + \
           float(l1.split(",")[1])) / 2.)
  except:
    pass
  if(l0 == "" and l1 == ""):
    break

