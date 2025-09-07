#pragma once
#include <iostream>
#include <memory>

namespace myStd
{
    /**
     * @brief Abstract base class for all numeric types.
     *
     * This class defines a polymorphic interface for numeric operations,
     * enabling arithmetic, comparison, and I/O for derived numeric types.
     */
    class Numeric
    {
    public:
        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived objects via base class pointers.
         */
        virtual ~Numeric() = default;

        /**
         * @brief Pure virtual arithmetic operators.
         *
         * These functions must be implemented by derived classes.
         * They return smart pointers for safe polymorphic ownership.
         *
         * @param other Reference to another Numeric object.
         * @return Unique pointer to the result as a new Numeric object.
         */
        virtual std::unique_ptr<Numeric> operator+(Numeric &) = 0;
        virtual std::unique_ptr<Numeric> operator-(Numeric &) = 0;
        // virtual std::unique_ptr<Numeric> operator*(Numeric &) = 0;
        // virtual std::unique_ptr<Numeric> operator/(Numeric &) = 0;

        /**
         * @brief Pure virtual compound assignment operators.
         *
         * These functions must be implemented by derived classes.
         * They modify the current object and return a reference to it.
         *
         * @param other Reference to another Numeric object.
         * @return Reference to this object after modification.
         */
        virtual Numeric &operator+=(Numeric &) = 0;
        virtual Numeric &operator-=(Numeric &) = 0;
        virtual Numeric &operator*=(Numeric &) = 0;
        virtual Numeric &operator/=(Numeric &) = 0;

        /**
         * @brief Pure virtual comparison operators.
         *
         * These functions must be implemented by derived classes.
         * They compare the current object with another Numeric object.
         *
         * @param other Reference to another Numeric object.
         * @return Result of the comparison.
         */
        virtual bool operator<(Numeric &) = 0;
        virtual bool operator>(Numeric &) = 0;
        virtual bool operator==(Numeric &) = 0;

        /**
         * @brief Pure virtual print function.
         *
         * Allows derived classes to define custom output formatting.
         *
         * @param os Output stream.
         * @return Reference to the output stream.
         */
        virtual std::ostream &print(std::ostream &os) = 0;

        /**
         * @brief Pure virtual function to get the value as double.
         *
         * For arithmetic types, returns the value.
         * For complex types, returns the magnitude.
         *
         * @return Value as double.
         */
        virtual double getValue() = 0;
    };
}