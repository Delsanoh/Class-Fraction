#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <cstdint>
#include <limits>

// Пользовательский класс исключений для дробей
class FractionException : public std::exception {
private:
    std::string message;
public:
    FractionException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Fraction {
private:
    int64_t numerator;      // числитель (хранит знак)
    uint64_t denominator;   // знаменатель (всегда > 0)

    // Приватные методы для приведения к канонической форме
    int64_t gcd(int64_t a, int64_t b) const;  // НОД
    void reduce();          // Сокращение дроби
    void normalize();       // Приведение к канонической форме

    // Вспомогательные методы для безопасных операций
    static bool willAdditionOverflow(int64_t a, int64_t b);
    static bool willMultiplicationOverflow(int64_t a, int64_t b);
    static bool willMultiplicationOverflow(uint64_t a, uint64_t b);

public:
    // Конструкторы
    Fraction();                                 // По умолчанию: 0/1
    Fraction(int64_t num);                      // Целое число
    Fraction(int64_t num, uint64_t den);        // Числитель и знаменатель
    Fraction(const Fraction& other);           // Копирующий конструктор
    Fraction(Fraction&& other) noexcept;       // Перемещающий конструктор

    // Шаблонный конструктор для любого числового типа
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Fraction(T value) : numerator(static_cast<int64_t>(value)), denominator(1) {
        normalize();
    }

    // Деструктор
    ~Fraction() = default;

    // Операторы присваивания
    Fraction& operator=(const Fraction& other);   // Копирующее присваивание
    Fraction& operator=(Fraction&& other) noexcept; // Перемещающее присваивание

    // Методы доступа
    int64_t getNumerator() const { return numerator; }
    uint64_t getDenominator() const { return denominator; }

    // Арифметические операторы с дробями
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    // Шаблонные арифметические операторы для числовых типов (правый аргумент)
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Fraction operator+(T value) const {
        return *this + Fraction(value);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Fraction operator-(T value) const {
        return *this - Fraction(value);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Fraction operator*(T value) const {
        return *this * Fraction(value);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Fraction operator/(T value) const {
        return *this / Fraction(value);
    }

    // Шаблонные операторы сравнения для числовых типов (правый аргумент)
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    bool operator==(T value) const {
        return *this == Fraction(value);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    bool operator!=(T value) const {
        return *this != Fraction(value);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    bool operator<(T value) const {
        return *this < Fraction(value);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    bool operator<=(T value) const {
        return *this <= Fraction(value);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    bool operator>(T value) const {
        return *this > Fraction(value);
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    bool operator>=(T value) const {
        return *this >= Fraction(value);
    }

    // Шаблонные составные операторы присваивания для числовых типов
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Fraction& operator+=(T value) {
        *this = *this + Fraction(value);
        return *this;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Fraction& operator-=(T value) {
        *this = *this - Fraction(value);
        return *this;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Fraction& operator*=(T value) {
        *this = *this * Fraction(value);
        return *this;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Fraction& operator/=(T value) {
        *this = *this / Fraction(value);
        return *this;
    }

    // Унарные операторы
    Fraction operator-() const;                 // Унарный минус
    Fraction operator!() const;                 // Обратная дробь

    // Операторы сравнения с дробями
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

    // Инкремент и декремент
    Fraction& operator++();     // Префиксный инкремент
    Fraction operator++(int);   // Постфиксный инкремент
    Fraction& operator--();     // Префиксный декремент
    Fraction operator--(int);   // Постфиксный декремент

    // Составные операторы присваивания с дробями
    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    // Приведение типов
    explicit operator double() const;
    explicit operator float() const;
    explicit operator int64_t() const;
    explicit operator uint64_t() const;

    // Ввод/вывод
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);
    friend std::istream& operator>>(std::istream& is, Fraction& frac);

    // Вспомогательные методы
    std::string toString() const;
    Fraction reciprocal() const;  // Получение обратной дроби

    // Метод для получения информации об объекте
    std::string getInfo() const;
};

#endif 