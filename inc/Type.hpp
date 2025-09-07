#pragma once
#include <iostream>
#include <memory>

#include "Utils.hpp"
#include "Numeric.hpp"
#include "Complex.hpp"

namespace myStd
{
    /**
     * @brief Generic numeric wrapper class supporting arithmetic and polymorphic operations.
     *
     * @tparam T Underlying numeric or complex type.
     */
    template <typename T>
    class Type : public Numeric
    {
    private:
        // Smart pointer to the underlying value of type T
        std::unique_ptr<T> ptr;

        // Allow all instantiations of Type to access private members of each other
        template <typename>
        friend class Type;

        /**
         * @brief Extracts the value of any supported complex type as Complex<double, double>.
         *
         * @param obj Reference to a Numeric object.
         * @param c Output parameter to hold the extracted complex value.
         * @return true if obj is a supported complex type, false otherwise.
         */
        bool extractComplexAsDouble(Numeric &obj, Complex<double, double> &c)
        {
            if (auto *ci = dynamic_cast<Type<Complex<int, int>> *>(&obj))
            {
                c = Complex<double, double>(static_cast<double>(ci->ptr->real), static_cast<double>(ci->ptr->img));
                return true;
            }
            if (auto *cd = dynamic_cast<Type<Complex<double, double>> *>(&obj))
            {
                c = Complex<double, double>(cd->ptr->real, cd->ptr->img);
                return true;
            }
            if (auto *cid = dynamic_cast<Type<Complex<int, double>> *>(&obj))
            {
                c = Complex<double, double>(static_cast<double>(cid->ptr->real), cid->ptr->img);
                return true;
            }
            if (auto *cdi = dynamic_cast<Type<Complex<double, int>> *>(&obj))
            {
                c = Complex<double, double>(cdi->ptr->real, static_cast<double>(cdi->ptr->img));
                return true;
            }
            return false;
        }

    public:
        // =========================
        // Constructors & Destructor
        // =========================

        /**
         * @brief Default constructor.
         */
        Type() = default;

        /**
         * @brief Construct from a value of type T.
         * @param val Initial value.
         */
        explicit Type(T val)
        {
            ptr = std::make_unique<T>(val);
        }

        /**
         * @brief Destructor.
         */
        ~Type() = default;

        /**
         * @brief Copy constructor.
         * @param obj Object to copy from.
         */
        Type(const Type<T> &obj)
        {
            ptr = std::make_unique<T>(*(obj.ptr));
        }

        /**
         * @brief Move constructor.
         * @param obj Object to move from.
         */
        Type(Type<T> &&obj)
        {
            ptr = std::make_unique<T>(*(obj.ptr));
        }

        // =========================
        // Assignment Operators
        // =========================

        /**
         * @brief Copy assignment operator.
         * @param val Object to copy from.
         * @return Reference to this object.
         */
        Type<T> &operator=(const Type<T> &val)
        {
            ptr = std::make_unique<T>(*(val.ptr));
            return *this;
        }

        /**
         * @brief Assignment from unique_ptr<Numeric>. Only allowed for Type<double> and Type<Complex<double, double>>.
         * @param uptr Unique pointer to a Numeric object.
         * @return Reference to this object.
         * @throws std::runtime_error if assignment is invalid.
         */
        Type<T> &operator=(std::unique_ptr<Numeric> uptr)
        {
            static_assert(
                (std::is_same_v<T, Complex<double, double>>) || (std::is_same_v<T, double>),
                "Assignment from unique_ptr<Numeric> is only allowed for Type<Complex<double, double>> or Type<double>!");
            if (auto *castedPtr = dynamic_cast<Type<T> *>(uptr.get()))
            {
                ptr = std::make_unique<T>(*(castedPtr->ptr));
            }
            else
            {
                throw(std::runtime_error("Invalid Assignment!"));
            }
            return *this;
        }

        // =========================
        // Compound Assignment Operators
        // =========================

        /**
         * @brief Compound addition assignment.
         * @param obj Numeric object to add.
         * @return Reference to this object.
         */
        Numeric &operator+=(Numeric &obj) override
        {
            auto castedObj = dynamic_cast<Type<T> *>(&obj);
            if (castedObj)
                *(this->ptr) = *(this->ptr) + *(castedObj->ptr);
            // If T is complex, add real part and keep imaginary part
            if constexpr (is_complex<T>::value)
                this->ptr->real = this->ptr->real + obj.getValue();
            else
                *(this->ptr) = *(this->ptr) + static_cast<T>(obj.getValue());
            return *this;
        }

