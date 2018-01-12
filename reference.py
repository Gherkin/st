import fileinput
from itertools import groupby
from operator import itemgetter
from statistics import median, mean

data = (line.split() for line in fileinput.input())
for key, group in groupby(data, key=itemgetter(0)):
    values = list(float(value) for _, value in group)
    print(f'{key} {mean(values):.6f} {median(values):.6f}')
