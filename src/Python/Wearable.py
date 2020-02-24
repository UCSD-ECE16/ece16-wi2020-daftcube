from Libraries.Data import Data 
from Libraries.HR import HR 
from Libraries.Visualize import Visualize 
from Libraries.Connection import Connection 

class Wearable:
    def __init__(self, serial_name, baud_rate):
        self.connection = Connection(serial_name, baud_rate)
        self.HR = HR()

    def collect_data(self, num_samples):
        #first make sure data sending is stopped by ending streaming
        self.connection.end_streaming()

        #start sending data
        self.connection.start_streaming()
        
        while self.connection.data.get_num_samples() < num_samples: #collect x samples
            try:
                #receive data
                self.connection.receive_data()

            except(KeyboardInterrupt):
                #deal with exception
                break

        #end streaming
        self.connection.end_streaming()
        
        # Return data read!
        return self.connection.get_data_field().get_data()

    def main(self):
        
        SAMPLES_TO_COLLECT = 500

        data_array = self.collect_data(SAMPLES_TO_COLLECT) #number of samples to collect
        
        self.connection.close_connection()
        
        # calculate sampling rate
        sampling_rate = self.connection.data.calc_sampling_frequency()
        
        # save data 
        self.HR.save_to_file(data_array)
        
        # read data
        data_array = self.HR.load_from_file("foo.csv")
        
        # Extract HR reading
        data_array1 = data_array[:,3]
        
        # Process
        data_array1 = self.HR.calc_heart_rate_time(data_array1, sampling_rate)
        
        Visualize.plotData(data_array)
        

def main():
    wearable = Wearable("COM5", 115200)
    wearable.main()

if __name__== "__main__":
    main()
