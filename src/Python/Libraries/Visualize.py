import numpy as np
import matplotlib.pyplot as plt

class Visualize:
    def plotData(data_array):
        plt.clf()
        fig, axs = plt.subplots(3)
        
        plt.subplot(411)
        plt.plot(data_array[:,0], data_array[:,1])    
        
        plt.title("Accelerometer Data")
        plt.ylabel("X Amplitude")
        
        plt.subplot(412)
        plt.plot(data_array[:,0], data_array[:,2])
        plt.ylabel("Y Amplitude")
        
        plt.subplot(413)
        plt.plot(data_array[:,0], data_array[:,3])
        plt.ylabel("Z Amplitude")
        
        plt.subplot(414)
        plt.plot(data_array[:,0], -data_array[:,4])
        plt.ylabel("Red")
        plt.xlabel("Time Sampled")

        plt.show()
        
    def plotAccel(data_array):
        plt.clf()
        fig, axs = plt.subplots(3)
        
        plt.subplot(311)
        plt.plot(data_array[:,0], data_array[:,1])    
        
        plt.title("Accelerometer Data")
        plt.ylabel("X Amplitude")
        
        plt.subplot(312)
        plt.plot(data_array[:,0], data_array[:,2])
        plt.ylabel("Y Amplitude")
        
        plt.subplot(313)
        plt.plot(data_array[:,0], data_array[:,3])
        plt.ylabel("Z Amplitude")

    def plotHr(data_array):
        # plot the heart pulse data
        plt.clf()
        
        plt.plot(data_array[:,0], -data_array[:,4])
        plt.ylabel("Red")
        plt.xlabel("Time Sampled")

        plt.show()



