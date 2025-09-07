#pragma once
#include <iostream>
#include "Complex.hpp"
// Helper trait: defaults to false
template <typename>
struct is_complex : std::false_type
{
};

// Specialization: true for Complex<T, U>
template <typename T, typename U>
struct is_complex<myStd::Complex<T, U>> : std::true_type
{
};