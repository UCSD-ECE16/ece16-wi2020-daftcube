from Libraries.Data import Data 
from Libraries.HR import HR 
from Libraries.Visualize import Visualize 
from Libraries.Connection import Connection 
from Libraries.ML import ML

class Wearable:
    def __init__(self, serial_name, baud_rate):
        self.connection = Connection(serial_name, baud_rate)
        self.HR = HR()
        self.ml = ML(self.HR)

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
        
        # Return data read and reset!
        data = self.connection.get_data_field().get_data()

        self.connection.get_data_field().clear_data()

        return data

    def main(self):
        
        
        # calculate sampling rate
        """sampling_rate = self.connection.data.calc_sampling_frequency()
        
        # save data 
        self.HR.save_to_file(data_array)
        
        # read data
        data_array = self.HR.load_from_file("foo.csv")
        
        # Extract HR reading
        data_array1 = data_array[:,3]
        
        # Process
        data_array1 = self.HR.calc_heart_rate_time(data_array1, sampling_rate)
        
        print(sampling_rate)
        
        Visualize.plotData(data_array)
        """

        # Train ML before execution

        self.ml.load_hr_data("ml_data\\training\\")
        self.ml.train_hr_model(self.ml.list_sub[0:10])
        self.ml.test_hr_model("ml_data\\testing\\")
        
        while True:
            print("Please enter a command: ")
            command = input()
            if command == "READ":        
                SAMPLES_TO_COLLECT = 500
                
                # RAW DATA
                data_array = self.collect_data(SAMPLES_TO_COLLECT) #number of samples to collect
                
                processed_array = self.ml.filter_ml_data(data_array[:,4])
                
                print("Your heart rate is... " + str(self.ml.calc_hr(processed_array, self.ml.TEST_FREQUENCY)))
                
            if command == "CLOSE":
                print("Goodbye!")
                self.connection.close_connection()
                break

def main():
    wearable = Wearable("COM5", 230400)
    wearable.main()

if __name__== "__main__":
    main()
