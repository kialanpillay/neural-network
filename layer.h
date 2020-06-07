#ifndef LAYER_H
#define LAYER_H
#include "neuron.h"
#include <vector>

namespace PLLKIA010
{
    class Layer
    {
    public:
        friend class NeuralNetwork;
        Layer(void);
        Layer(const std::vector<Neuron> & layer);
        void compose(const Neuron & neuron);

    private:
        std::vector<Neuron> layer; //Layer of Neurons
    };
} // namespace PLLKIA010

#endif