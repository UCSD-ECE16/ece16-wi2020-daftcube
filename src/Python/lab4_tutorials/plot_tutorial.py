# -*- coding: utf-8 -*-
"""
Created on Tue Feb 18 10:34:18 2020

@author: Owen Bartolf
"""

import matplotlib.pyplot as plt
import numpy as np

a = np.array([[1,2,3,4],[1,4,9,16]])
b = np.array([[1,2,3,4],[4,2,1,6]])
x = 0 #index from a to get [1,2,3,4]
y = 1 #index from a to get [1,4,9,16]

print(a[x])
print(a[y])

plt.clf()
plt.subplot(211)
plt.plot(a[0],a[1]) #fill in ax and ay
plt.subplot(212)
plt.plot(b[0],b[1]) #fill in bx and by
plt.show()

