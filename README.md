# Computational Intelligence(Artificial Neural Networks)

Programming exercises for CSE035 - Computational Intelligence, Computer Science and Engineering University of Ioannina

# Implementation of training and test set

The code file set1.cpp implemetents a data set of random 6000 points inside the box [-2,2]x[-2,2] 
for supervised learning. The first 3000 points are used for the training set, while the other 3000 for
the test set. Each data point has a certain label from the set {"C1","C2","C3"}. Some point also have some noise.

The code file set2.cpp implemetents a data set of random 600 points for unsupervised learning.
For every 100 points there is a different method of creating the data points. For examble, the first
100 points are inside a circle with its centre is the point (0,0) and radious 0.3.

# Supervised Learning

For the supervised learning the method that was implemented is the Multi-Layer Perceptron(MLP)
network. The MLP network has two hidden layers with H1 neurons and H2 neurons respectively. The neurons
use as activation function either the Hyperbolic fuction or the Linear function. The input layer has two neurons
hence the data points are two-dimensional. The output layer has three neurons to identify the label of the point.

   # Multi-Layer Perceptron Network
   
   In general, the MLP network is a feedforward network. Multi-layering aid in difficult mathematical
   analysis and also benefits from parallel processing. In case of the training process, a MLP network
   uses the backprobagation method. Fisrt of all, we have the training set D ={(xn,tn)}. Through this set,
   the weights of the network should change in order to achieve maximum generalization. The weights change
   with the use of gradient descent.
   
# Unsupervised Learning
