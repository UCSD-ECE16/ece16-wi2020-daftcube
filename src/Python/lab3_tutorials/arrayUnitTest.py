# -*- coding: utf-8 -*-
"""
Created on Tue Feb 11 16:23:12 2020

@author: Owen Bartolf
"""

import numpy

e = numpy.array([
            [12, 3, 1, 2],
            [0, 0, 1, 2],
            [4, 2, 3, 1]
        ])

print("Unit testing e for challenge fulfillment!")
print("e[0] == [12, 3, 1, 2]?   " + str(numpy.array_equal(e[0], [12, 3, 1, 2])))     # >>> [12 3 1 2] – Direct Index
print("e[1,0] == 0?             " + str(e[1,0] == 0) )   # >>> 0 – Direct Index
print("e[:,1]) == [3, 0, 2]?    " + str(numpy.array_equal(e[:,1], [3, 0, 2])))    # >>> [3 0 2]
print("e[2, :2] == [4, 2]?      " + str(numpy.array_equal(e[2, :2], [4, 2]))) # >>> [4 2]
print("e[2, 2:] == [3, 1]?      " + str(numpy.array_equal(e[2, 2:], [3, 1]))) # >>> [3 1] 
print("e[:,2] == [1, 1, 3]?     " + str(numpy.array_equal(e[:,2], [1, 1, 3])))   # >>> [1 1 3]
print("e[1,3] == 2?             " + str(e[1,3] == 2))   # >>> 2 – Direct Index
print("If any were false, then it was not successful. Otherwise, we're good!")