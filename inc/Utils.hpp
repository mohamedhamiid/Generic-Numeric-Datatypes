#pragma once
#include <iostream>
#include "Complex.hpp"

/**
 * @file Utils.hpp
 * @brief Utility type traits and helpers for generic numeric operations.
 */

/**
 * @brief Type trait to detect if a type is a specialization of myStd::Complex.
 *
 * Primary template: defaults to false.
 * Specialization: true for myStd::Complex<T, U>.
 */
template <typename>
struct is_complex : std::false_type
{
    // By default, a type is not considered complex.
};

/**
 * @brief Specialization of is_complex for myStd::Complex<T, U>.
 *
 * This specialization sets is_complex<myStd::Complex<T, U>>::value to true.
 */
template <typename T, typename U>
struct is_complex<myStd::Complex<T, U>> : std::true_type
{
    // Any myStd::Complex<T, U> is considered complex.
};