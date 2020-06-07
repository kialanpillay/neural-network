#include "neuron.h"
#include <string>
#include <vector>

using namespace PLLKIA010;

Neuron::Neuron(void){}

Neuron::Neuron(std::string a, std::vector<float> & w): activation(a), weights(w) {}