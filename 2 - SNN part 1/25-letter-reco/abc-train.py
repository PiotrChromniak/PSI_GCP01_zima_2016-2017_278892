#!/usr/bin/python
from fann2 import libfann as fann
import matplotlib.pyplot as plt

connection_rate = 1
learning_rate = 0.1
num_input = 24
num_layers = 4
num_hidden = 48
num_output = 25

desired_error = 0.0001
max_iterations = 100
iterations_between_reports = 5

#data loading
data = fann.training_data()
data.read_train_from_file("train_data.data")
validation_data = fann.training_data()
validation_data.read_train_from_file("noise_data1.data")

overal_fig = plt.figure()
overal_ax = overal_fig.add_subplot(111)


for j in range(30):
	MSE = []
	validation_MSE = []
	err = float('inf')
	validation_err = float('inf')
	iterations = 0
	

	ann = fann.neural_net()
	ann.create_sparse_array(connection_rate, (num_input, num_hidden, num_output))
	ann.set_learning_rate(learning_rate)
	ann.set_activation_function_output(fann.SIGMOID_STEPWISE)
	ann.set_activation_function_hidden(fann.SIGMOID_STEPWISE)
	
	temporary_fig = plt.figure()
	temporary_ax = temporary_fig.add_subplot(111)
	
	while (err > desired_error) and (iterations <= max_iterations):
		err = ann.train_epoch(data)
		MSE.append(err)
		err = ann.get_MSE()
		ann.save("net"+str(iterations)+".net")
		
		validation_err = ann.test_data(validation_data)
		validation_MSE.append(validation_err)
		iterations += 1
		
	x = [i for i in range (0,len(MSE))]
	temporary_ax.plot(x,MSE)
	temporary_ax.plot(x,validation_MSE)
	overal_ax.plot(x,MSE)

plt.show()