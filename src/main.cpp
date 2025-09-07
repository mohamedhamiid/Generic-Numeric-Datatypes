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
    // myStd::Type<int> x(20), y(15);
    // myStd::Type<double> z(10.5);
    // std::vector<std::unique_ptr<myStd::Numeric>> v;
    // v.push_back(std::make_unique<myStd::Type<int>>(x));
    // v.push_back(std::make_unique<myStd::Type<double>>(z));
    // v.push_back(std::make_unique<myStd::Type<int>>(y));
    // sort(v.begin(), v.end());
    // for (const auto &i : v)
    //     i->print(std::cout);

    // complex test
    myStd::Type<int> i1(10), i2(15);
    myStd::Type<double> d1(10.5);
    // d1 = i1 + d1;
    myStd::Complex<int, int> a{3, 4}, b{6, 8};
    myStd::Type<myStd::Complex<int, int>> c1(a), c2(b);
    myStd::Type<myStd::Complex<double, double>> c3;

    try
    {
        // c1 += d1;
        c3 = d1 / c1;
        std::cout << c3 << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::vector<std::unique_ptr<myStd::Numeric>> v;
    v.push_back(std::make_unique<myStd::Type<int>>(i1));
    v.push_back(std::make_unique<myStd::Type<myStd::Complex<int, int>>>(c1));
    v.push_back(std::make_unique<myStd::Type<myStd::Complex<int, int>>>(c2));
    v.push_back(std::make_unique<myStd::Type<int>>(i2));
    v.push_back(std::make_unique<myStd::Type<double>>(d1));

    std::sort(v.begin(), v.end(),
              [](const auto &a, const auto &b)
              { return *a < *b; });
    for (auto &i : v)
        i->print(std::cout);
}