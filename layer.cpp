#include "layer.h"
#include <vector>

using namespace PLLKIA010;

Layer::Layer(void){}

Layer::Layer(const std::vector<Perceptron> &layer): layer(layer){}

void Layer::compose(const Perceptron & perceptron){
    layer.push_back(perceptron);
}