# Generic Numeric Datatypes

A modern C++ library providing a polymorphic numeric type system with type safety and dynamic dispatch for arithmetic operations.

## Overview

This library implements a type-safe numeric wrapper system using modern C++ features including templates, smart pointers, and virtual inheritance. It provides a unified interface for different numeric types while maintaining type safety and enabling polymorphic behavior.

## Features

- **Polymorphic Design**: Abstract base class `Numeric` enables runtime polymorphism
- **Type Safety**: Template-based implementation with compile-time type checking
- **Smart Pointer Integration**: Uses `std::unique_ptr` for memory safety
- **Complete Operator Set**: Full arithmetic and comparison operator support
- **Stream I/O Support**: Built-in input/output stream operators
- **Modern C++ Standards**: Utilizes C++17/20 features like `std::is_same_v` and `if constexpr`

## Architecture

### Core Components

#### `Numeric` (Abstract Base Class)
- Pure virtual interface for all numeric operations
- Defines contract for arithmetic (`+`, `-`, `*`, `/`) and compound assignment (`+=`, `-=`, `*=`, `/=`) operators
- Provides comparison operators (`<`, `>`, `==`)
- Uses smart pointers for memory-safe return values

#### `Type<T>` (Template Implementation)
- Concrete implementation of the `Numeric` interface
- Generic template supporting any arithmetic type
- Type-safe operations with runtime type checking
- Automatic type validation in assignment operations

## Usage Examples

### Basic Operations

```cpp
#include "inc/Type.hpp"
using namespace myStd;

// Create numeric objects
Type<int> a(10);
Type<int> b(20);

// Arithmetic operations
auto sum = a + b;           // Returns std::unique_ptr<Numeric>
auto difference = a - b;    // Returns std::unique_ptr<Numeric>

// Compound assignment
a += b;  // a becomes 30
a -= b;  // a becomes 10

// Comparisons
bool isLess = a < b;        // true
bool isEqual = a == b;      // false
```

### Polymorphic Usage

```cpp
// Using base class pointers
std::unique_ptr<Numeric> num1 = std::make_unique<Type<double>>(3.14);
std::unique_ptr<Numeric> num2 = std::make_unique<Type<double>>(2.71);

// Polymorphic operations
auto result = *num1 + *num2;
```

### Stream I/O

```cpp
Type<float> value;
std::cout << "Enter a number: ";
std::cin >> value;
std::cout << "You entered: " << value << std::endl;
```

## File Structure

```
project/
├── inc/
│   ├── Numeric.hpp     # Abstract base class definition
│   └── Type.hpp        # Template implementation
└── README.md           # This file
```

## Requirements

- **C++ Standard**: C++17 or later
- **Compiler Support**: Any modern C++ compiler (GCC 7+, Clang 5+, MSVC 2017+)
- **Dependencies**: Standard library only (`<memory>`, `<iostream>`, `<type_traits>`)

## Compilation

### Basic Compilation
```bash
g++ -std=c++17 -I./inc your_source.cpp -o your_program
```

### With Optimizations
```bash
g++ -std=c++17 -O2 -Wall -Wextra -I./inc your_source.cpp -o your_program
```

### CMake Example
```cmake
cmake_minimum_required(VERSION 3.10)
project(NumericTypeSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)

add_executable(example example.cpp)
```

## Design Patterns

### Virtual Inheritance
The library uses virtual inheritance to enable polymorphic behavior while maintaining type safety through templates.

### RAII and Smart Pointers
Memory management is handled automatically using `std::unique_ptr`, ensuring no memory leaks.

### Template Specialization
The `Type<T>` template can work with any arithmetic type, providing flexibility while maintaining performance.

## Type Safety Features

- **Compile-time Type Checking**: Assignment operations validate type compatibility
- **Runtime Type Validation**: Dynamic casting ensures type safety at runtime
- **Exception Handling**: Type mismatches throw `std::runtime_error`

## Known Limitations

1. **Dynamic Casting Overhead**: Runtime type checking using `dynamic_cast` may impact performance
2. **Single Type Operations**: Mixed-type arithmetic operations are not currently supported
3. **Incomplete Implementation**: The `operator+` method in the current codebase appears to have a missing return statement

## Future Enhancements

- [ ] Mixed-type arithmetic support
- [ ] Additional numeric types (complex numbers, fractions)
- [ ] Performance optimizations
- [ ] Extended mathematical functions (trigonometric, logarithmic)
- [ ] Serialization support

## Contributing

When contributing to this project:

1. Maintain C++17 compatibility
2. Follow RAII principles
3. Add appropriate unit tests
4. Document any new features
5. Ensure exception safety
