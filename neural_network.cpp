#include "neural_network.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>

using namespace PLLKIA010;

NeuralNetwork::NeuralNetwork(void) {}

NeuralNetwork::NeuralNetwork(const Data &train, const Data &test, const float r, const int l) : train(train), test(test), learning_rate(r), layers(l)
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

int step(float x, float threshold)
{
    if (x > threshold)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void NeuralNetwork::fit(void)
{
    for (int k = 0; k < 10; ++k)
    {
        //std::cout << "Iteration " << (k + 1) << std::endl;
        for (int m = 0; m < train.train_input.size(); ++m)
        {
            std::vector<float> x = train.train_input[m].x;
            for (auto &perceptron : model[0])
            {
                std::vector<float> linear;
                std::transform(perceptron.weights.begin(), perceptron.weights.end(),
                               x.begin(), std::back_inserter(linear),
                               std::multiplies<float>());
                float sum = std::accumulate(linear.begin(), linear.end(), 0.0);

                if (perceptron.activation == "step")
                {
                    perceptron.output = step(sum, 1.5);
                }
                float t = train.train_labels[m];
                float o = perceptron.output;
                float rate = learning_rate;

                std::vector<float> delta;
                std::transform(x.begin(), x.end(), std::back_inserter(delta), [rate, t, o](float x) { return rate * (t - o) * x; });
                std::transform(perceptron.weights.begin(), perceptron.weights.end(),
                               delta.begin(), perceptron.weights.begin(),
                               std::plus<float>());
            }
        }
    }
}

void NeuralNetwork::evaluate(void)
{
    std::vector<float> predicted;
    for (int i = 0; i < int(test.train_input.size()); ++i)
    {
        std::vector<float> linear;
        std::transform(model[0][0].weights.begin(), model[0][0].weights.end(),
                       test.train_input[i].x.begin(), std::back_inserter(linear),
                       std::multiplies<float>());
        float sum = std::accumulate(linear.begin(), linear.end(), 0.0);
        float prediction = step(sum, 1.5);
        std::cout << "[" << test.train_input[i].x[0] << ", " << test.train_input[i].x[1] << "] - "
                  << "Prediction: " << prediction << std::endl;
        predicted.push_back(prediction);
    }
    int true_positive = 0;
    for (int i = 0; i < int(predicted.size()); ++i)
    {
        if (predicted[i] == test.train_labels[i])
        {
            true_positive++;
        }
    }

    std::cout << "Accuracy: " << true_positive / test.train_labels.size() * 100 << "%" << std::endl;
}