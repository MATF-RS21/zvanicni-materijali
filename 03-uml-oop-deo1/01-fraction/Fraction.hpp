#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

class Fraction
{
public:
    Fraction(int numerator = 0, unsigned int denominator = 1);

    // Metodi koji omogucavaju da citamo privatne podatke.
    // Kljucna rec `const` sa desne strane oznacava da 
    // metodi ne menjaju "unutrasnje stanje" objekta (atribute klase).
    int numerator() const;
    unsigned int denominator() const;

    // Binarni operatori za sabiranje i oduzimanje razlomaka `a` i `b` gde je:
    // - `a` -> *this
    // - `b` -> other
    Fraction operator+(const Fraction &other) const;
    Fraction operator-(const Fraction &other) const;

    // Prefiksno inkrementiranje.
    Fraction &operator++();
    // Postfiksno inkremetiranje.
    Fraction operator++(int);

    // Unarni operator -
    Fraction operator-() const;

    // Operator za konverziju u double.
    operator double() const;

    // Operatori za jednakost i nejednakost.
    bool operator==(const Fraction &other) const;
    bool operator!=(const Fraction &other) const;

    // ------------------------------------------------------------------------
    // DOMACI:
    // ------------------------------------------------------------------------
    // - Mnozenje razlomaka
    // - Deljenje razlomaka
    // - Operatori >, <
    // - Prefiksni i postfiksni operatori --
    // - Operatori >=, <=
    // - Mnozenje i deljenje skalarom
    // ------------------------------------------------------------------------

private:
    // Vrsi skracivanje razlomaka.
    void reduce_fraction();

    // Metodi koji omogucavaju da se promene vrednosti za brojilac i imenilac.
    // Primetimo da su im nazivi i argumenti identicni kao metodi za dohvatanje ovih podataka,
    // ali tip povratne vrednosti i "konstantnost" se razlikuju.
    void numerator(int numerator);
    void denominator(unsigned int denominator);

private:
    int m_numerator;
    unsigned m_denominator;

    // Oznacavamo funkciju (odnosno operator >>) kao prijateljsku funkciju za nasu klasu. 
    // Time dozvoljavamo funkciji da pristupi privatnim clanovima za objekte koji su instanca ove klase. 
    // To omogucava da direktno pristupamo brojiocu i imeniocu (m_numerator, m_denominator) 
    // umesto da zovemo funkcije numerator() i denominator().
    friend std::istream &operator>>(std::istream &in, Fraction &value);
};

std::ostream &operator<<(std::ostream &out, const Fraction &value);
std::istream &operator>>(std::istream &in, Fraction &value);

#endif
