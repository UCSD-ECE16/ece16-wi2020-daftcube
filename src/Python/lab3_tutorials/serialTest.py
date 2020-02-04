# -*- coding: utf-8 -*-
"""
Created on Tue Feb  4 10:11:13 2020

@author: Owen Bartolf
"""

import serial

def setup_serial():
    serial_name = 'name of your serial port'
    ser = serial.Serial(serial_name, 9600)  # open serial port
    print(ser.name)         # check which port was really used
    return ser

def send_serial(ser):
    S = 'Hello World\n'         
    ser.write(S.encode('utf-8'))         # write a string

def main():
    ser = setup_serial()
    send_serial(ser)
    ser.close()

if __name__== "__main__":
    main()
