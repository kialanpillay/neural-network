#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include "neuron.h"
#include "layer.h"
#include "data.h"
#include "input.h"
#include <vector>

namespace PLLKIA010
{
    class NeuralNetwork
    {
    public:
        NeuralNetwork(void);
        NeuralNetwork(const Data &train, const Data &test, const float learning_rate, const int layers, const std::vector<float> &bias);
        NeuralNetwork(const Data &test, const float learning_rate, const int layers, const std::vector<float> &bias, const std::vector<std::vector<float>> &weight_matrix);
        void fit();
        void evaluate();
        void structure();

    private:
        Data train;
        Data test;
        float learning_rate;
        int layers;
        std::vector<Layer> model;
        std::vector<float> bias;
    };
} // namespace PLLKIA010

#endif