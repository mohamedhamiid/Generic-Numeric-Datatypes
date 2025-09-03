#pragma once
#include <iostream>
#include <cmath>
namespace myStd
{
    template <typename T, typename U>
    class Complex
    {
    private:
        T real;
        U img;

    public:
        Complex() = default;
        Complex(T real, U img) : real(real), img(img) {};
        static Complex<T, U> create(T real, U img)
        {
            return Complex<T, U>(real, img);
        }

        Complex<T, U> operator+(const Complex<T, U> &obj)
        {
            return {this->real + obj.real, this->img + obj.img};
        }

        Complex<T, U> &operator+=(const Complex<T, U> &obj)
        {
            this->real += obj.real;
            this->img += obj.img;
            return *this;
        }
        Complex<T, U> operator-(const Complex<T, U> &obj)
        {
            return {this->real - obj.real, this->img - obj.img};
        }
        Complex<T, U> &operator-=(const Complex<T, U> &obj)
        {
            this->real -= obj.real;
            this->img -= obj.img;
            return *this;
        }
        Complex<T, U> operator*(const Complex<T, U> &obj)
        {
            return {
                this->real * obj.real - this->img * obj.img,
                this->real * obj.img + this->img * obj.real};
        }

        Complex<T, U> &operator*=(const Complex<T, U> &obj)
        {
            *this = *this * obj;
            return *this;
        }

        Complex<T, U> operator/(const Complex<T, U> &obj)
        {
            T denom = obj.real * obj.real + obj.img * obj.img;
            return {
                (this->real * obj.real + this->img * obj.img) / denom,
                (this->img * obj.real - this->real * obj.img) / denom};
        }

        Complex<T, U> &operator/=(const Complex<T, U> &obj)
        {
            *this = *this / obj;
            return *this;
        }

        bool operator<(const Complex<T, U> &obj)
        {
            auto mag1 = std::sqrt(this->real * this->real + this->img * this->img);
            auto mag2 = std::sqrt(obj.real * obj.real + obj.img * obj.img);
            return mag1 < mag2;
        }

        bool operator>(const Complex<T, U> &obj)
        {
            auto mag1 = std::sqrt(this->real * this->real + this->img * this->img);
            auto mag2 = std::sqrt(obj.real * obj.real + obj.img * obj.img);
            return mag1 > mag2;
        }

        bool operator==(const Complex<T, U> &obj) const
        {
            return std::tie(real, img) == std::tie(obj.real, obj.img);
        }

        bool operator!=(const Complex<T, U> &obj)
        {
            return !(*this == obj);
        }

        friend std::ostream &operator<<(std::ostream &os, const myStd::Complex<T, U> &c)
        {
            os << "(" << c.real << (c.img >= 0 ? " + " : " - ")
               << std::abs(c.img) << "i)";
            return os;
        }

        friend std::istream &operator>>(std::istream &is, myStd::Complex<T, U> &c)
        {
            // Example input format: (real imag)
            char ch;
            is >> ch; // read '('
            is >> c.real >> c.img;
            is >> ch; // read ')'
            return is;
        }
    };
}