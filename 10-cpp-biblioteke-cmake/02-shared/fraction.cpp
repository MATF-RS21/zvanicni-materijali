#include "fraction.hpp"

namespace matf
{
    fraction::fraction(int numerator, unsigned int denominator)
        : m_numerator(numerator), m_denominator(denominator)
    {
        reduce_fraction();
    }

    void fraction::reduce_fraction()
    {
    }

    int fraction::numerator() const
    {
        return m_numerator;
    }

    unsigned int fraction::denominator() const
    {
        return m_denominator;
    }

    void fraction::set_numerator(int numerator)
    {
        m_numerator = numerator;
    }

    void fraction::set_denominator(unsigned int denominator)
    {
        m_denominator = denominator;
    }

    fraction fraction::operator+(const fraction &other) const
    {
        return fraction(
            m_denominator * other.m_numerator + other.m_denominator * m_numerator,
            m_denominator * other.m_denominator);
    }

    fraction fraction::operator-(const fraction &other) const
    {
        return fraction(
            other.m_denominator * m_numerator - m_denominator * other.m_numerator,
            m_denominator * other.m_denominator);
    }

    fraction fraction::operator++(int)
    {
        fraction tmp(m_numerator, m_denominator);
        ++(*this);
        return tmp;
    }

    fraction &fraction::operator++()
    {
        m_numerator += m_denominator;
        return (*this);
    }

    fraction fraction::operator-() const
    {
        return fraction();
    }

    fraction::operator double() const
    {
        return m_numerator / static_cast<double>(m_denominator);
    }

    bool fraction::operator==(const fraction &other) const
    {
        return m_numerator * other.m_denominator == other.m_numerator * m_denominator;
    }

    bool fraction::operator!=(const fraction &other) const
    {
        return !(*this == other);
    }

} // namespace matf

std::ostream &operator<<(std::ostream &out, const matf::fraction &value)
{
    return out << value.numerator() << "/" << value.denominator();
}

std::istream &operator>>(std::istream &in, matf::fraction &value)
{
    char c;
    int numerator;
    unsigned denominator;
    in >> numerator >> c >> denominator;
    value.set_numerator(numerator);
    value.set_denominator(denominator);
    return in;
}