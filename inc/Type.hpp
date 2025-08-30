#pragma once
#include "../inc/Numeric.hpp"
#include <iostream>
#include <memory>
namespace myStd
{
    // Template class definition and implementation
    template <typename T>
    class Type : public Numeric
    {
    private:
        T value{};

    public:
        // Constructors
        Type() = default;
        explicit Type(T val) : value(val) {}

        // Destructor
        ~Type() = default;

        // Assignment operators
        template <typename U>
        Type<T> &operator=(const Type<U> &val)
        {
            if constexpr (!std::is_same_v<T, U>)
                throw std::runtime_error("Type mismatch in assignment");
            value = val;
            return *this;
        }

        // Arithmetic operations (compound assignment)
        Numeric &operator+=(Numeric &obj) override
        {
            value += dynamic_cast<Type<T> &>(obj).value;
            return *this;
        }

        Numeric &operator-=(Numeric &obj) override
        {
            value -= dynamic_cast<Type<T> &>(obj).value;
            return *this;
        }

        Numeric &operator*=(Numeric &obj) override
        {
            value *= dynamic_cast<Type<T> &>(obj).value;
            return *this;
        }

        Numeric &operator/=(Numeric &obj) override
        {
            value /= dynamic_cast<Type<T> &>(obj).value;
            return *this;
        }

        // Arithmetic operations (return new object)
        std::unique_ptr<Numeric> operator+(Numeric &obj) override
        {
            // return (value + dynamic_cast<Type<T> &>(obj).value);
        }

        std::unique_ptr<Numeric> operator-(Numeric &obj) override
        {
            return std::make_unique<Type<T>>(value - dynamic_cast<Type<T> &>(obj).value);
        }

        std::unique_ptr<Numeric> operator*(Numeric &obj) override
        {
            return std::make_unique<Type<T>>(value * dynamic_cast<Type<T> &>(obj).value);
        }

        std::unique_ptr<Numeric> operator/(Numeric &obj) override
        {
            return std::make_unique<Type<T>>(value / dynamic_cast<Type<T> &>(obj).value);
        }

        // Comparison operators
        bool operator<(Numeric &obj) override
        {
            return value < dynamic_cast<Type<T> &>(obj).value;
        }

        bool operator>(Numeric &obj) override
        {
            return value > dynamic_cast<Type<T> &>(obj).value;
        }

        bool operator==(Numeric &obj) override
        {
            return value == dynamic_cast<Type<T> &>(obj).value;
        }

        // Friend functions for I/O

        friend std::ostream &operator<<(std::ostream &os, const Type<T> &obj)
        {
            os << obj.value;
            return os;
        }

        friend std::istream &operator>>(std::istream &is, Type<T> &obj)
        {
            is >> obj.value;
            return is;
        }
    };
}