        /**
         * @brief Compound subtraction assignment.
         * @param obj Numeric object to subtract.
         * @return Reference to this object.
         */
        Numeric &operator-=(Numeric &obj) override
        {
            auto castedObj = dynamic_cast<Type<T> *>(&obj);
            if (castedObj)
                *(this->ptr) = *(this->ptr) - *(castedObj->ptr);
            if constexpr (is_complex<T>::value)
                this->ptr->real = this->ptr->real - obj.getValue();
            else
                *(this->ptr) = *(this->ptr) - static_cast<T>(obj.getValue());
            return *this;
        }

        /**
         * @brief Compound multiplication assignment.
         * @param obj Numeric object to multiply.
         * @return Reference to this object.
         */
        Numeric &operator*=(Numeric &obj) override
        {
            auto castedObj = dynamic_cast<Type<T> *>(&obj);
            if (castedObj)
                *(this->ptr) = *(this->ptr) * *(castedObj->ptr);
            if constexpr (is_complex<T>::value)
                this->ptr->real = this->ptr->real * obj.getValue();
            else
                *(this->ptr) = *(this->ptr) * static_cast<T>(obj.getValue());
            return *this;
        }

        /**
         * @brief Compound division assignment.
         * @param obj Numeric object to divide by.
         * @return Reference to this object.
         */
        Numeric &operator/=(Numeric &obj) override
        {
            auto castedObj = dynamic_cast<Type<T> *>(&obj);
            if (castedObj)
                *(this->ptr) = *(this->ptr) / *(castedObj->ptr);
            if constexpr (is_complex<T>::value)
                this->ptr->real = this->ptr->real / obj.getValue();
            else
                *(this->ptr) = *(this->ptr) / static_cast<T>(obj.getValue());
            return *this;
        }

        // =========================
        // Arithmetic Operators
        // =========================

        /**
         * @brief Addition operator. Handles same and mixed types.
         * @param obj Numeric object to add.
         * @return Unique pointer to the result as Numeric.
         */
        std::unique_ptr<Numeric> operator+(Numeric &obj) override
        {
            auto castedObj = dynamic_cast<Type<T> *>(&obj);
            // Same type
            if (castedObj)
            {
                return std::make_unique<Type<T>>(*(this->ptr) + *(castedObj->ptr));
            }

            // If first operand is complex, promote to Complex<double, double>
            if constexpr (is_complex<T>::value)
            {
                Complex<double, double> c(this->ptr->real + obj.getValue(), this->ptr->img);
                return std::make_unique<Type<Complex<double, double>>>(c);
            }
            else
            {
                // If second operand is complex, promote to Complex<double, double>
                Complex<double, double> c_other;
                if (extractComplexAsDouble(obj, c_other))
                {
                    Complex<double, double> c(c_other.real + this->getValue(), c_other.img);
                    return std::make_unique<Type<Complex<double, double>>>(c);
                }
                else
                {
                    // Both are arithmetic, promote to double
                    double sum = this->getValue() + obj.getValue();
                    return std::make_unique<Type<double>>(sum);
                }
            }
        }

        /**
         * @brief Subtraction operator. Handles same and mixed types.
         * @param obj Numeric object to subtract.
         * @return Unique pointer to the result as Numeric.
         */
        std::unique_ptr<Numeric> operator-(Numeric &obj) override
        {
            auto castedObj = dynamic_cast<Type<T> *>(&obj);
            // Same type
            if (castedObj)
            {
                return std::make_unique<Type<T>>(*(this->ptr) - *(castedObj->ptr));
            }

            // If first operand is complex, promote to Complex<double, double>
            if constexpr (is_complex<T>::value)
            {
                Complex<double, double> c(this->ptr->real - obj.getValue(), this->ptr->img);
                return std::make_unique<Type<Complex<double, double>>>(c);
            }
            else
            {
                // If second operand is complex, promote to Complex<double, double>
                Complex<double, double> c_other;
                if (extractComplexAsDouble(obj, c_other))
                {
                    Complex<double, double> c(c_other.real - this->getValue(), c_other.img);
                    return std::make_unique<Type<Complex<double, double>>>(c);
                }
                else
                {
                    // Both are arithmetic, promote to double
                    double sum = this->getValue() - obj.getValue();
                    return std::make_unique<Type<double>>(sum);
                }
            }
        }

