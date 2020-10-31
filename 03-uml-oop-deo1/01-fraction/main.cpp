#include <iostream>
#include "Fraction.hpp"

int main()
{
    // Poziv konstruktora objekta
    Fraction r; // Isto kao da smo pozvali: Fraction r(0, 1);

    // Operatori za citanje iz ulaznog toka i pisanje na izlazni tok
    std::cout << "Unesite razlomak u formatu n/d:" << std::endl;
    std::cin >> r;
    std::cout << "Unet je razlomak: " << r << std::endl;

    // Prefiksno i postfiksno inkrementiranje
    std::cout << "++r: " << ++r << std::endl;
    std::cout << "r++: " << r++ << std::endl;
    std::cout << "r: " << r << std::endl;

    // Implicitno kastovanje u double
    double d1 = r;
    std::cout << "implicitno (double)r = " << d1 << std::endl;

    // Eksplicitno C kastovanje u double
    double d2 = (double)r;
    std::cout << "eksplicitno (double)r = " << d2 << std::endl;

    // Preporuceno kastovanje u C++ svetu koristeci static_cast
    // https://stackoverflow.com/questions/103512/why-use-static-castintx-instead-of-intx
    double d3 = static_cast<double>(r);
    std::cout << "static_cast<double>(r) = " << d3 << std::endl;

    // Konstruisanje "privremenog" objekta, tj. objekta ciji zivotni vek istice nakon naredne linije
    std::cout << Fraction(-3, 2) << std::endl;

    // Kombinacija operatora
    auto result = -(Fraction(2, 5) - Fraction(7, 5));
    std::cout << "1/1 == " << result << std::endl;

    return 0;
}
