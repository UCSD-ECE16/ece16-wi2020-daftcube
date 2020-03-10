# -*- coding: utf-8 -*-
"""
Created on Mon Mar  9 13:43:03 2020

@author: Owen Bartolf
"""

from scipy.stats import pearsonr
from scipy import signal as sig
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure
import os

from HR import HR 

hr = HR()

files = os.listdir("C:\\_Repositories\\ece16-wi2020-daftcube\\src\\Python\\lab5_challenges\\personal_heartrate_data")

est_time = np.array([])
est_freq = np.array([])
gnd = np.array([77, 81, 74, 72, 78, 107, 91, 101, 102, 95]) #reference heart rate

for file in files:
    print("-----")
    print("FILE: " + file)
    data_array = np.genfromtxt("personal_heartrate_data\\" + file, delimiter=',')
    
    # Grab Actual Heartrate
    actual_heart_rate = float( file[3:6] )
    print("ACTUAL: " + str(actual_heart_rate))
    
    # Grab data
    t = data_array[:, 0]  # get the time array
    s = data_array[:, 4]  # get the heart rate array
    fs = 50
    
    heart_rate_time = hr.calc_heart_rate_time(s, fs)
    heart_rate_freq = hr.calc_heart_rate_freq(s, fs)
    print( "HR_TIME: " + str(round(heart_rate_time)))
    print( "HR_FREQ: " + str(round(heart_rate_freq)))
    
    est_time = np.append(est_time, [heart_rate_time])
    est_freq = np.append(est_freq, [heart_rate_freq])

print("TIME")

est = est_time

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

print("TIME BIAS: " + str(bias))

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

print("FREQ")

est = est_freq

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

print("FREQ BIAS: " + str(bias))

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

# RMSE Calculation

rmse_time = np.sqrt( np.mean( ( gnd - est_time ) ** 2 ))
rmse_freq = np.sqrt( np.mean( ( gnd - est_freq ) ** 2 ))

print( "RMSE TIME: " + str(rmse_time) )
print( "RMSE FREQ: " + str(rmse_freq) )