        /**
         * @brief Multiplication operator.
         * @param obj Numeric object to multiply.
         * @return Unique pointer to the result as Numeric.
         */
        template <typename U = T>
        std::enable_if_t<!is_complex<U>::value, std::unique_ptr<Numeric>>
        operator*(Numeric &obj)
        {
            auto castedObj = dynamic_cast<Type<T> *>(&obj);
            // Same type
            if (castedObj)
            {
                return std::make_unique<Type<T>>(*(this->ptr) * *(castedObj->ptr));
            }

            // If first operand is complex, promote to Complex<double, double>
            if constexpr (is_complex<T>::value)
            {
                throw(std::runtime_error("Can't do this operation for complex numbers"));
            }
            else
            {
                // If second operand is complex, promote to Complex<double, double>
                Complex<double, double> c_other;
                if (extractComplexAsDouble(obj, c_other))
                {
                    throw(std::runtime_error("Can't do this operation for complex numbers"));
                }
                else
                {
                    // Both are arithmetic, promote to double
                    double sum = this->getValue() * obj.getValue();
                    return std::make_unique<Type<double>>(sum);
                }
            }
        }

        /**
         * @brief Division operator.
         * @param obj Numeric object to divide by.
         * @return Unique pointer to the result as Numeric.
         */
        template <typename U = T>
        std::enable_if_t<!is_complex<U>::value, std::unique_ptr<Numeric>>
        operator/(Numeric &obj)
        {
            auto castedObj = dynamic_cast<Type<T> *>(&obj);
            // Same type
            if (castedObj)
            {
                return std::make_unique<Type<T>>(*(this->ptr) / *(castedObj->ptr));
            }

            // If first operand is complex, promote to Complex<double, double>
            if constexpr (is_complex<T>::value)
            {
                throw(std::runtime_error("Can't do this operation for complex numbers"));
            }
            else
            {
                // If second operand is complex, promote to Complex<double, double>
                Complex<double, double> c_other;
                if (extractComplexAsDouble(obj, c_other))
                {
                    throw(std::runtime_error("Can't do this operation for complex numbers"));
                }
                else
                {
                    // Both are arithmetic, promote to double
                    double sum = this->getValue() / obj.getValue();
                    return std::make_unique<Type<double>>(sum);
                }
            }
        }

        // =========================
        // Comparison Operators
        // =========================

        /**
         * @brief Less-than comparison operator.
         * @param obj Numeric object to compare.
         * @return true if this object is less than obj.
         */
        bool operator<(Numeric &obj) override
        {
            Type<T> *castedObj = dynamic_cast<Type<T> *>(&obj);
            if (typeid(*this) == typeid(castedObj))
                return *(this->ptr) < *(castedObj->ptr);

            return this->getValue() < obj.getValue();
        }

        /**
         * @brief Greater-than comparison operator.
         * @param obj Numeric object to compare.
         * @return true if this object is greater than obj.
         */
        bool operator>(Numeric &obj) override
        {
            return *(this->ptr) > *(dynamic_cast<Type<T> &>(obj).ptr);
        }

        /**
         * @brief Equality comparison operator.
         * @param obj Numeric object to compare.
         * @return true if this object is equal to obj.
         */
        bool operator==(Numeric &obj) override
        {
            return *(this->ptr) == *(dynamic_cast<Type<T> &>(obj).ptr);
        }

        // =========================
        // I/O Operators
        // =========================

        /**
         * @brief Output stream operator.
         * @param os Output stream.
         * @param obj Type object to print.
         * @return Reference to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const Type<T> &obj)
        {
            os << *(obj.ptr);
            return os;
        }

        /**
         * @brief Input stream operator.
         * @param is Input stream.
         * @param obj Type object to read into.
         * @return Reference to the input stream.
         */
        friend std::istream &operator>>(std::istream &is, Type<T> &obj)
        {
            is >> *(obj.ptr);
            return is;
        }

        /**
         * @brief Prints the value to the provided output stream.
         * @param os Output stream.
         * @return Reference to the output stream.
         */
        std::ostream &print(std::ostream &os)
        {
            os << *this << std::endl;
            return os;
        }

        /**
         * @brief Returns the value as double.
         *        For complex types, returns the magnitude.
         * @return Value as double.
         */
        double getValue()
        {
            if constexpr (is_complex<T>::value)
            {
                return static_cast<double>(this->ptr->getValue());
            }
            else
            {
                return static_cast<double>(*(this->ptr));
            }
        }
    };
}
