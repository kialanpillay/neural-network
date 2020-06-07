#ifndef NEURON_H
#define NEURON_H
#include "input.h"
#include <string>
#include <vector>

namespace PLLKIA010
{
    class Neuron
    {
    public:
        friend class NeuralNetwork;
        Neuron(void);
        Neuron(std::string activation, std::vector<float> & weights);

    private:
        std::string activation;
        std::vector<float> weights;
        Input x;
        float output;
    };
} // namespace PLLKIA010

#endif