#ifndef TRAINING_H
#define TRAINING_H
#include "input.h"
#include <iostream>
#include <vector>

namespace PLLKIA010
{
    class Training
    {
    public:
        Training(void);
        Training(const std::vector<float> & labels, const std::vector<Input> & input);

    private:
        std::vector<float> train_labels; //m dimensional label (target) vector
        std::vector<Input> train_input; //m dimensional input vector (m x n)
    };
} // namespace PLLKIA010

#endif