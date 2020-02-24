import numpy as np

class HR:
    
    def remove_mean_offset(self, s):
        mean_s = np.mean(s)
        s = s - mean_s
        
        return s

    def moving_average(self, s, n_avg):
        ma = np.zeros(s.size)
        for i in np.arange(0, len(s)):
            ma[i] = np.mean( s[i:(i + n_avg)] )    
        return ma

    def detrend(self, s, n_avg):
        ma = self.moving_average(s, n_avg)
        return s - ma

    def signal_diff(s):
        s_diff = np.diff(s)
        s_diff = np.append(s_diff, 0) #np.diff returns one shorter, so need to add a 0
        #remember to return s_diff
        return s_diff


    def calc_heart_rate_time(self, signal, fs):

        # invert source
        signal = -signal
        
        #filter the signal to remove baseline drifting
        signal = self.detrend(signal, 16)
        
        #filter the signal to remove high frequency noise
        signal = self.moving_average(signal, 8)
        
        # get standard deviation and remove all values exceeding 2 standard deviations from the mean.
        #std_dev = np.std(signal) 
        #signal = np.clip(signal, -std_dev * 1.75, std_dev * 1.75)

        #Normalize the signal between 0 and 1
        signal = self.normalize_signal(signal)
        
        #Explore using the signal directly or potentially using the diff of the signal. 

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
        
        return ((crossings/2) * 60) / time_to_get_samples

    def normalize_signal(self, signal):
        
        #find min of signal
        minimum = np.min(signal)
        
        #subtract the minimum so the minimum of the signal is zero
        signal = signal - minimum
        #find the new maximum of the signal
        maximum = np.max(signal)
        
        #divide the signal by the new maximum so the maximum becomes 1
        signal = signal / maximum
        
        return signal

    def linear_map(self, a1, a2, b1, b2, s):
        return b1 + (((s - a1) * (b2 - b1))/(a2 - a1))

    def save_to_file(self, data_array, file_name = "foo.csv"):
        np.savetxt(file_name, data_array, delimiter=",")

    def load_from_file(self, file_name):
        return np.genfromtxt(file_name, delimiter=',')