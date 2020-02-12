# -*- coding: utf-8 -*-
"""
Created on Tue Feb 11 17:14:29 2020

@author: Owen Bartolf
"""

import numpy

data_string = '1,2,3,4'
data_as_array = numpy.fromstring(data_string, dtype=int, sep=',')
stack_array = data_as_array[:]

for i in range(100):
    data_as_array = numpy.vstack((data_as_array, stack_array))

print(data_as_array)