#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <string>
#include <vector>

namespace PLLKIA010
{
    class Perceptron
    {
    public:
        Perceptron(void);
        Perceptron(std::string & activation, std::vector<float> & weights, std::vector<float> & input);

    private:
        std::string activation;
        std::vector<float> weights;
        std::vector<float> input;
        Input x;
        float output;
    };
} // namespace PLLKIA010

#endif