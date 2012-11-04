#!/usr/bin/env python

## Thanks to Dr N.D. van Foreest for providing this example code. ##


"""
The cost matrix is based on Balas and Toth, 1985, Branch and bound
# methods, in Lawler, E.L, et al., The TSP, John Wiley & Sons,
Chischester, pp 361--401.
"""

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

print  hungarian.lap(a)[0]

