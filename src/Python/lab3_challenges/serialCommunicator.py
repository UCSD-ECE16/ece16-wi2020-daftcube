# -*- coding: utf-8 -*-
"""
Created on Tue Feb 11 18:44:13 2020

@author: Owen Bartolf
"""

import serial
import numpy as np

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
    
    while sample_count < 100:
        try:
            receive_sample(ser)
            
        except(KeyboardInterrupt):
            # Send stop data 
            ser.close() #we'll use ctrl+c to stop the program
            print("Exiting program due to KeyboardInterrupt")
            break
    # Send stop data 
    ser.write("stop data".encode('utf-8'))

def setup_serial():
    serial_name = 'COM7'
    ser = serial.Serial(serial_name, 115200)  # open serial port
    print(ser.name)         # check which port was really used
    return ser

def main():
    ser = setup_serial()
    ser.write("start data".encode('utf-8'))
    receive_data(ser)
    ser.close()


if __name__== "__main__":
    main()