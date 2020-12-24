#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QVariant>

#include "StudentSerialization_global.h"

// Pravimo apstraktnu baznu klasu koju ce implementirati sve klase
// za koje zelimo da omogucimo (de)serijalizaciju u neki format.
// Koristimo klasu QVariant kako bismo mogli da (de)serijalizujemo razne tipove.
// Same klase koje implementiraju ovaj interfejs ce opisivati na koji nacin se vrsi (de)serijalizacija.
class STUDENTSERIALIZATION_EXPORT Serializable
{
public:
    virtual ~Serializable() = default;
    // Metod toVariant() sluzi za opisivanje na koji nacin se vrsi serijalizacija.
    virtual QVariant toVariant() const = 0;
    // Metod toVariant() sluzi za opisivanje na koji nacin se vrsi deserijalizacija.
    virtual void fromVariant(const QVariant & variant) = 0;
};

#endif // SERIALIZABLE_H
