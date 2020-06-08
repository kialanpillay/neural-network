#ifndef DATA_H
#define DATA_H
#include "input.h"
#include <vector>

namespace PLLKIA010
{
    class Data
    {
    public:
        friend class NeuralNetwork;
        Data(void);
        Data(const std::vector<float> & labels, const std::vector<Input> & input);

    private:
        std::vector<float> labels; //m-Dimensional Label (Target) Vector
        std::vector<Input> input; //m-Dimensional Input Vector (M x N)
    };
} // namespace PLLKIA010

#endif