#include "neural_network.h"
#include "data.h"
#include "input.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace PLLKIA010;

int main(int argc, char *argv[])
{
    vector<float> training_labels = {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0};
    vector<float> test_labels = {0, 1, 1, 0, 1, 1};
    vector<Input> training_input = {Input({0, 0}), Input({0, 1}), Input({1, 0}), Input({1, 1}), Input({0, 0}), Input({0, 1}), Input({1, 0}), Input({1, 1}), Input({0, 0}), Input({0, 1}), Input({1, 0}), Input({1, 1})};
    vector<Input> test_input = {Input({0, 0}), Input({0, 1}), Input({1, 0}), Input({1, 1}), Input({0, 1.1}), Input({0.9, 0.1})};
    Data train_xor(training_labels, training_input);
    Data test_xor(test_labels, test_input);
    float learning_rate = 0.1;
    vector<float> bias = {0, 0.5, -1};
    int layers = 2;
    NeuralNetwork nn_xor(train_xor, test_xor, learning_rate, layers, bias);
    
    nn_xor.fit();
    nn_xor.evaluate();
    nn_xor.structure();

    test_labels = {0.36};
    test_input = {Input({1.3, 2.7, 0.8})};
    Data test(test_labels, test_input);
    bias = {0.1, -0.3, -0.3};
    vector<vector<float>> weight_matrix = {{0.1, 0.2, 0.5}, {-0.4, 1.0, -0.6}, {0.8, 1.0}};
    NeuralNetwork nn_mse(test, learning_rate, layers, bias, weight_matrix);
    
    nn_mse.evaluate();
    nn_mse.structure();
    return 0;
}
