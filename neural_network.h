#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include "perceptron.h"
#include "data.h"
#include "input.h"
#include <iostream>
#include <vector>

namespace PLLKIA010
{
    class NeuralNetwork
    {
    public:
        NeuralNetwork(void);
        NeuralNetwork(const Data & train, const Data & test, const float learning_rate, const int layers);
        void fit();
        void evaluate();
        void predict();
    private:
        Data train;
        Data test;
        float learning_rate;
        int layers;
        std::vector<std::vector<Perceptron>> model;

    };
    std::ostream &operator<<(std::ostream &os, const NeuralNetwork &nn);
} // namespace PLLKIA010

#endif