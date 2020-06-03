#include "neural_network.h"
#include "data.h"
#include "perceptron.h"
#include "input.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace PLLKIA010;

int main(int argc, char *argv[])
{
    vector<float> training_labels = {0, 1, 1, 1};
    vector<float> test_labels = {0, 1, 1, 1};
    vector<Input> training_input = {Input({0, 0}), Input({0, 1}), Input({1, 0}), Input({1, 1})};
    vector<Input> test_input = {Input({0, 0}), Input({0, 1}), Input({1, 0}), Input({1, 1})};
    Data train(training_labels, training_input);
    Data test(test_labels, test_input);
    float learning_rate = 0.1;
    int layers = 2;
    NeuralNetwork nn(train, test, learning_rate, layers);
    nn.fit();
    //nn.evaluate();
    //ofstream out("output.txt");
    //out.close();
    return 0;
}
