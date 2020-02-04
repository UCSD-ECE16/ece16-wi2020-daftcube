import serial

# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

def main():
    
    # A
    a = "Hello World!!!"
    print(a)
    
    # Get B, C, D
    b = a[0:5]
    c = a[6:11]
    d = a[11:14]
    
    print(b)
    print(c)
    print(d)
    
    if "ello" in a:
        print("ello is in a!")
    
    hiHowAreYou()

def hiHowAreYou():
    original_list = ['hi',1,2,'you']
    new_list = original_list
    newer_list = new_list[1:3]
    newer_list[0:2] = ['how','are']
    print(original_list)

if __name__ == "__main__":
    main()


