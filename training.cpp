#include "training.h"
#include <iostream>

using namespace PLLKIA010;

Training::Training(void) {}

Training::Training(const std::vector<float> &labels, const std::vector<Input> &input) : train_labels(labels), train_input(input){}