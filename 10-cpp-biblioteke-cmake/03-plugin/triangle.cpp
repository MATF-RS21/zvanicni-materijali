#include "polygon.hpp"
#include <cmath>

class triangle : public polygon
{
public:
    virtual double area() const
    {
        return side_length_ * side_length_ * sqrt(3) / 4;
    }
};

// Primetite da funkcije ispod imaju oznaku extern "C".
// Ovo je neophodno uraditi da bi se funkcija mogla dinamicki ucitati.
extern "C" polygon *create()
{
    return new triangle;
}

extern "C" void destroy(polygon *p)
{
    delete p;
}