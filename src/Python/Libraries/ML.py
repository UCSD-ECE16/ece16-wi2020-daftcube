# -*- coding: utf-8 -*-
"""
Created on Mon Mar  9 22:12:26 2020

@author: Owen Bartolf
"""

import glob
import numpy as np
import matplotlib.pyplot as plt
from sklearn.mixture import GaussianMixture as GMM


from HR import HR

class ML:
    
    # Default constructor
    def __init__(self):
        #self.hr = hr_instance
        self.hr = HR()
        
        # Initialize collections
        self.list_data = np.array([])
        self.list_sub = np.array([])
        self.list_ref = np.array([])
        
        # Create instance of GMM
        self.gmm = GMM(n_components=2)
        
        # Load data
        self.load_hr_data("ml_data\\training\\")
    
    def load_hr_data(self, directory):
        
        # Fetch unique IDs in directory
        all_files = glob.glob(directory + "*.csv")
        unique_ids = list(set([file.split("\\")[2][0:2] for file in set(all_files)]))
        
        self.list_data = np.array([])
        self.list_sub = np.array([])
        self.list_ref = np.array([])
        
        # print(unique_ids)
        
        for sub_id in unique_ids:
                
            # For each unique ID, get all sub files.
            sub_files = glob.glob(directory + "\\" + sub_id + "_*_*.csv")
            
            for sub_file in sub_files:
                # Load and splice data
                data_array = np.genfromtxt(sub_file, delimiter=",")
                heartrate_data = data_array[:,4]
                
                # Filter Data
                heartrate_data = self.hr.detrend(heartrate_data, 4)
                heartrate_data = self.hr.low_pass(heartrate_data, .065)
                heartrate_data = self.hr.normalize_signal(heartrate_data)
                
                # Append to list_data. Slice off any additional values
                if self.list_data.size > 0:
                    self.list_data = np.vstack((self.list_data, heartrate_data[:500]))
                else:
                    self.list_data = heartrate_data[:500]
                
                # Append subject id to list_sub
                self.list_sub = np.append(self.list_sub, int(sub_id))
                
                # Extract reference heartrate from file, then add to list_ref.
                heartrate_ref_string = sub_file.split("_")
                heartrate_ref = int(heartrate_ref_string[len(heartrate_ref_string) - 1].split(".")[0])
                
                self.list_ref = np.append(self.list_ref, heartrate_ref)
                
        
        print("Done")
    
    # Trains the HR model using the dataset in the given directory.
    def train_hr_model(self, train_ids):
        train_data = np.array([])
        hold_out_data = np.array([])
        
        hold_out_sub = train_ids[0] # For now we’ll hold out the first training subject
        
        for index, sub_id in enumerate(self.list_sub, 0):
            if sub_id != hold_out_sub:
                print(index)
                train_data = np.concatenate((train_data, self.list_data[index]))
            else:
                print(index)
                hold_out_data = np.concatenate((hold_out_data, self.list_data[index]))
        
        self.gmm = GMM(n_components=2).fit(train_data.reshape(-1, 1))
        test_pred = self.gmm.predict(hold_out_data.reshape(-1, 1))
        
        # plt.plot(test_pred)
        plt.plot(test_pred[1000:1500])
        plt.plot(hold_out_data[1000:1500])
        
        plt.show()
        
        print(self.calc_hr(hold_out_data[3000:3500], 50))
        
    # The Machine-learning specific algorithm to calculate the heart rate
    # Returns the heart rate
    def calc_hr(self, s, fs):
        analyzed_data = self.gmm.predict(s.reshape(-1,1))
        plt.plot(analyzed_data)
        plt.show()
        
        return self.hr.calc_heart_rate_time(s, fs)
    
    # Runs a test of the machine learning model using the data in the given directory.
    def test_hr_model(self, directory):
        pass
    
    def plot_training_data(self, directory):
        pass

ml = ML()

ml.load_hr_data("ml_data\\training\\")
ml.train_hr_model(ml.list_sub[0:10])

"""
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
"""