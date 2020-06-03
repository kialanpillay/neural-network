#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include "input.h"
#include <string>
#include <vector>

namespace PLLKIA010
{
    class Perceptron
    {
    public:
        friend class NeuralNetwork;
        Perceptron(void);
        Perceptron(std::string activation, std::vector<float> & weights);

    private:
        std::string activation;
        std::vector<float> weights;
        Input x;
        float output;
    };
} // namespace PLLKIA010

#endif