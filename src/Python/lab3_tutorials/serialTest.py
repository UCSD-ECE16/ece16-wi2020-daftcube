# -*- coding: utf-8 -*-
"""
Created on Tue Feb  4 10:11:13 2020

@author: Owen Bartolf
"""

import serial

def setup_serial():
    serial_name = 'COM5'
    ser = serial.Serial(serial_name, 115200)  # open serial port
    print(ser.name)         # check which port was really used
    return ser

def send_serial(ser):    
    S_List = ['Hello',' World','!','\n']

    for S in S_List:
        ser.write(S)

def read_serial1(ser):
    s = ser.read(30).decode('utf-8')     # read 30 bytes and decode it
    print(s)

def read_serial2(ser):
    n=0
    while (n<30):
        s = ser.read(1).decode('utf-8')     # read 1 byte and decode it
        print(s)
        n=n+1

def read_serial3(ser):
    n=0
    full_string = []
    while (n<30):
        s = ser.read(1).decode('utf-8')     # read 1 byte and decode it
        full_string.append(s)
        n=n+1
        
    print(full_string)

def read_serial4(ser):
    while True:
        try:
            s = ser.read(1)         # read 1 byte and decode to utf-8
            print(s)
        except(KeyboardInterrupt):
            ser.close() #we'll use ctrl+c to stop the program
            print("Exiting program due to KeyboardInterrupt")
            break


def main():
    ser = setup_serial()
    read_serial4(ser)
    ser.close()


if __name__== "__main__":
    main()
