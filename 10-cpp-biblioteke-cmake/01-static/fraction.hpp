#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

namespace matf
{
    class fraction
    {
    public:
        fraction(int numerator = 0, unsigned int denominator = 1);

        int numerator() const;
        unsigned int denominator() const;

        void set_numerator(int numerator);
        void set_denominator(unsigned int denominator);

        fraction operator+(const fraction &other) const;
        fraction operator-(const fraction &other) const;
        fraction operator++(int);
        fraction &operator++();
        fraction operator-() const;

        operator double() const;

        bool operator==(const fraction &other) const;
        bool operator!=(const fraction &other) const;

    private:
        int m_numerator;
        unsigned m_denominator;

        void reduce_fraction();
    };
} // namespace matf

std::ostream &operator<<(std::ostream &out, const matf::fraction &value);
std::istream &operator>>(std::istream &in, matf::fraction &value);

#endif
