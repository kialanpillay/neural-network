#include "neural_network.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <math.h>

using namespace PLLKIA010;

NeuralNetwork::NeuralNetwork(void) {}

NeuralNetwork::NeuralNetwork(const Data &train, const Data &test, const float r, const int l, const std::vector<float> &b) : train(train), test(test), learning_rate(r), layers(l), bias(b)
{
    srand(unsigned(time(0)));
    for (int i = 0; i < l; ++i)
    {
        Layer layer;
        model.push_back(layer);
        std::vector<float> weights;

        float r = float(rand()) / float(RAND_MAX);
        for (int w = 0; w < 2; ++w)
        {

            weights.push_back(r);
        }

        if (i == l - 1)
        {
            model[i].compose(Perceptron("step", weights)); //Output Layer
        }
        else
        {
            model[i].compose(Perceptron("step", weights));
            model[i].compose(Perceptron("step", weights)); //2-Node Hidden Layer
        }
    }
}

NeuralNetwork::NeuralNetwork(const Data &test, const float r, const int l, const std::vector<float> &b, const std::vector<std::vector<float>> &w) : test(test), learning_rate(r), layers(l), bias(b)
{
    std::vector<std::vector<float>> weight_matrix = w;
    int c = 0;
    for (int i = 0; i < l; ++i)
    {
        Layer layer;
        std::vector<float> weights;
        model.push_back(layer);
        if (i == l - 1)
        {
            weights = weight_matrix[c];
            model[i].compose(Perceptron("sigmoid", weights)); //Output Layer
        }
        else
        {

            for (int j = 0; j < 2; ++j)
            {
                weights = weight_matrix[c++];
                model[i].compose(Perceptron("sigmoid", weights));
            }
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

float sigmoid(float x)
{
    return 1 / (1 + exp(-x));
}

void NeuralNetwork::fit(void)
{
    int c = 0; //Counter
    for (auto &perceptron : model[0].layer)
    {
        for (int k = 0; k < 10; ++k)
        {
            for (int m = (c * 4); m < ((c * 4) + 4); ++m)
            {
                std::vector<float> x = train.train_input[m].x;
                std::vector<float> linear;
                std::transform(perceptron.weights.begin(), perceptron.weights.end(),
                               x.begin(), std::back_inserter(linear),
                               std::multiplies<float>());
                float sum = bias[c] + std::accumulate(linear.begin(), linear.end(), 0.0);
                if (perceptron.activation == "step")
                {
                    perceptron.output = step(sum, 0);
                }
                else if (perceptron.activation == "sigmoid")
                {
                    perceptron.output = sigmoid(sum);
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
        c++;
    }

    for (int k = 0; k < 10; ++k)
    {
        for (int m = (c * 4); m < ((c * 4) + 4); ++m)
        {
            std::vector<float> x = train.train_input[m].x;
            std::vector<float> h; //Output of Hidden Layer
            int c = 0;
            for (auto &perceptron : model[0].layer)
            {
                std::vector<float> linear;
                std::transform(perceptron.weights.begin(), perceptron.weights.end(),
                               x.begin(), std::back_inserter(linear),
                               std::multiplies<float>());
                float sum = bias[c] + std::accumulate(linear.begin(), linear.end(), 0.0);
                if (perceptron.activation == "step")
                {
                    perceptron.output = step(sum, 0);
                }
                else if (perceptron.activation == "sigmoid")
                {
                    perceptron.output = sigmoid(sum);
                }
                h.push_back(perceptron.output);
                c++;
            }
            std::vector<float> linear;
            std::transform(model[1].layer[0].weights.begin(), model[1].layer[0].weights.end(),
                           h.begin(), std::back_inserter(linear),
                           std::multiplies<float>());
            float sum = bias[c] + std::accumulate(linear.begin(), linear.end(), 0.0);
            if (model[1].layer[0].activation == "step")
            {
                model[1].layer[0].output = step(sum, 0);
            }
            float t = train.train_labels[m];
            float o = model[1].layer[0].output;
            float rate = learning_rate;

            std::vector<float> delta;
            std::transform(h.begin(), h.end(), std::back_inserter(delta), [rate, t, o](float x) { return rate * (t - o) * x; });
            std::transform(model[1].layer[0].weights.begin(), model[1].layer[0].weights.end(),
                           delta.begin(), model[1].layer[0].weights.begin(),
                           std::plus<float>());
        }
    }
}

void NeuralNetwork::evaluate(void)
{
    std::cout << "Neural Network Evaluation - Test Data" << std::endl;
    std::vector<float> predicted;
    int c = 0;
    for (int i = 0; i < int(test.train_input.size()); ++i)
    {
        c = 0;
        std::vector<float> x = test.train_input[i].x;
        std::vector<float> h; //Output of Hidden Layer
        for (auto &perceptron : model[0].layer)
        {
            std::vector<float> linear;
            std::transform(perceptron.weights.begin(), perceptron.weights.end(),
                           x.begin(), std::back_inserter(linear),
                           std::multiplies<float>());
            float sum = bias[c] + std::accumulate(linear.begin(), linear.end(), 0.0);
            if (perceptron.activation == "step")
            {
                perceptron.output = step(sum, 0);
            }
            else if (perceptron.activation == "sigmoid")
            {
                perceptron.output = sigmoid(sum);
            }
            h.push_back(perceptron.output);
            c++;
        }
        std::vector<float> linear;
        std::transform(model[1].layer[0].weights.begin(), model[1].layer[0].weights.end(),
                       h.begin(), std::back_inserter(linear),
                       std::multiplies<float>());
        float sum = bias[c] + std::accumulate(linear.begin(), linear.end(), 0.0);
        if (model[1].layer[0].activation == "step")
        {
            model[1].layer[0].output = step(sum, 0);
        }
        else if (model[1].layer[0].activation == "sigmoid")
        {
            model[1].layer[0].output = sigmoid(sum);
        }
        float prediction = model[1].layer[0].output;
        std::cout << std::setprecision(2) << std::fixed;
        std::cout << "[" << test.train_input[i].x[0] << ", " << test.train_input[i].x[1] << "] - "
                  << "Prediction: " << prediction << std::endl;
        predicted.push_back(prediction);
    }

    float true_positive = 0;
    for (int i = 0; i < int(predicted.size()); ++i)
    {
        if (predicted[i] == test.train_labels[i])
        {
            true_positive++;
        }
    }
    std::cout << "\nNeural Network Accuracy: " << true_positive / test.train_labels.size() * 100 << "%" << std::endl << std::endl;
}