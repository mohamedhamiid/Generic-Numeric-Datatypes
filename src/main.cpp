#include <iostream>
#include <vector>
#include "../inc/Numeric.hpp"
#include "../inc/Type.hpp"

int main()
{
    std::vector<myStd::Numeric> v;

    myStd::Type<int> x(10), z;
    myStd::Type<double> y(2.5);

    try
    {
        x = z;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
    std::cout << x;
    return 0;
}