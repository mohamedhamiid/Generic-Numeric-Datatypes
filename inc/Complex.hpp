#pragma once
#include <iostream>
#include <cmath>

namespace myStd
{
    // Forward declaration of Type template for friendship
    template <typename T>
    class Type;

    /**
     * @brief Generic Complex number class supporting arithmetic and comparison operations.
     *
     * @tparam T Type of the real part.
     * @tparam U Type of the imaginary part.
     */
    template <typename T, typename U>
    class Complex
    {
    private:
        T real; ///< Real part of the complex number
        U img;  ///< Imaginary part of the complex number

        // Allow all instantiations of Type<T> to access private members
        template <typename>
        friend class Type;

    public:
        /**
         * @brief Default constructor. Initializes real and imaginary parts to default values.
         */
        Complex() = default;

        /**
         * @brief Parameterized constructor.
         * @param real Real part.
         * @param img Imaginary part.
         */
        Complex(T real, U img) : real(real), img(img) {}

        /**
         * @brief Addition operator.
         * @param obj Complex number to add.
         * @return Sum as a new Complex object.
         */
        Complex<T, U> operator+(const Complex<T, U> &obj)
        {
            return {this->real + obj.real, this->img + obj.img};
        }

        /**
         * @brief Compound addition assignment.
         * @param obj Complex number to add.
         * @return Reference to this object.
         */
        Complex<T, U> &operator+=(const Complex<T, U> &obj)
        {
            this->real += obj.real;
            this->img += obj.img;
            return *this;
        }

        /**
         * @brief Subtraction operator.
         * @param obj Complex number to subtract.
         * @return Difference as a new Complex object.
         */
        Complex<T, U> operator-(const Complex<T, U> &obj)
        {
            return {this->real - obj.real, this->img - obj.img};
        }

        /**
         * @brief Compound subtraction assignment.
         * @param obj Complex number to subtract.
         * @return Reference to this object.
         */
        Complex<T, U> &operator-=(const Complex<T, U> &obj)
        {
            this->real -= obj.real;
            this->img -= obj.img;
            return *this;
        }

        /**
         * @brief Multiplication operator.
         * @param obj Complex number to multiply.
         * @return Product as a new Complex object.
         */
        Complex<T, U> operator*(const Complex<T, U> &obj)
        {
            return {
                this->real * obj.real - this->img * obj.img,
                this->real * obj.img + this->img * obj.real};
        }

        /**
         * @brief Compound multiplication assignment.
         * @param obj Complex number to multiply.
         * @return Reference to this object.
         */
        Complex<T, U> &operator*=(const Complex<T, U> &obj)
        {
            *this = *this * obj;
            return *this;
        }

        /**
         * @brief Division operator.
         * @param obj Complex number to divide by.
         * @return Quotient as a new Complex object.
         */
        Complex<T, U> operator/(const Complex<T, U> &obj)
        {
            T denom = obj.real * obj.real + obj.img * obj.img;
            return {
                (this->real * obj.real + this->img * obj.img) / denom,
                (this->img * obj.real - this->real * obj.img) / denom};
        }

        /**
         * @brief Compound division assignment.
         * @param obj Complex number to divide by.
         * @return Reference to this object.
         */
        Complex<T, U> &operator/=(const Complex<T, U> &obj)
        {
            *this = *this / obj;
            return *this;
        }

        /**
         * @brief Less-than comparison operator (by magnitude).
         * @param obj Complex number to compare.
         * @return true if this object's magnitude is less than obj's.
         */
        bool operator<(const Complex<T, U> &obj)
        {
            auto mag1 = std::sqrt(this->real * this->real + this->img * this->img);
            auto mag2 = std::sqrt(obj.real * obj.real + obj.img * obj.img);
            return mag1 < mag2;
        }

        /**
         * @brief Greater-than comparison operator (by magnitude).
         * @param obj Complex number to compare.
         * @return true if this object's magnitude is greater than obj's.
         */
        bool operator>(const Complex<T, U> &obj)
        {
            auto mag1 = std::sqrt(this->real * this->real + this->img * this->img);
            auto mag2 = std::sqrt(obj.real * obj.real + obj.img * obj.img);
            return mag1 > mag2;
        }

        /**
         * @brief Equality comparison operator.
         * @param obj Complex number to compare.
         * @return true if both real and imaginary parts are equal.
         */
        bool operator==(const Complex<T, U> &obj) const
        {
            return std::tie(real, img) == std::tie(obj.real, obj.img);
        }

        /**
         * @brief Inequality comparison operator.
         * @param obj Complex number to compare.
         * @return true if either real or imaginary part differs.
         */
        bool operator!=(const Complex<T, U> &obj)
        {
            return !(*this == obj);
        }

        /**
         * @brief Returns the magnitude (absolute value) of the complex number.
         * @return Magnitude as double.
         */
        double getValue()
        {
            return std::sqrt(this->real * this->real + this->img * this->img);
        }

        /**
         * @brief Output stream operator for printing.
         * @param os Output stream.
         * @param c Complex number to print.
         * @return Reference to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const myStd::Complex<T, U> &c)
        {
            os << "(" << c.real << (c.img >= 0 ? " + " : " - ")
               << std::abs(c.img) << "i)";
            return os;
        }

        /**
         * @brief Input stream operator for reading.
         * @param is Input stream.
         * @param c Complex number to read into.
         * @return Reference to the input stream.
         * @note Example input format: (real imag)
         */
        friend std::istream &operator>>(std::istream &is, myStd::Complex<T, U> &c)
        {
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter real part : " << std::endl;
            is >> c.real;

            std::cout << "Enter imaginary part : " << std::endl;
            is >> c.img;
            return is;
        }
    };
}