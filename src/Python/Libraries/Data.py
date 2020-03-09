import numpy as np
from scipy import signal

class Data:
    
    def __init__(self):
        self.data_array = np.array([])
    
    def get_data(self):
        return self.data_array
    
    def add_data(self, new_data):
        #check the number of samples using get_num_samples and add the new data into the data_array accordingly. 
        temp_data_array = new_data
        
        if(self.get_num_samples() == 0): 
            self.data_array = temp_data_array
        else:
            self.data_array = np.vstack((self.data_array, temp_data_array))

    def clear_data(self):
        # reset data_array to empty np array
        self.data_array = np.array([])

    def get_num_samples(self):
        #the size of data_array
        if self.data_array.size > 0:
            return self.data_array.shape[0]
        else:
            return 0
        
    def calc_sampling_latency(self):
        difference = np.diff(self.data_array, 1, 0)
        np.set_printoptions(precision=3)
        mean = np.mean(difference[:,0])
        return mean / 1000
    
    def calc_sampling_frequency(self):
        return 1 / (self.calc_sampling_latency() / 1000)


