#!/usr/bin/python
from fann2 import libfann as fann
import matplotlib.pyplot as plt




#neural net creation
ann = fann.neural_net()
ann.create_from_file("ABC.net")

MSE = []
for i in range(15):
	err = float('inf')
	data = fann.training_data()
	data.read_train_from_file("noise_data" + str(i) + ".data")
		
	err = ann.test_data(data)
	MSE.append(err)

x = [i for i in range (0,len(MSE))]

overal_fig = plt.figure()
overal_ax = overal_fig.add_subplot(111)
overal_ax.plot(x,MSE)
plt.ylabel("MSE")
plt.xlabel("Noise level")
plt.show()
