# -*- coding: utf-8 -*-
"""
Created on Mon Mar  9 00:53:13 2020

@author: Owen Bartolf
"""

from scipy import signal
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure
import os

figure(num=None, figsize=(8, 12), dpi=80, facecolor='w', edgecolor='k')

def moving_average(s, n_avg):
    ma = np.zeros(s.size)
    for i in np.arange(0, len(s)):
        ma[i] = np.mean( s[i:(i + n_avg)] )    
    return ma

def detrend(s, n_avg):
    ma = moving_average(s, n_avg)
    return s - ma

files = os.listdir("C:\\_Repositories\\ece16-wi2020-daftcube\\src\\Python\\lab5_challenges\\personal_heartrate_data")

# Grid initialization
grid = plt.GridSpec(10, 2,wspace=0.4,hspace=1)

# Render plots for all files
grid_row = 0

for file in files:
    print(file)
    data_array = np.genfromtxt("personal_heartrate_data\\" + file, delimiter=',')
    
    # Grab data
    t = data_array[:, 0]  # get the time array
    s = data_array[:, 4]  # get the heart rate array
    
    # Detrend and filter with low-pass
    s = detrend(s, 8)
    b,a = signal.butter(3, .1, btype='low') # currently high pass
    s_filt = signal.lfilter(b,a,s)
    
    # Heartrate reading, time domain filtered.
    plt.subplot(grid[grid_row,0])
    plt.xlabel("Time")
    plt.ylabel("PPG Reading")
    plt.plot(t, s_filt)
    
    # PSD of heartrate
    plt.subplot(grid[grid_row,1])
    Pxx, Freqs = plt.psd(s, NFFT=len(t), Fs=47.2)
    
    # Calculate dominant frequency
    highest_freq_index = np.argmax(Pxx)
    highest_freq = Freqs[highest_freq_index]
    print("Dominant Index: " + str(highest_freq_index) + ", Dominant Freq: " + str(highest_freq))
    
    grid_row = grid_row + 1
plt.show()