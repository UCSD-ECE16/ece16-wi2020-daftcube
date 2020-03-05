# -*- coding: utf-8 -*-
"""
Created on Thu Mar  5 09:40:01 2020

@author: Not Owen Bartolf
"""

import numpy as np
from scipy.stats import pearsonr
import matplotlib.pyplot as plt

#gnd = np.array([77, 81, 74, 72, 78, 107, 91, 101, 102, 95]) #reference heart rate
#est = np.array([82.116, 71.167, 76.642, 73.904, 71.167, 99.873, 93.065, 98.539, 95.802, 90.328]) #estimate of your algorithm
est = np.array([-10, 102, 50, 220, 1, 78, 22, 54, 109, 200])
gnd = np.array([70, 72, 80, 83, 85, 90, 108, 101, 95, 91])

[R,p] = pearsonr(gnd,est)

plt.figure(1)
plt.clf()
plt.subplot(121)
plt.plot(gnd,gnd)
plt.scatter(gnd,est)
plt.text(min(gnd) + 2,max(est)+2,"R="+str(round(R,2)))
plt.ylabel("estimate HR (BPM)")
plt.xlabel("reference HR (BPM)")

avg = (gnd + est) / 2 #take the average of gnd and est
dif = gnd - est #take the difference of gnd and est
std = np.std(dif) #get the standard deviation of the difference (using np.std)
bias = np.mean(dif) #the mean value of the difference
upper_std = bias + 1.96 * std #the bias plus 1.96 times the std
lower_std = bias - 1.96 * std #the bias minus 1.96 times the std

plt.subplot(122)
plt.scatter(avg, dif)
plt.plot([np.min(avg),np.max(avg)],[bias,bias])
plt.plot([np.min(avg),np.max(avg)],[upper_std, upper_std])
plt.plot([np.min(avg),np.max(avg)],[lower_std, lower_std])
plt.text(np.max(avg)+5,bias,"mean="+str(round(np.mean(gnd-est),2)))
plt.text(np.max(avg)+5,upper_std,"1.96STD="+str(round(upper_std,2)))
plt.text(np.max(avg)+5,lower_std,"-1.96STD="+str(round(lower_std,2)))
plt.ylabel("Difference of Est and Gnd (BPM)")
plt.xlabel("Average of Est and Gnd (BPM)")
plt.show()

print("avg: " + str(avg))
print("std: " + str(std))
print("R: " + str(R))
print("bias: " + str(bias))

