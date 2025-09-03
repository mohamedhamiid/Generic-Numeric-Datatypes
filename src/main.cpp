#include <iostream>
#include <vector>
#include <algorithm>
#include "../inc/Numeric.hpp"
#include "../inc/Type.hpp"
#include "../inc/Complex.hpp"

int main()
{
    // Constructor
    // myStd::Type<int> x(10);

    // Copy Constructor
    // myStd::Type<int> x(10), y(15), z;
    // std::cout << x << " " << z << std::endl;

    // Vector
    // myStd::Type<int> x(10), y(15);
    // myStd::Type<double> z(10.5);
    // std::vector<std::unique_ptr<myStd::Numeric>> v;
    // v.push_back(std::make_unique<myStd::Type<int>>(x));
    // v.push_back(std::make_unique<myStd::Type<int>>(y));
    // v.push_back(std::make_unique<myStd::Type<double>>(z));
    // sort(v.begin(), v.end());
    // for (const auto &i : v)
    //     i->print(std::cout);

    // complex test
    myStd::Complex<double, double> a{1.0, 2.0}, b{2.5, 3}; // ← you want to disallow this
    myStd::Type<myStd::Complex<double, double>> x(a), y(b);
    x += y;
    std::cout << x;
}