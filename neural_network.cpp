#include "neural_network.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>

using namespace PLLKIA010;

NeuralNetwork::NeuralNetwork(void) {}

NeuralNetwork::NeuralNetwork(const Training &train, const std::vector<Input> &test, const float r, const int l) : training_data(train), test_data(test), learning_rate(r), layers(l)
{
    
    for (int i = 0; i < l; ++i)
    {
        std::vector<Perceptron> layer;
        model.push_back(layer);
        std::vector<float> weights;
        for (int w = 0; w < 2; ++w)
        {
            float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            weights.push_back(r);
        }
        if (i != 0)
        {
            model[i].push_back(Perceptron("step", weights));
            model[i].push_back(Perceptron("step", weights)); //2-Node Hidden Layer
        }
        else
        {
            model[i].push_back(Perceptron("step", weights)); //Output Layer
        }
    }
}

void NeuralNetwork::fit(void)
{
    for (int m = 0; m < training_data.train_input.size(); ++m)
    {
        std::vector<float> x = training_data.train_input[m].x;
        for (auto &perceptron : model[0])
        {

            std::vector<float> linear;
            std::transform(perceptron.weights.begin(), perceptron.weights.end(),
                           x.begin(), std::back_inserter(linear),
                           std::multiplies<float>());
            float sum = std::accumulate(linear.begin(), linear.end(), 0);
            std::cout << sum;
        }
    }
}