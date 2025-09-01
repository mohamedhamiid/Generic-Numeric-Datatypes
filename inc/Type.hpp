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
        std::unique_ptr<T> ptr;

    public:
        // Constructors
        Type() = default;
        explicit Type(T val)
        {
            ptr = std::make_unique<T>(val);
        }

        // Destructor
        ~Type() = default;

        // Copy Constructor
        Type(const Type<T> &obj)
        {
            ptr = std::make_unique<T>(*(obj.ptr));
        }

        // Move constructor
        Type(Type<T> &&obj)
        {
            ptr = std::make_unique<T>(*(obj.ptr));
        }

        // Assignment operators
        Type<T> &operator=(const Type<T> &val)
        {
            ptr = std::make_unique<T>(*(val.ptr));
            return *this;
        }

        Type<T> &operator=(std::unique_ptr<Numeric> val)
        {
            ptr = std::make_unique<T>(*((dynamic_cast<Type<T> *>(val.get()))->ptr));
            return *this;
        }

        // Arithmetic operations (compound assignment)
        Numeric &operator+=(Numeric &obj) override
        {
            *(this->ptr) = *(this->ptr) + *(dynamic_cast<Type<T> &>(obj).ptr);
            return *this;
        }

        Numeric &operator-=(Numeric &obj) override
        {
            *(this->ptr) = *(this->ptr) + *(dynamic_cast<Type<T> &>(obj).ptr);
            return *this;
        }

        Numeric &operator*=(Numeric &obj) override
        {
            *(this->ptr) = *(this->ptr) * *(dynamic_cast<Type<T> &>(obj).ptr);
            return *this;
        }

        Numeric &operator/=(Numeric &obj) override
        {
            *(this->ptr) = *(this->ptr) / *(dynamic_cast<Type<T> &>(obj).ptr);
            return *this;
        }

        // Arithmetic operations (return new object)
        std::unique_ptr<Numeric> operator+(Numeric &obj) override
        {
            return std::make_unique<Type<T>>(*(this->ptr) + *(dynamic_cast<Type<T> &>(obj).ptr));
        }

        std::unique_ptr<Numeric> operator-(Numeric &obj) override
        {
            return std::make_unique<Type<T>>(*(this->ptr) - *(dynamic_cast<Type<T> &>(obj).ptr));
        }

        std::unique_ptr<Numeric> operator*(Numeric &obj) override
        {
            return std::make_unique<Type<T>>(*(this->ptr) * *(dynamic_cast<Type<T> &>(obj).ptr));
        }

        std::unique_ptr<Numeric> operator/(Numeric &obj) override
        {
            return std::make_unique<Type<T>>(*(this->ptr) / *(dynamic_cast<Type<T> &>(obj).ptr));
        }

        // Comparison operators
        bool operator<(Numeric &obj) override
        {
            return *(this->ptr) < *(dynamic_cast<Type<T> &>(obj).ptr);
        }

        bool operator>(Numeric &obj) override
        {
            return *(this->ptr) > *(dynamic_cast<Type<T> &>(obj).ptr);
        }

        bool operator==(Numeric &obj) override
        {
            return *(this->ptr) == *(dynamic_cast<Type<T> &>(obj).ptr);
        }

        // Friend functions for I/O

        friend std::ostream &operator<<(std::ostream &os, const Type<T> &obj)
        {
            os << *(obj.ptr);
            return os;
        }

        friend std::istream &operator>>(std::istream &is, Type<T> &obj)
        {
            is >> *(obj.ptr);
            return is;
        }

        std::ostream &print(std::ostream &os)
        {
            os << *this;
            return os;
        }
    };
}
