#ifndef INPUT_H
#define INPUT_H
#include <vector>

namespace PLLKIA010
{
    class Input
    {
    public:
        friend class NeuralNetwork;
        Input(void);
        Input(const std::vector<float> &input);

    private:
        std::vector<float> x; //n-Dimensional Input Vector (Input Nodes)
    };
} // namespace PLLKIA010

#endif