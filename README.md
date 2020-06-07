# Assignment Seven: PLLKIA010

## Makefile
The purpose of the Makefile is to automatically compile and link the C++ source files into a binary executable that can be run locally. Run these commands in sequence to interact with the program.
```make``` will compile the files into an executable called ```driver```

```make run``` will run the executable and write the Neural Network prediction results to the console.
Answers to the assignment questions are contained in the ```results.txt``` file.

## neural_network.h

This is a header file that contains the ```NeuralNetwork``` Class declaration. This class provides the major functionality. The class consists of several member variables that store: the number of layers in the neural network (excluding input layer), the learning rate for the perceptron training rule, ```Data``` objects that hold test and training data respectively, and ```vector``` variables that contain the bias parameters for each neuron and ```Layer``` objects (model). The class also has a default constructor and two different parameterised constructors. The class is designed in a fairly generic manner and can accommdate any number of hidden layers and neurons in each layer.


## neural_network.cpp

This file is the actual implementation of the methods declared in the ```neural_network.h``` file. The implementation of the methods is explained below. 

**Default Constructor**: Initialises an empty ```NeuralNetwork``` object.

**Constructor A**: Initialises a ```NeuralNetwork``` object, with test and training ```Data```, the learning rate and network layers, and a bias ```vector```. The constructor body creates ```Layer``` objects, which contain ```Neuron``` objects with randomly generated weights between 0 and 1, and adds each ```Layer``` to the ```NeuralNetwork``` model variable. This constructor is used when weights have not been pre-learnt, and the model needs to train on the given training data.

**Constructor B**: Initialises a ```NeuralNetwork``` object, with only test ```Data```, the learning rate and network layers, a bias ```vector```, and a 2D ```vector``` for the weight matrix. The constructor body creates ```Layer``` objects, which contain ```Neuron``` objects that are constructed with the pre-defined weights, and adds each ```Layer``` to the ```NeuralNetwork``` model variable. This constructor is used when weights have been pre-learnt, and the model just needs to evaluate test data.

**fit**: This method uses the Perceptron Training Rule to train the connection weights for each node in the network. The XOR problem requires a hidden layer of 2 nodes, and a single node in the output layer, although a generic network can be defined. This structure is informed by the decomposition of XOR into AND(OR,NAND), and each perceptron represents a single basic logic gate. The method iterates over each neuron in the hidden layer, and for a fixed number of iterations (20), updates the weights according to the learning rule for each relevant training example. The neuron input is passed to the relevant activation function which is determined by the ```Neuron``` object member. Once these neurons are trained, the output is propagated to the output node, and the weights for this node are learnt using the same procedure.

**evaluate** This method evaluates a set of labelled test data once the network has been trained. For each test example, the input is propagated through the network to produce an output. This output is compared against the label to produce an accuracy score for the neural network and to compute the MSE metric. The method shares some of its implementation with the above method concerning output and intermediate value computation, although of course, does not update any connection weights. The Test Data, Prediction, Accuracy and MSE score are written to console. 

**structure** This method writes the structure of the neural network to the console. The size of each hidden output layer is given by the dimensions of the model member variable and ascertains the size of the input layer from an element in the test ```Data``` class ```vector``` of ```Input``` objects.


## neuron.h

This is a header file that contains the ```Neuron``` Class declaration. The neuron is the computational unit in the neural network. The class contains member variables that store the activation function for the particular neuron, a ```vector``` of weights, which are the values of the incoming neuron connections, a ```Input``` object that represents the neuron input, and the output of the perceptron. This class only consists of Constructors. The class friends ```NeuralNetwork``` since they are tightly coupled and to allow for efficient code.


## neuron.cpp

This file is the actual implementation of the methods declared in the ```neuron.h``` file. The implementation of the methods is explained below. 

**Default Constructor**: Initialises an empty ```Neuron``` object.

**Constructor**: Initialises a ```Neuron``` object, with the specified activation function (stored as a ```string```), and a ```vector``` of the weights.

## layer.h

This is a header file that contains the ```Layer``` Class declaration. The class consists solely of a ```vector``` of the ```Neuron``` objects, and functions as a wrapper class for a model layer. It also contains a method to compose (build) a layer with perceptrons.

## layer.cpp

This file is the actual implementation of the methods declared in the ```layer.h``` file. The implementation of the methods is explained below. 

**Default Constructor**: Initialises an empty ```Layer``` object. Used when constructing a ```NeuralNetwork``` object

**Constructor**: Initialises a ```Layer``` object, with a ```vector``` of ```Neuron``` objects.

## data.h

This is a header file that contains the ```Data``` Class declaration. This class stores a ```vector``` of training labels, and a ```vector``` of ```Input``` objects, which represent the input for each test/training example i.e. the input nodes. The class is an encapsulation of the test/training data required by the neural network. The class friends ```NeuralNetwork``` since they are tightly coupled.


## data.cpp

This file is the actual implementation of the methods declared in the ```data.h``` file. The implementation of the methods is explained below. 

**Default Constructor**: Initialises an empty ```Data``` object.

**Constructor**: Initialises a ```Data``` object, with a ```vector``` of data labels, and a ```vector``` of constructed ```Input``` objects that correspond to input data.

## input.h

This is a header file that contains the ```Input``` Class declaration. The class consists solely of a ```vector``` of type ```float``` and functions as a wrapper class for the input layer (input data for the network). The class friends ```NeuralNetwork``` since they are tightly coupled.


## input.cpp

This file is the actual implementation of the methods declared in the ```input.h``` file. The implementation of the methods is explained below. 

**Default Constructor**: Initialises an empty ```Input``` object.

**Constructor**: Initialises a ```Input``` object, with a ```vector``` of```float``` containing the input layer neuron values (input data).


## driver.cpp

This file contains the main method and provides an entry point into the program. It imports the ```neural_network.h``` file to provide the artificial neural network functionality. The main method has two ```NeuralNetwork``` objects, one for each question. Several ```vector``` objects and objects of type ```Data``` are constructed and passed into the relevant ```NeuralNetwork``` class constructors. The relevant methods of each ```NeuralNetwork``` object are called to answer the posed questions. 

