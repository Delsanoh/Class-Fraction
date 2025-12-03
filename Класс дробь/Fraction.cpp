#include "Fraction.h"
#include <sstream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <algorithm>

bool Fraction::willAdditionOverflow(int64_t a, int64_t b) {
    if (b > 0) {
        return a > std::numeric_limits<int64_t>::max() - b;
    }
    else {
        return a < std::numeric_limits<int64_t>::min() - b;
    }
}

bool Fraction::willMultiplicationOverflow(int64_t a, int64_t b) {
    if (a > 0) {
        if (b > 0) {
            return a > std::numeric_limits<int64_t>::max() / b;
        }
        else {
            return b < std::numeric_limits<int64_t>::min() / a;
        }
    }
    else {
        if (b > 0) {
            return a < std::numeric_limits<int64_t>::min() / b;
        }
        else {
            return a != 0 && b < std::numeric_limits<int64_t>::max() / a;
        }
    }
}

bool Fraction::willMultiplicationOverflow(uint64_t a, uint64_t b) {
    if (a == 0 || b == 0) return false;
    return a > std::numeric_limits<uint64_t>::max() / b;
}

int64_t Fraction::gcd(int64_t a, int64_t b) const {
    a = std::llabs(a);
    b = std::llabs(b);
    while (b != 0) {
        int64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void Fraction::reduce() {
    if (numerator == 0) {
        denominator = 1;
        return;
    }

    int64_t divisor = gcd(numerator, static_cast<int64_t>(denominator));
    if (divisor != 1) {
        numerator /= divisor;
        denominator /= static_cast<uint64_t>(divisor);
    }
}

void Fraction::normalize() {
    if (denominator == 0) {
        throw FractionException("Знаменатель не может быть нулем");
    }

    if (static_cast<int64_t>(denominator) < 0) {
        if (numerator == std::numeric_limits<int64_t>::min()) {
            throw FractionException("Переполнение числителя при нормализации");
        }
        numerator = -numerator;
        denominator = -static_cast<int64_t>(denominator);
    }

    reduce();
}

Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(int64_t num) : numerator(num), denominator(1) {
    normalize();
}

Fraction::Fraction(int64_t num, uint64_t den) : numerator(num), denominator(den) {
    normalize();
}

Fraction::Fraction(const Fraction& other)
    : numerator(other.numerator), denominator(other.denominator) {
}

Fraction::Fraction(Fraction&& other) noexcept
    : numerator(other.numerator), denominator(other.denominator) {
    other.numerator = 0;
    other.denominator = 1;
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

Fraction& Fraction::operator=(Fraction&& other) noexcept {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;

        other.numerator = 0;
        other.denominator = 1;
    }
    return *this;
}

Fraction Fraction::operator+(const Fraction& other) const {
    if (willMultiplicationOverflow(numerator, static_cast<int64_t>(other.denominator)) ||
        willMultiplicationOverflow(other.numerator, static_cast<int64_t>(denominator)) ||
        willMultiplicationOverflow(denominator, other.denominator)) {
        throw FractionException("Переполнение при сложении дробей");
    }

    int64_t num1 = numerator * static_cast<int64_t>(other.denominator);
    int64_t num2 = other.numerator * static_cast<int64_t>(denominator);
    uint64_t den = denominator * other.denominator;

    if (willAdditionOverflow(num1, num2)) {
        throw FractionException("Переполнение числителя при сложении");
    }

    int64_t result_num = num1 + num2;

    return Fraction(result_num, den);
}

Fraction Fraction::operator-(const Fraction& other) const {
    if (willMultiplicationOverflow(numerator, static_cast<int64_t>(other.denominator)) ||
        willMultiplicationOverflow(other.numerator, static_cast<int64_t>(denominator)) ||
        willMultiplicationOverflow(denominator, other.denominator)) {
        throw FractionException("Переполнение при вычитании дробей");
    }

    int64_t num1 = numerator * static_cast<int64_t>(other.denominator);
    int64_t num2 = other.numerator * static_cast<int64_t>(denominator);
    uint64_t den = denominator * other.denominator;

    if (num2 > 0 && num1 < std::numeric_limits<int64_t>::min() + num2) {
        throw FractionException("Переполнение числителя при вычитании");
    }
    if (num2 < 0 && num1 > std::numeric_limits<int64_t>::max() + num2) {
        throw FractionException("Переполнение числителя при вычитании");
    }

    int64_t result_num = num1 - num2;

    return Fraction(result_num, den);
}

Fraction Fraction::operator*(const Fraction& other) const {
    if (willMultiplicationOverflow(numerator, other.numerator)) {
        throw FractionException("Переполнение при умножении дробей");
    }

    if (willMultiplicationOverflow(denominator, other.denominator)) {
        throw FractionException("Переполнение при умножении дробей");
    }

    int64_t num = numerator * other.numerator;
    uint64_t den = denominator * other.denominator;

    return Fraction(num, den);
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) {
        throw FractionException("Деление на ноль");
    }

    if (willMultiplicationOverflow(numerator, static_cast<int64_t>(other.denominator))) {
        throw FractionException("Переполнение при делении дробей");
    }

    if (willMultiplicationOverflow(static_cast<int64_t>(denominator), other.numerator)) {
        throw FractionException("Переполнение при делении дробей");
    }

    int64_t num = numerator * static_cast<int64_t>(other.denominator);
    int64_t den = static_cast<int64_t>(denominator) * other.numerator;

    if (den < 0) {
        num = -num;
        den = -den;
    }

    if (den < 0 || static_cast<uint64_t>(den) > std::numeric_limits<uint64_t>::max()) {
        throw FractionException("Переполнение знаменателя при делении");
    }

    return Fraction(num, static_cast<uint64_t>(den));
}

Fraction Fraction::operator-() const {
    if (numerator == std::numeric_limits<int64_t>::min()) {
        throw FractionException("Переполнение при унарном минусе");
    }
    return Fraction(-numerator, denominator);
}

Fraction Fraction::operator!() const {
    if (numerator == 0) {
        throw FractionException("Невозможно получить обратную дробь к нулю");
    }
    if (numerator > 0) {
        if (denominator > static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
            throw FractionException("Переполнение при получении обратной дроби");
        }
        return Fraction(static_cast<int64_t>(denominator), static_cast<uint64_t>(numerator));
    }
    else {
        uint64_t abs_numerator = static_cast<uint64_t>(-numerator);
        if (denominator > static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
            throw FractionException("Переполнение при получении обратной дроби");
        }
        return Fraction(-static_cast<int64_t>(denominator), abs_numerator);
    }
}

bool Fraction::operator==(const Fraction& other) const {
    return numerator == other.numerator && denominator == other.denominator;
}

bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}

