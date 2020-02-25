# -*- coding: utf-8 -*-
"""
Created on Tue Feb 11 18:44:13 2020

@author: Owen Bartolf
"""

import serial
import numpy as np
import matplotlib.pyplot as plt

#Make the variables below global
string_buffer = []
data_array = np.array([])
sample_count = 0

def receive_sample(ser):
    
    global string_buffer
    global data_array
    global sample_count
    
    byte_recv = ser.read(1).decode('utf-8')
    
    # read a byte from serial (remember to decode)
    if( byte_recv == '\n'):
        
        data_string = "".join(string_buffer)
        print(data_string)
        temp_data_array = np.fromstring(data_string, sep=',')
        
        if(data_array.size == 0): 
            data_array = temp_data_array
        else:
            data_array = np.vstack((data_array, temp_data_array))
        
        sample_count = sample_count + 1
        
        # Clear string buffer
        string_buffer = []
    else:
        # append the new char to string_buffer
        string_buffer.extend(byte_recv)
        
def receive_data(ser):
    global sample_count
    
    while sample_count < 50*10:
        try:
            receive_sample(ser)
            
        except(KeyboardInterrupt):
            # Send stop data 
            ser.close() #we'll use ctrl+c to stop the program
            print("Exiting program due to KeyboardInterrupt")
            break

# Returns Milliseconds
def calc_sampling_rate():
    global data_array
    
    difference = np.diff(data_array, 1, 0)
    np.set_printoptions(precision=3)
    mean = np.mean(difference[:,0])
    return mean / 1000

def plot():
    global data_array
    
    np.savetxt("foo.csv", data_array, delimiter=",")
    data_array_from_file = np.genfromtxt('foo.csv', delimiter=',')

    
    plt.clf()
    fig, axs = plt.subplots(3)
    
    plt.subplot(411)
    plt.plot(data_array_from_file[:,0], data_array_from_file[:,1])    
    
    plt.title("Accelerometer Data")
    plt.ylabel("X Amplitude")
    
    plt.subplot(412)
    plt.plot(data_array_from_file[:,0], data_array_from_file[:,2])
    plt.ylabel("Y Amplitude")
    
    plt.subplot(413)
    plt.plot(data_array_from_file[:,0], data_array_from_file[:,3])
    plt.ylabel("Z Amplitude")
    
    plt.subplot(414)
    plt.plot(data_array_from_file[:,0], -data_array_from_file[:,4])
    plt.ylabel("Red")
    plt.xlabel("Time Sampled")
    
    
    plt.show()

    # plot_z(data_array_from_file)
    
def remove_mean_offset(s):
    mean_s = np.mean(s)
    s = s - mean_s
    
    return s

def moving_average(s, n_avg):
    ma = np.zeros(s.size)
    for i in np.arange(0, len(s)):
        ma[i] = np.mean( s[i:(i + n_avg)] )    
    return ma

def detrend(s, n_avg):
    ma = moving_average(s, n_avg)
    return s - ma

def signal_diff(s):
    s_diff = np.diff(s)
    s_diff = np.append(s_diff, 0) #np.diff returns one shorter, so need to add a 0
    #remember to return s_diff
    return s_diff


def calc_heart_rate_time(signal, fs):
    global data_array
    
    # invert source
    signal = -signal
    
    #filter the signal to remove baseline drifting
    signal = detrend(signal, 16)
    
    #filter the signal to remove high frequency noise
    signal = moving_average(signal, 8)
    
    # get standard deviation and remove all values exceeding 2 standard deviations from the mean.
    #std_dev = np.std(signal) 
    #signal = np.clip(signal, -std_dev * 1.75, std_dev * 1.75)

    #Normalize the signal between 0 and 1
    signal = normalize_signal(signal)
    
    #Explore using the signal directly or potentially using the diff of the signal. 
    
    plt.clf()
    plt.plot(data_array[:,0], signal)
    plt.show()
    
    #########################################################
    
    threshold = 0.5
    goingUp = signal[0] < threshold
    crossings = 0
    
    #Count the number of times the signal crosses a threshold.
    for i in range(signal.size):
        current_sample = signal[i]
        
        if goingUp and current_sample > threshold:
            goingUp = False
            crossings = crossings + 1
        else:
            if not goingUp and current_sample < threshold:
                goingUp = True
                crossings = crossings + 1
    
    # Calculate the beats per minute.
    time_to_get_samples = (1/fs) * signal.size
    print(time_to_get_samples)
    
    return ((crossings/2) * 60) / time_to_get_samples

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

def linear_map(a1, a2, b1, b2, s):
    return b1 + (((s - a1) * (b2 - b1))/(a2 - a1))

def setup_serial():
    serial_name = 'COM5'
    ser = serial.Serial(serial_name, 115200)  # open serial port
    print(ser.name)         # check which ports was really used
    return ser

def main():
    global data_array
    
    ser = setup_serial()
    ser.write("start data\n".encode('utf-8'))
    receive_data(ser)
    ser.write("stop data\n".encode('utf-8'))
    ser.close()
    
    sampRate = calc_sampling_rate()
    print("The latency was " + str(sampRate))
    print("The frequency was " + str(1/(sampRate/1000)))

    plot()
    print(calc_heart_rate_time(data_array[:,4], 1/(sampRate/1000)))
        

if __name__== "__main__":
    main()