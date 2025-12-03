#ifndef FRACTION_OPERATORS_H
#define FRACTION_OPERATORS_H

#include "Fraction.h"
#include <type_traits>

// Дружественные функции для операций с числовым типом слева и дробью справа

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Fraction operator+(T value, const Fraction& frac) {
    return Fraction(value) + frac;
}

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Fraction operator-(T value, const Fraction& frac) {
    return Fraction(value) - frac;
}

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Fraction operator*(T value, const Fraction& frac) {
    return Fraction(value) * frac;
}

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Fraction operator/(T value, const Fraction& frac) {
    return Fraction(value) / frac;
}

// Дружественные функции для операций сравнения с числовым типом слева

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
bool operator==(T value, const Fraction& frac) {
    return Fraction(value) == frac;
}

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
bool operator!=(T value, const Fraction& frac) {
    return Fraction(value) != frac;
}

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
bool operator<(T value, const Fraction& frac) {
    return Fraction(value) < frac;
}

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
bool operator<=(T value, const Fraction& frac) {
    return Fraction(value) <= frac;
}

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
bool operator>(T value, const Fraction& frac) {
    return Fraction(value) > frac;
}

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
bool operator>=(T value, const Fraction& frac) {
    return Fraction(value) >= frac;
}

#endif