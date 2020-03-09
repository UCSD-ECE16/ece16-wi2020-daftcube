# -*- coding: utf-8 -*-
"""
Created on Mon Mar  9 00:11:14 2020

@author: Owen Bartolf
"""

from scipy import signal
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

def normalize_signal(signal):
        
    #find min of signal
    minimum = np.min(signal)
        
    #subtract the minimum so the minimum of the signal is zero
    signal = signal - minimum

    #find the new maximum of the signal
    maximum = np.max(signal)

    #divide the signal by the new maximum so the maximum becomes 1
    signal = signal / maximum
        
    return signal

#b, a = signal.butter(filter_order, filter_cutoff, btype='low')
#s_filt = signal.lfilter(b,a,s)

data_array = np.genfromtxt('appendix_a.csv', delimiter=',')#get data from Appendix A and save as .csv.

fs = 50 #sampling rate in Hz
t = data_array[:, 0]  #get the time array
s = data_array[:, 1] #get the x-acceleration array


"""
plt.subplot(211)
plt.plot(t, s)
plt.subplot(212)
plt.psd(s, NFFT=len(t), Fs=fs) #plot the power spectral density
plt.show()
"""

plt.style.use('seaborn-white')

grid = plt.GridSpec(3,4,wspace=0.4,hspace=0.3)

# Filter response of low-pass filter
s = detrend(s, 8)
b,a = signal.butter(3, .1, btype='low') # currently high pass
s_filt = signal.lfilter(b,a,s)

plt.subplot(grid[0,:])

w, h = signal.freqz(b,a)
plt.plot(w, 20 * np.log10(abs(h)))

# Original Signal of the pulse signal
plt.subplot(grid[1,0:2])
plt.plot(t, s)

# PSD of the original Signal
plt.subplot(grid[1,2:4])
Pxx, Freqs = plt.psd(s, NFFT=len(t), Fs=fs)

# Filtered pulse signal
plt.subplot(grid[2,0:2])
plt.plot(t, s_filt)

# PSD of filtered signal
plt.subplot(grid[2,2:4])
Pxx, Freqs = plt.psd(s_filt, NFFT=len(t), Fs=fs)





plt.show()