#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <string>
#include <vector>

namespace PLLKIA010
{
    class Input
    {
    public:
        Input(void);
        Input(const std::vector<float> &input);

    private:
        std::vector<float> x; //n-dimensional input vector (input nodes)
    };
} // namespace PLLKIA010

#endif