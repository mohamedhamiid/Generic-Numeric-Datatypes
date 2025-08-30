#pragma once
#include <memory>

namespace myStd
{
    // Abstract base class
    class Numeric
    {
    public:
        // Virtual destructor must have a definition
        virtual ~Numeric() = default;

        // Pure virtual functions for arithmetic operations (return smart pointers for safety)
        virtual std::unique_ptr<Numeric> operator+(Numeric &) = 0;
        virtual std::unique_ptr<Numeric> operator-(Numeric &) = 0;
        virtual std::unique_ptr<Numeric> operator*(Numeric &) = 0;
        virtual std::unique_ptr<Numeric> operator/(Numeric &) = 0;

        virtual Numeric &operator+=(Numeric &) = 0;
        virtual Numeric &operator-=(Numeric &) = 0;
        virtual Numeric &operator*=(Numeric &) = 0;
        virtual Numeric &operator/=(Numeric &) = 0;

        // Pure virtual functions for comparisons
        virtual bool operator<(Numeric &) = 0;
        virtual bool operator>(Numeric &) = 0;
        virtual bool operator==(Numeric &) = 0;
    };
}