#!/usr/bin/env python

## Thanks to Dr N.D. van Foreest for providing this example code. ##


"""
The cost matrix is based on Balas and Toth, 1985, Branch and bound
# methods, in Lawler, E.L, et al., The TSP, John Wiley & Sons,
Chischester, pp 361--401.
"""
from __future__ import print_function

import numpy
import hungarian

inf = 1000

a = numpy.array( [[inf,2,11,10,8,7,6,5],
                  [6,inf,1,8,8,4,6,7],
                  [5,12,inf,11,8,12,3,11],
                  [11,9,10,inf,1,9,8,10],
                  [11,11,9,4,inf,2,10,9],
                  [12,8,5,2,11,inf,11,9],
                  [10,11,12,10,9,12,inf,3],
                  [10,10,10,10,6,3,1,inf]] )

answers = hungarian.lap(a)
print('For each row, matching column index:', answers[0])
assert(numpy.array_equal([1, 2, 0, 4, 5, 3, 7, 6], answers[0]))
points0 = list(zip(range(len(answers[0])), answers[0]))
print('Matching pairs, sorted by row:', points0)

print('For each column, matching row index:', answers[1])
assert(numpy.array_equal([2, 0, 1, 5, 3, 4, 7, 6], answers[1]))
points1 = list(zip(answers[1], range(len(answers[1]))))
print('Matching pairs, sorted by col:', points1)

sum0 = sum(a[range(len(answers[0])), answers[0]])
sum1 = sum(a[answers[1], range(len(answers[1]))])
print('Cost of match:', sum1)
assert(sum0 == 17)
assert(sum1 == 17)
