#include "neural_network.h"
#include "training.h"
#include "perceptron.h"
#include "input.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace PLLKIA010;

int main(int argc, char *argv[])
{
    vector<float> training_labels = {0, 0, 0, 1};
    vector<Input> training_input = {Input({0, 0}), Input({0, 1}), Input({1, 0}), Input({1, 1})};
    vector<Input> test = {Input({0, 0}), Input({0, 1}), Input({1, 0}), Input({1, 1})};
    Training train(training_labels, training_input);
    float learning_rate = 0.1;
    int layers = 1;
    NeuralNetwork nn(train, test, learning_rate, layers);
    nn.fit();
    nn.evaluate();
    //ofstream out("output.txt");
    //out.close();
    return 0;
}
