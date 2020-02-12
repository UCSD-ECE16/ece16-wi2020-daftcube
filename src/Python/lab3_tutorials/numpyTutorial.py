# -*- coding: utf-8 -*-
"""
Created on Tue Feb 11 09:14:47 2020

@author: Owen Bartolf
"""

import numpy

def numpyArray0():
    print("---------------------------")
    print("numpyArray0 Demo")
    test_list = [0,10,4,12]
    test_array = numpy.array(test_list)
    print(test_array)
    test_array = test_array - 20
    print(test_array)
    print("test_array is a " + str( test_array.shape ) + " matrix.")

def numpyArray1():
    print("---------------------------")
    print("numpyArray1 Demo")
    test_2d_array = numpy.array([[0,10,4,12], [1,20,3,41]])
    print(test_2d_array)
    print("test_2d_array is a " + str( test_2d_array.shape ) + " matrix.")

def numpyZeros():
    print("---------------------------")
    print("numpyZeros Demo")
    test_zeros_list = numpy.zeros((10,20))
    print(test_zeros_list)

def vhstackDemo():
    print("---------------------------")
    print("vhstack Demo")
    
    basicUnit = numpy.array([0, 10, 4, 12])
    horizontal = numpy.hstack((basicUnit, basicUnit))
    vertical = horizontal
    for i in range(3):
        vertical = numpy.vstack((vertical, horizontal))
    print(vertical)

def arangeDemo():
    print("---------------------------")
    print("arange Demo")
    arange_array1 = numpy.arange(-3, 16, 6) # Second parameter is exclusive
    arange_array2 = numpy.arange(-7, -20, -2)
    print(arange_array1)
    print(arange_array2)

def linspaceDemo():
    print("---------------------------")
    print("linspace Demo")
    linspace_array = numpy.linspace(0, 100, num=49)
    print(linspace_array)

def main():
    numpyArray0()
    numpyArray1()
    numpyZeros()
    vhstackDemo()
    arangeDemo()
    linspaceDemo()
    print(1/50 * 1000000)

if __name__== "__main__":
    main()

