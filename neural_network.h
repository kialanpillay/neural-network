#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include "perceptron.h"
#include "training.h"
#include "input.h"
#include <iostream>
#include <vector>

namespace PLLKIA010
{
    class NeuralNetwork
    {
    public:
        NeuralNetwork(void);
        NeuralNetwork(const Training & training_data, const std::vector<Input> & test_data, const float learning_rate, const int layers);
        void fit();
        void evaluate();
        void predict();
    private:
        Training training_data;
        float learning_rate;
        int layers;
        std::vector<std::vector<Perceptron>> model;
        std::vector<Input> test_data;

    };
    std::ostream &operator<<(std::ostream &os, const NeuralNetwork &nn);
} // namespace PLLKIA010

#endif