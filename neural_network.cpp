#include "neural_network.h"
#include <iostream>

using namespace PLLKIA010;

NeuralNetwork::NeuralNetwork(void) {}

NeuralNetwork::NeuralNetwork(const Training &train, const std::vector<Input> &test, const float r, const int l) : training_data(train), test_data(test), learning_rate(r), layers(l)
{
    for (int i = 0; i < layers; ++i)
    {
        model[i].push_back(Perceptron)
    }
}