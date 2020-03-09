# -*- coding: utf-8 -*-
"""
Created on Sun Mar  8 21:40:36 2020

@author: Owen Bartolf
"""

import numpy as np
import matplotlib.pyplot as plt

def moving_average(s, n_avg):
    ma = np.zeros(s.size)
    for i in np.arange(0, len(s)):
        ma[i] = np.mean( s[i:(i + n_avg)] )    
    return ma

def detrend(s, n_avg):
    ma = moving_average(s, n_avg)
    return s - ma

data_array = np.genfromtxt('appendix_a.csv', delimiter=',')#get data from Appendix A and save as .csv.

fs = 50 #sampling rate in Hz
t = data_array[:, 0]  #get the time array
s = data_array[:, 1] #get the x-acceleration array
#s = detrend(s, 16) # We skip detrending.

Pxx, Freqs = plt.psd(s, NFFT=len(t), Fs=fs)

index_of_largest_freq = np.argmax(Pxx[2:])

largest_freq = Freqs[index_of_largest_freq]
print(index_of_largest_freq)
print(largest_freq)

plt.subplot(211)
plt.plot(t, s)
plt.subplot(212)
plt.psd(s, NFFT=len(t), Fs=fs) #plot the power spectral density
plt.show()
