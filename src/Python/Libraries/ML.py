# -*- coding: utf-8 -*-
"""
Created on Mon Mar  9 22:12:26 2020

@author: Owen Bartolf
"""

import glob
import numpy as np
import matplotlib.pyplot as plt
from sklearn.mixture import GaussianMixture as GMM
from scipy.stats import pearsonr

from HR import HR

class ML:
    
    # Default constructor
    def __init__(self, heartrate_instance):
        #self.hr = hr_instance
        self.hr = heartrate_instance
        
        # Constant: Test Freq
        self.TEST_FREQUENCY = 50 # 50 hz
        
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
                heartrate_data = self.filter_ml_data(heartrate_data)
                
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
    
    # Trains the HR model using the given ids
    def train_hr_model(self, train_ids):
        train_data = np.array([])
        hold_out_data = np.array([])
        
        hold_out_sub = train_ids[0] # For now we’ll hold out the first training subject
        
        for index, sub_id in enumerate(self.list_sub, 0):
            if sub_id != hold_out_sub:
                train_data = np.concatenate((train_data, self.list_data[index]))
            else:
                hold_out_data = np.concatenate((hold_out_data, self.list_data[index]))
        
        self.gmm = GMM(n_components=2).fit(train_data.reshape(-1, 1))
        test_pred = self.gmm.predict(hold_out_data.reshape(-1, 1))
        
        # plt.plot(test_pred)
        plt.plot(test_pred[1500:2500])
        plt.plot(hold_out_data[1500:2500])
        
        plt.show()
        
        print(self.calc_hr(hold_out_data[1500:2500], 50))
        
    # The Machine-learning specific algorithm to calculate the heart rate
    # Returns the heart rate
    def calc_hr(self, s, fs):
        analyzed_data = self.gmm.predict(s.reshape(-1,1))
        plt.plot(s)
        plt.plot(analyzed_data)
        plt.show()
        
        threshold = 0.5
        goingUp = s[0] < threshold
        crossings = 0
        
        #Count the number of times the signal crosses a threshold.
        for i in range(s.size):
            current_sample = s[i]
            
            if goingUp and current_sample > threshold:
                goingUp = False
                crossings = crossings + 1
            else:
                if not goingUp and current_sample < threshold:
                    goingUp = True
                    crossings = crossings + 1
        
        # Calculate the beats per minute.
        time_to_get_samples = (1/fs) * s.size
        
        return ((crossings/2) * 60) / time_to_get_samples
    
    
    # Runs a test of the machine learning model using the data in the given directory.
    def test_hr_model(self, directory):
        # Fetch unique IDs in directory
        all_files = glob.glob(directory + "*.csv")
        unique_ids = list(set([file.split("\\")[2][0:2] for file in set(all_files)]))
        
        self.list_test_data = np.array([])
        self.list_test_sub = np.array([])
        self.list_test_ref = np.array([])
        self.list_test_result = np.array([])
        
        for sub_id in unique_ids:
                
            # For each unique ID, get all sub files.
            sub_files = glob.glob(directory + "\\" + sub_id + "_*_*.csv")
            
            for sub_file in sub_files:
                # Load and splice data
                data_array = np.genfromtxt(sub_file, delimiter=",")
                heartrate_data = data_array[:,4]
                
                # Filter Data
                heartrate_data = self.filter_ml_data(heartrate_data)
                
                # Append to list_data. Slice off any additional values
                if self.list_test_data.size > 0:
                    self.list_test_data = np.vstack((self.list_test_data, heartrate_data[:500]))
                else:
                    self.list_test_data = heartrate_data[:500]
                
                # Append subject id to list_sub
                self.list_test_sub = np.append(self.list_test_sub, int(sub_id))
                
                # Extract reference heartrate from file, then add to list_ref.
                heartrate_ref_string = sub_file.split("_")
                heartrate_ref = int(heartrate_ref_string[len(heartrate_ref_string) - 1].split(".")[0])
                
                self.list_test_ref = np.append(self.list_test_ref, heartrate_ref)
                
                # Get Result
                self.list_test_result = np.append(self.list_test_result, self.calc_hr( heartrate_data[:500], self.TEST_FREQUENCY ))
        
        # Render plot
        self.render_bland_altman_plot(self.list_test_ref, self.list_test_result)
        

    # Renders a Bland-Altman plot, where gnd is the known truths and est is the estimate from our algorithm.
    def render_bland_altman_plot(self, gnd, est):
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
        rmse = np.sqrt( np.mean( ( gnd - est ) ** 2 ))
        
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
        
        print("rmse: " + str(rmse))
        print("std: " + str(std))
        print("R: " + str(R))
        print("bias: " + str(bias))
        
        
    
    # The filtering function for ML stuff
    def filter_ml_data(self, heartrate_data):
        heartrate_data = -heartrate_data
        heartrate_data = self.hr.detrend(heartrate_data, 4)
        heartrate_data = self.hr.low_pass(heartrate_data, .065)
        heartrate_data = self.hr.normalize_signal(heartrate_data)
        return heartrate_data


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