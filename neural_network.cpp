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
    for (int i = 0; i < layers; ++i)
    {
        Layer layer;
        model.push_back(layer);
        std::vector<float> weights;

        float r = float(rand()) / float(RAND_MAX);
        for (int w = 0; w < 2; ++w)
        {

            weights.push_back(r);
        }

        if (i == layers - 1)
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
    int l = 0;
    for (auto &perceptron : model[0].layer)
    {
        for (int k = 0; k < 20; ++k)
        {
            for (int m = (c * 4); m < ((c * 4) + 4); ++m) //Iterate through Training Examples
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
    l++;

    if (l == layers - 1)
    {

        for (int k = 0; k < 20; ++k)
        {
            for (int m = (c * 4); m < ((c * 4) + 4); ++m)
            {
                std::vector<float> x = train.train_input[m].x;
                std::vector<float> h; //Output of Hidden Layer
                int c = 0;
                for (auto &perceptron : model[l - 1].layer)
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
                std::transform(model[l].layer[0].weights.begin(), model[l].layer[0].weights.end(),
                               h.begin(), std::back_inserter(linear),
                               std::multiplies<float>());
                float sum = bias[c] + std::accumulate(linear.begin(), linear.end(), 0.0);
                if (model[l].layer[0].activation == "step")
                {
                    model[l].layer[0].output = step(sum, 0);
                }
                float t = train.train_labels[m];
                float o = model[l].layer[0].output;
                float rate = learning_rate;

                std::vector<float> delta;
                std::transform(h.begin(), h.end(), std::back_inserter(delta), [rate, t, o](float x) { return rate * (t - o) * x; });
                std::transform(model[l].layer[0].weights.begin(), model[l].layer[0].weights.end(),
                               delta.begin(), model[l].layer[0].weights.begin(),
                               std::plus<float>());
            }
        }
    }
    for (auto w : model[0].layer[1].weights){
        std::cout << w << " ";
    }
}

void NeuralNetwork::evaluate(void)
{
    std::cout << "Neural Network Evaluation - Test Data" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::vector<float> predicted;
    std::vector<float> h; //Output of Hidden Layer
    int c = 0;
    int l = 0;
    for (int i = 0; i < int(test.train_input.size()); ++i)
    {
        c = 0;
        l = 0;
        std::vector<float> x = test.train_input[i].x;
        h.clear();
        for (auto &perceptron : model[l].layer)
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
        l++;
        if (l == layers - 1)
        {
            std::vector<float> linear;
            std::transform(model[l].layer[0].weights.begin(), model[l].layer[0].weights.end(),
                           h.begin(), std::back_inserter(linear),
                           std::multiplies<float>());
            float sum = bias[c] + std::accumulate(linear.begin(), linear.end(), 0.0);
            if (model[l].layer[0].activation == "step")
            {
                model[l].layer[0].output = step(sum, 0);
            }
            else if (model[l].layer[0].activation == "sigmoid")
            {
                model[l].layer[0].output = sigmoid(sum);
            }
            float prediction = model[l].layer[0].output;
            std::cout << std::setprecision(2) << std::fixed;
            std::cout << "[" << test.train_input[i].x[0] << ", " << test.train_input[i].x[1] << "] - "
                      << "Prediction: " << prediction << std::endl;
            predicted.push_back(prediction);
        }
        else
        {
            float prediction = h[0]; //Perceptron Output
            std::cout << std::setprecision(2) << std::fixed;
            std::cout << "[" << test.train_input[i].x[0] << ", " << test.train_input[i].x[1] << "] - "
                      << "Prediction: " << prediction << std::endl;
            predicted.push_back(prediction);
        }
    }

    float true_positive = 0;
    float SSE = 0;
    for (int i = 0; i < int(predicted.size()); ++i)
    {
        if (predicted[i] == test.train_labels[i])
        {
            true_positive++;
        }
        SSE += pow((predicted[i] - test.train_labels[i]), 2);
    }
    std::cout << std::endl
              << "Neural Network Accuracy: " << true_positive / test.train_labels.size() * 100 << "%" << std::endl;
    float MSE = SSE / test.train_labels.size();
    std::cout << "Mean Squared Error (MSE): " << MSE << std::endl;
    if (predicted.size() == 1)
    {
        std::cout << std::setprecision(4) << std::fixed;
        std::cout << "Hidden Layer Output - [ ";
        for (auto output : h)
        {
            std::cout << output << " ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << std::endl;
}

void NeuralNetwork::structure()
{
    std::cout << "Neural Network Structure" << std::endl;
    std::cout << "Input Layer Nodes:  " << test.train_input[0].x.size() << std::endl;
    for (int l = 0; l < layers; ++l)
    {
        if (l == layers - 1)
        {
            std::cout << "Output Layer Nodes: " << model[l].layer.size() << std::endl;
        }
        else
        {
            std::cout << "Hidden Layer Nodes: " << model[l].layer.size() << std::endl;
        }
    }

    std::cout << "Fully Connected Nodes" << std::endl;
    std::cout << "=====================================" << std::endl
              << std::endl;
}