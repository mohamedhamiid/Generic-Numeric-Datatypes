#include <iostream>
#include <vector>
#include <algorithm>
#include "../inc/Numeric.hpp"
#include "../inc/Type.hpp"
#include "../inc/Complex.hpp"

int main()
{
    // =========================
    // 1. Basic Construction and Output
    // =========================
    std::cout << "=== Basic Construction and Output ===" << std::endl;
    myStd::Type<int> i1(10), i2(15);
    myStd::Type<double> d1(10.5), d2(2.5);
    myStd::Complex<int, int> a{3, 4}, b{6, 8};
    myStd::Type<myStd::Complex<int, int>> c1(a), c2(b);
    myStd::Type<myStd::Complex<double, double>> c3;

    std::cout << "i1: " << i1 << ", i2: " << i2 << std::endl;
    std::cout << "d1: " << d1 << ", d2: " << d2 << std::endl;
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;

    // =========================
    // 2. Copy and Move Constructors
    // =========================
    std::cout << "\n=== Copy and Move Constructors ===" << std::endl;
    myStd::Type<int> i3(i1);               // Copy
    myStd::Type<double> d3(std::move(d2)); // Move
    std::cout << "i3 (copy of i1): " << i3 << std::endl;
    std::cout << "d3 (move of d2): " << d3 << std::endl;

    // =========================
    // 3. Arithmetic Operations (Same Type)
    // =========================
    std::cout << "\n=== Arithmetic Operations (Same Type) ===" << std::endl;
    myStd::Type<int> i_sum = i1 + i2;
    myStd::Type<double> d_prod = d1 * d3;
    myStd::Type<myStd::Complex<int, int>> c_sum = c1 + c2;
    std::cout << "i1 + i2: " << i_sum << std::endl;
    std::cout << "d1 * d3: " << d_prod << std::endl;
    std::cout << "c1 + c2: " << c_sum << std::endl;

    // =========================
    // 4. Compound Assignment Operators
    // =========================
    std::cout << "\n=== Compound Assignment Operators ===" << std::endl;
    myStd::Type<int> i4(5);
    i4 += i1;
    std::cout << "i4 += i1: " << i4 << std::endl;
    i4 -= i2;
    std::cout << "i4 -= i2: " << i4 << std::endl;
    i4 *= i1;
    std::cout << "i4 *= i1: " << i4 << std::endl;
    i4 /= i1;
    std::cout << "i4 /= i1: " << i4 << std::endl;

    // =========================
    // 5. Mixed-Type Arithmetic (int + double, double + int)
    // =========================
    std::cout << "\n=== Mixed-Type Arithmetic (int + double, double + int) ===" << std::endl;
    myStd::Type<double> mix1 = i1 + d1;
    myStd::Type<double> mix2 = d1 + i2;
    std::cout << "i1 + d1: " << mix1 << std::endl;
    std::cout << "d1 + i2: " << mix2 << std::endl;

    // =========================
    // 6. Mixed-Type Arithmetic (int + complex, double + complex)
    // =========================
    std::cout << "\n=== Mixed-Type Arithmetic (int/double + complex) ===" << std::endl;
    myStd::Type<myStd::Complex<double, double>> ic_sum = i1 + c1;
    myStd::Type<myStd::Complex<double, double>> ci_sum = c1 + i2;
    myStd::Type<myStd::Complex<double, double>> dc_sum = d1 + c1;
    myStd::Type<myStd::Complex<double, double>> cd_sum = c1 + d1;
    std::cout << "i1 + c1: " << ic_sum << std::endl;
    std::cout << "c1 + i2: " << ci_sum << std::endl;
    std::cout << "d1 + c1: " << dc_sum << std::endl;
    std::cout << "c1 + d1: " << cd_sum << std::endl;

    // =========================
    // 7. Comparison Operators
    // =========================
    std::cout << "\n=== Comparison Operators ===" << std::endl;
    std::cout << "i1 < i2: " << (i1 < i2) << std::endl;
    std::cout << "d1 > d3: " << (d1 > d3) << std::endl;
    std::cout << "c1 == c2: " << (c1 == c2) << std::endl;

    // =========================
    // 8. Assignment from unique_ptr<Numeric> (allowed only for double and Complex<double, double>)
    // =========================
    std::cout << "\n=== Assignment from unique_ptr<Numeric> ===" << std::endl;
    try
    {
        myStd::Type<double> d4;
        d4 = std::move(mix1); // Should work
        std::cout << "d4 (assigned from mix1): " << d4 << std::endl;

        myStd::Type<myStd::Complex<double, double>> c4;
        c4 = std::move(cd_sum); // Should work
        std::cout << "c4 (assigned from cd_sum): " << c4 << std::endl;

        // Uncommenting the following should cause a compile-time error:
        // myStd::Type<int> i5;
        // i5 = std::move(mix1);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Assignment error: " << e.what() << std::endl;
    }

    // =========================
    // 9. Exception Handling for Invalid Operations
    // =========================
    std::cout << "\n=== Exception Handling for Invalid Operations ===" << std::endl;
    try
    {
        // Should throw: multiplication of int and complex
        myStd::Type<myStd::Complex<double, double>> invalid = i1 * c1;
        std::cout << "i1 * c1: " << invalid << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Expected error (i1 * c1): " << e.what() << std::endl;
    }

    try
    {
        // Should throw: division of double and complex
        myStd::Type<myStd::Complex<double, double>> invalid2 = d1 / c1;
        std::cout << "d1 / c1: " << invalid2 << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Expected error (d1 / c1): " << e.what() << std::endl;
    }

    // =========================
    // 10. Sorting a vector of mixed numeric types
    // =========================
    std::cout << "\n=== Sorting a vector of mixed numeric types ===" << std::endl;
    std::vector<std::unique_ptr<myStd::Numeric>> v;
    v.push_back(std::make_unique<myStd::Type<int>>(i1));
    v.push_back(std::make_unique<myStd::Type<myStd::Complex<int, int>>>(c1));
    v.push_back(std::make_unique<myStd::Type<myStd::Complex<int, int>>>(c2));
    v.push_back(std::make_unique<myStd::Type<int>>(i2));
    v.push_back(std::make_unique<myStd::Type<double>>(d1));

    std::sort(v.begin(), v.end(),
              [](const auto &a, const auto &b)
              { return *a < *b; });

    std::cout << "Sorted vector:" << std::endl;
    for (auto &i : v)
        i->print(std::cout);

    // =========================
    // 11. Input/Output Operators
    // =========================
    std::cout << "\n=== Input/Output Operators ===" << std::endl;
    myStd::Type<int> inputTest;
    std::cout << "Enter an integer value: ";
    std::cin >> inputTest;
    std::cout << "You entered: " << inputTest << std::endl;

    myStd::Type<myStd::Complex<int, int>> complexInputTest;
    std::cout << "Enter a complex value (format: (real imag)): ";
    std::cin >> complexInputTest;
    std::cout << "You entered: " << complexInputTest << std::endl;

    return 0;
}