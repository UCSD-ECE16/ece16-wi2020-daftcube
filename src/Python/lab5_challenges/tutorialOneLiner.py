# -*- coding: utf-8 -*-
"""
Created on Mon Mar  9 23:40:48 2020

@author: Owen Bartolf
"""

import glob

directory = "ml_data/"

all_files = glob.glob(directory + "*.csv")

just_0 = glob.glob(directory + "/*_01_*.csv")
for file in just_0:
    print(file)

# THE GRAND ONE LINER, WITH UNIT TEST

# One liner, string comprehension.    
unique = list(set([file.split("\\")[1][0:2] for file in set(all_files)]))

# UNIT TEST
# TEST 1: NUMBERS

failed_test = False

print("TEST 1: NUMBERS IN LIST")
for i in range(1, 13):
    test_condition = "{:02d}".format(i)
    
    test_result = test_condition in unique
    print("Has " + str(test_condition) + "? " + str(test_result))
    if not(test_result):
        print("FAILED TEST " + str(i))
        failed_test = True
        break

# TEST 2: IS A LIST

print("TEST 2: IS LIST")
if type(unique) == list:
    print("Is List? True")
else:
    print("FAILED TEST: NOT A LIST")
    failed_test = True
    
if not(failed_test):
    print("All tests succeeded! 2 Points Please!")