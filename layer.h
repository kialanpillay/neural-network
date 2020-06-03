#ifndef LAYER_H
#define LAYER_H
#include "perceptron.h"
#include <vector>

namespace PLLKIA010
{
    class Layer
    {
    public:
        friend class NeuralNetwork;
        Layer(void);
        Layer(const std::vector<Perceptron> & layer);
        void compose(const Perceptron & perceptron);

    private:
        std::vector<Perceptron> layer; //n-dimensional input vector (input nodes)
    };
} // namespace PLLKIA010

#endif