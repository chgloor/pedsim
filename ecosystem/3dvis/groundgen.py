from __future__ import print_function
from random import randint

w = 250
h = 150

cellsize = 1
xll = (-w/2) * cellsize
yll = (-h/2) * cellsize
nodata = 0

matrix = [[0 for x in range(w)] for y in range(h)]

def expand(matrix, x, y, rate=0.1):
    v = matrix[y][x]
    if x+1 < w and matrix[y][x+1] < v:
        matrix[y][x+1] = v - rate
    if x-1 >= 0 and matrix[y][x-1] < v:
        matrix[y][x-1] = v - rate
    if y+1 < h and matrix[y+1][x] < v:
        matrix[y+1][x] = v - rate
    if y-1 >= 0 and matrix[y-1][x] < v:
        matrix[y-1][x] = v - rate

for growsteps in range(20):
    for growbits in range(100):
        rx = randint(0, w-1)
        ry = randint(0, h-1)
        hh = matrix[ry][rx]
        matrix[ry][rx] = hh + 1

    for steps in range(20):
        for y in range(h):
            for x in range(w):
                expand(matrix, x, y)

print("ncols         {0}".format(w))
print("nrows         {0}".format(h))
print("xllcorner     {0}".format(xll))
print("yllcorner     {0}".format(yll))
print("cellsize      {0}".format(cellsize))
print("NODATA_value  {0}".format(nodata))

for y in range(h):
    for x in range(w):
        print("{0} ".format(matrix[y][x]), end="")

    print("")

