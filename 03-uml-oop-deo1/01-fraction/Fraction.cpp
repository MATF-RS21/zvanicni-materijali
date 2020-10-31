#include "Fraction.hpp"

Fraction::Fraction(int numerator, unsigned int denominator)
    : m_numerator(numerator), m_denominator(denominator)
{
    reduce_fraction();
}

void Fraction::reduce_fraction()
{
    // TODO: Implementirati skracivanje razlomaka za domaci
}

int Fraction::numerator() const
{
    return m_numerator;
}

unsigned int Fraction::denominator() const
{
    return m_denominator;
}

void Fraction::numerator(int numerator)
{
    m_numerator = numerator;
}

void Fraction::denominator(unsigned int denominator)
{
    m_denominator = denominator;
}

Fraction Fraction::operator+(const Fraction &other) const
{
    return Fraction(
        denominator() * other.numerator() + other.denominator() * numerator(),
        denominator() * other.denominator());
}

Fraction Fraction::operator-(const Fraction &other) const
{
    return Fraction(
        other.denominator() * numerator() - denominator() * other.numerator(),
        denominator() * other.denominator());
}

// Prefiksno inkrementiranje.
Fraction &Fraction::operator++()
{
    auto newNumerator = numerator() + denominator();
    numerator(newNumerator);
    return (*this);
}

// Postfiksno inkrementiranje.
Fraction Fraction::operator++(int)
{
    // Pamtimo tekucu vrednost razlomka koju cemo vratiti
    Fraction tmp(numerator(), denominator());

    // Inkrementiramo trenutni objekat koristeci vec definisani
    // prefiksni operator inkrementacije
    ++(*this);

    // Vracamo originalnu vrednost
    return tmp;
}

// Unarni operator -
Fraction Fraction::operator-() const
{
    return Fraction(-numerator(), denominator());
}

// Operator za konverziju u double.
Fraction::operator double() const
{
    return numerator() / static_cast<double>(denominator());
}

// Operatori za jednakost i nejednakost.
bool Fraction::operator==(const Fraction &other) const
{
    return numerator() * other.denominator() == other.numerator() * denominator();
}

bool Fraction::operator!=(const Fraction &other) const
{
    // Vec smo definisali operator jednakosti,
    // pa ce ovaj operator vratiti suprotno od onoga sto kaze operator jednakosti
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &out, const Fraction &value)
{
    return out << value.numerator() << "/" << value.denominator();
}

std::istream &operator>>(std::istream &in, Fraction &value)
{
    // Koristimo `c` da progutamo separator izmedju brojeva koje je prosledio korisnik.
    char c;
    return in >> value.m_numerator >> c >> value.m_denominator;
}
