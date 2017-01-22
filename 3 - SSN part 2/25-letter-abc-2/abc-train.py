#!/usr/bin/python
from fann2 import libfann as fann
import matplotlib.pyplot as plt
from timeit import default_timer as timer


learning_rate = 0.1
num_input = 24
num_layers = 4
num_output = 25
layers = [num_input, 20, num_output]
desired_error = 0.0000000000001
max_iterations = 300
#iterations_between_reports = 5

#data loading
data = fann.training_data()
data.read_train_from_file("train_data.data")
validation_data = fann.training_data()
validation_data.read_train_from_file("noise_data1.data")

#time & overall plot 
overall_fig = plt.figure()
overall_ax = overall_fig.add_subplot(111)
total_time_fig = plt.figure()
total_time_ax = total_time_fig.add_subplot(111)

TIME = []

for j in range(30):
	MSE = []
	validation_MSE = []
	err = float('inf')
	validation_err = float('inf')
	iterations = 0
	
	#creating fully connected backprop net
	ann = fann.neural_net()
	ann. create_standard_array(layers)
	ann.set_activation_function_output(fann.SIGMOID)
	ann.set_activation_function_hidden(fann.SIGMOID)
	
	temporary_fig = plt.figure()
	temporary_ax = temporary_fig.add_subplot(111)
	time_elapsed = 0.0
	
	while (err > desired_error) and (iterations <= max_iterations):
		start = timer()
		err = ann.train_epoch(data)
		stop = timer()
		time_elapsed += stop - start
		MSE.append(err)
		ann.save("net"+str(iterations)+".net")
		
		validation_err = ann.test_data(validation_data)
		validation_MSE.append(validation_err)
		iterations += 1
		
	TIME.append(time_elapsed)

	x = [i for i in range (0,len(MSE))]
	x_time = [i for i in range(0, len(TIME))]

	temporary_ax.plot(x,MSE)
	temporary_ax.plot(x,validation_MSE)
	overall_ax.plot(x,MSE)
	total_time_ax.plot(x_time, TIME)

plt.show()
