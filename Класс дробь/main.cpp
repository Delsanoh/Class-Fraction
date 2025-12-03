#include <iostream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <cstdint>
#include "Fraction.h"
#include "FractionOperators.h"

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "=== ДЕМОНСТРАЦИЯ КЛАССА ДРОБЕЙ С int64_t/uint64_t ===\n\n";

    try {
        std::cout << "1. СОЗДАНИЕ ДРОБЕЙ:\n";
        Fraction f1;
        Fraction f2(5);
        Fraction f3(3, 4);
        Fraction f4(-2, 3);
        Fraction f5(2.5);
        Fraction f6(-1.75);

        std::cout << "f1 = " << f1.getInfo() << std::endl;
        std::cout << "f2 = " << f2.getInfo() << std::endl;
        std::cout << "f3 = " << f3.getInfo() << std::endl;
        std::cout << "f4 = " << f4.getInfo() << std::endl;
        std::cout << "f5 = " << f5.getInfo() << std::endl;
        std::cout << "f6 = " << f6.getInfo() << std::endl << std::endl;

        std::cout << "2. АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ:\n";
        std::cout << "f3 + f4 = " << (f3 + f4).getInfo() << std::endl;
        std::cout << "f3 - f4 = " << (f3 - f4).getInfo() << std::endl;
        std::cout << "f3 * f4 = " << (f3 * f4).getInfo() << std::endl;
        std::cout << "f3 / f4 = " << (f3 / f4).getInfo() << std::endl << std::endl;

        std::cout << "3. ОПЕРАЦИИ С ЧИСЛАМИ (дробь + число):\n";
        std::cout << "f3 + 2 = " << (f3 + 2).getInfo() << std::endl;
        std::cout << "f3 - 0.5 = " << (f3 - 0.5).getInfo() << std::endl;
        std::cout << "f3 * 3 = " << (f3 * 3).getInfo() << std::endl;
        std::cout << "f3 / 2 = " << (f3 / 2).getInfo() << std::endl << std::endl;

        std::cout << "4. ДРУЖЕСТВЕННЫЕ ОПЕРАТОРЫ (число + дробь):\n";
        std::cout << "2 + f3 = " << (2 + f3).getInfo() << std::endl;
        std::cout << "1.5 - f3 = " << (1.5 - f3).getInfo() << std::endl;
        std::cout << "3 * f3 = " << (3 * f3).getInfo() << std::endl;
        std::cout << "2 / f3 = " << (2 / f3).getInfo() << std::endl << std::endl;

        std::cout << "5. ОПЕРАЦИИ СРАВНЕНИЯ:\n";
        std::cout << "f3 == 0.75: " << (f3 == 0.75) << std::endl;
        std::cout << "f3 != 0.75: " << (f3 != 0.75) << std::endl;
        std::cout << "f3 < 1: " << (f3 < 1) << std::endl;
        std::cout << "f3 > 0.5: " << (f3 > 0.5) << std::endl;
        std::cout << "0.5 == f3: " << (0.5 == f3) << std::endl;
        std::cout << "1 > f3: " << (1 > f3) << std::endl << std::endl;

        std::cout << "6. СОСТАВНЫЕ ОПЕРАТОРЫ:\n";
        Fraction a(1, 2);
        std::cout << "a = " << a.getInfo() << std::endl;
        a += 0.25;
        std::cout << "a += 0.25: " << a.getInfo() << std::endl;
        a *= 2;
        std::cout << "a *= 2: " << a.getInfo() << std::endl;
        a /= 3;
        std::cout << "a /= 3: " << a.getInfo() << std::endl << std::endl;

        std::cout << "7. ИНКРЕМЕНТ/ДЕКРЕМЕНТ:\n";
        Fraction b(2, 3);
        std::cout << "b = " << b.getInfo() << std::endl;
        std::cout << "++b = " << (++b).getInfo() << std::endl;
        std::cout << "b++ = " << (b++).getInfo() << std::endl;
        std::cout << "После b++: " << b.getInfo() << std::endl;
        std::cout << "--b = " << (--b).getInfo() << std::endl;
        std::cout << "b-- = " << (b--).getInfo() << std::endl;
        std::cout << "После b--: " << b.getInfo() << std::endl << std::endl;

        std::cout << "8. УНАРНЫЕ ОПЕРАТОРЫ:\n";
        std::cout << "f3 = " << f3.getInfo() << std::endl;
        std::cout << "-f3 = " << (-f3).getInfo() << std::endl;
        std::cout << "!f3 = " << (!f3).getInfo() << std::endl;
        std::cout << "!!f3 = " << (!!f3).getInfo() << std::endl << std::endl;

        std::cout << "9. ПРИВЕДЕНИЕ ТИПОВ:\n";
        Fraction c1(7, 2);
        Fraction c2(-5, 2);
        std::cout << "c1 = " << c1.getInfo() << std::endl;
        std::cout << "c2 = " << c2.getInfo() << std::endl;
        std::cout << "double(c1) = " << static_cast<double>(c1) << std::endl;
        std::cout << "float(c1) = " << static_cast<float>(c1) << std::endl;
        std::cout << "int64_t(c1) = " << static_cast<int64_t>(c1) << std::endl;

        try {
            std::cout << "uint64_t(c1) = " << static_cast<uint64_t>(c1) << std::endl;
        }
        catch (const FractionException& e) {
            std::cout << "uint64_t(c1): " << e.what() << std::endl;
        }

        try {
            std::cout << "uint64_t(c2) = " << static_cast<uint64_t>(c2) << std::endl;
        }
        catch (const FractionException& e) {
            std::cout << "uint64_t(c2): " << e.what() << std::endl;
        }
        std::cout << std::endl;

        std::cout << "10. ПРОВЕРКА ИСКЛЮЧЕНИЙ:\n";

        try {
            Fraction zero(0, 1);
            Fraction result = f3 / zero;
            std::cout << "f3 / 0 = " << result.getInfo() << std::endl;
        }
        catch (const FractionException& e) {
            std::cout << "Деление на ноль: " << e.what() << std::endl;
        }

        try {
            Fraction zero(0, 1);
            Fraction result = !zero;
            std::cout << "!0 = " << result.getInfo() << std::endl;
        }
        catch (const FractionException& e) {
            std::cout << "Обратная к нулю: " << e.what() << std::endl;
        }

        std::cout << std::endl;

        std::cout << "12. ПРАКТИЧЕСКИЙ ПРИМЕР:\n";
        Fraction sum;
        for (int i = 1; i <= 10; i++) {
            sum += Fraction(1, static_cast<uint64_t>(i));
        }
        std::cout << "1/1 + 1/2 + ... + 1/10 = " << sum.getInfo() << std::endl;
        std::cout << "В виде double: " << static_cast<double>(sum) << std::endl;

    }
    catch (const FractionException& e) {
        std::cerr << "\nОшибка Fraction: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "\nНеизвестная ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\n=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО УСПЕШНО ===\n";

    return 0;
}