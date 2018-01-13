from sys import stdin
from itertools import groupby
from operator import itemgetter

data = (line.split() for line in stdin)
for key, group in groupby(data, key=itemgetter(0)):
    values = list(float(value) for _, value in group)
    values.sort()
    mean = sum(values) / len(values)
    medianish = values[int(len(values) / 2)]  # Possibly wrong value for even len()
    print('{} {:.6f} {:.6f}'.format(key, mean, medianish))
