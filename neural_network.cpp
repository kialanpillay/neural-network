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
        srand(static_cast<unsigned>(time(0)));

        for (int w = 0; w < 2; ++w)
        {
            float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            weights.push_back(r);
        }

        if (i == l - 1)
        {
            model[i].push_back(Perceptron("step", weights)); //Output Layer
        }
        else
        {
            model[i].push_back(Perceptron("step", weights));
            model[i].push_back(Perceptron("step", weights)); //2-Node Hidden Layer
        }
    }
}

void NeuralNetwork::fit(void)
{
    for (int k = 0; k < 10; ++k)
    {
        //std::cout << "Iteration " << (k + 1) << std::endl;
        for (int m = 0; m < training_data.train_input.size(); ++m)
        {
            std::vector<float> x = training_data.train_input[m].x;
            for (auto &perceptron : model[0])
            {
                std::vector<float> linear;
                std::transform(perceptron.weights.begin(), perceptron.weights.end(),
                               x.begin(), std::back_inserter(linear),
                               std::multiplies<float>());
                float sum = std::accumulate(linear.begin(), linear.end(), 0.0);

                if (perceptron.activation == "step")
                {
                    if (sum > 1.5)
                    {
                        perceptron.output = 1;
                    }
                    else
                    {
                        perceptron.output = 0;
                    }
                }
                float t = training_data.train_labels[m];
                float o = perceptron.output;
                float rate = learning_rate;

                std::vector<float> delta;
                std::transform(x.begin(), x.end(), std::back_inserter(delta), [rate, t, o](float x) { return rate * (t - o) * x; });
                std::transform(perceptron.weights.begin(), perceptron.weights.end(),
                               delta.begin(), perceptron.weights.begin(),
                               std::plus<float>());
            }
        }
        for (auto w : model[0][0].weights)
        {
            //std::cout << w << " ";
        }
        //std::cout << std::endl << std::endl;
    }
}

void NeuralNetwork::evaluate(void)
{
    for (auto i : test_data)
    {
        std::vector<float> linear;
        std::transform(model[0][0].weights.begin(), model[0][0].weights.end(),
                       i.x.begin(), std::back_inserter(linear),
                       std::multiplies<float>());
        float sum = std::accumulate(linear.begin(), linear.end(), 0.0);
        if (sum > 1.5)
        {
            std::cout << "Prediction: " << 1;
        }
        else
        {
            std::cout << "Prediction: " << 0 << std::endl;
        }
    }
}