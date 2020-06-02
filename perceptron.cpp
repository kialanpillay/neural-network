#include "perceptron.h"
#include <string>
#include <vector>

using namespace PLLKIA010;

Perceptron::Perceptron(void){}

Perceptron::Perceptron(std::string & a, std::vector<float> & w, std::vector<float> & i): activation(a), weights(w), input(i) {}