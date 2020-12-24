#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "StudentSerialization_global.h"
#include "serializable.h"

class STUDENTSERIALIZATION_EXPORT Serializer
{
public:
    virtual ~Serializer() = default;

    // Metod save() se koristi za trajno smestanje podataka na sistem datoteka (serijalizacija).
    // Primetimo da je objekat koji se serijalizuje konstantan - nema smisla da ovaj metod menja objekat.
    // Argument filepath odredjuje putanju ka datoteci u kojoj ce podatak biti serijalizovan,
    // dok argument rootName moze sluziti za potrebe nekih strategija serijalizacije, npr. za naziv XML etikete.
    virtual void save(const Serializable& serializable, const QString& filepath, const QString& rootName = "") = 0;
    // Metod load() se koristi za citanje podataka sa sistema datoteka i upisivanje tih podataka u objekat (deserijalizacija).
    // Primetimo da objekat koji se deserijalizuje nije konstantan - ovaj metod mora da menja objekat.
    // Argument filepath odredjuje putanju ka datoteci iz koje se citaju podaci za deserijalizaciju.
    virtual void load(Serializable& serializable, const QString& filepath) = 0;
};

#endif // SERIALIZER_H