bool Fraction::operator<(const Fraction& other) const {
    if (numerator < 0 && other.numerator >= 0) return true;
    if (numerator >= 0 && other.numerator < 0) return false;

    if (numerator < 0) {
        int64_t left = std::llabs(numerator) * static_cast<int64_t>(other.denominator);
        int64_t right = std::llabs(other.numerator) * static_cast<int64_t>(denominator);
        return left > right;
    }
    else {
        int64_t left = numerator * static_cast<int64_t>(other.denominator);
        int64_t right = other.numerator * static_cast<int64_t>(denominator);
        return left < right;
    }
}

bool Fraction::operator<=(const Fraction& other) const {
    return *this < other || *this == other;
}

bool Fraction::operator>(const Fraction& other) const {
    return !(*this <= other);
}

bool Fraction::operator>=(const Fraction& other) const {
    return !(*this < other);
}

Fraction& Fraction::operator++() {
    if (willAdditionOverflow(numerator, static_cast<int64_t>(denominator))) {
        throw FractionException("Переполнение при инкременте");
    }
    numerator += static_cast<int64_t>(denominator);
    reduce();
    return *this;
}

Fraction Fraction::operator++(int) {
    Fraction temp = *this;
    ++(*this);
    return temp;
}

Fraction& Fraction::operator--() {
    if (willAdditionOverflow(numerator, -static_cast<int64_t>(denominator))) {
        throw FractionException("Переполнение при декременте");
    }
    numerator -= static_cast<int64_t>(denominator);
    reduce();
    return *this;
}

Fraction Fraction::operator--(int) {
    Fraction temp = *this;
    --(*this);
    return temp;
}

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
    *this = *this - other;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& other) {
    *this = *this * other;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
    *this = *this / other;
    return *this;
}

Fraction::operator double() const {
    return static_cast<double>(numerator) / denominator;
}

Fraction::operator float() const {
    return static_cast<float>(numerator) / denominator;
}

Fraction::operator int64_t() const {
    return numerator / static_cast<int64_t>(denominator);
}

Fraction::operator uint64_t() const {
    if (numerator < 0) {
        throw FractionException("Отрицательная дробь не может быть приведена к uint64_t");
    }
    return static_cast<uint64_t>(numerator) / denominator;
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    if (frac.denominator == 1) {
        os << frac.numerator;
    }
    else {
        os << frac.numerator << "/" << frac.denominator;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& frac) {
    int64_t num;
    uint64_t den = 1;
    char slash;

    is >> num;
    if (is.peek() == '/') {
        is >> slash >> den;
    }

    frac = Fraction(num, den);
    return is;
}

std::string Fraction::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

Fraction Fraction::reciprocal() const {
    return !(*this);
}

std::string Fraction::getInfo() const {
    std::stringstream ss;
    ss << "Дробь: " << *this;
    if (denominator != 1) {
        ss << " = " << static_cast<double>(*this);
    }
    return ss.str();
}