# -*- coding: utf-8 -*-
"""
Created on Tue Feb 11 17:04:28 2020

@author: Owen Bartolf
"""

import numpy;

e = numpy.zeros((3,4))

e[0] = [12, 3, 1, 2]
e[1,0] = 0
e[:,1] = [3, 0, 2]
e[2, :2] = [4, 2]
e[2, 2:] = [3, 1] 
e[:,2] = [1, 1, 3]
e[1,3] = 2

print(e)