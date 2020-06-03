#include "data.h"
#include <iostream>

using namespace PLLKIA010;

Data::Data(void) {}

Data::Data(const std::vector<float> &labels, const std::vector<Input> &input) : train_labels(labels), train_input(input){}