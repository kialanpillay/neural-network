#include "layer.h"
#include <vector>

using namespace PLLKIA010;

Layer::Layer(void){}

Layer::Layer(const std::vector<Neuron> &layer): layer(layer){}

void Layer::compose(const Neuron & neuron){
    layer.push_back(neuron);
}