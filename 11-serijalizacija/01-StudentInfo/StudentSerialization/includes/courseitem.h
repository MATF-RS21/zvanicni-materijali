#ifndef COURSEITEM_H
#define COURSEITEM_H

#include <QVariant>

#include "StudentSerialization_global.h"
#include "serializable.h"

class STUDENTSERIALIZATION_EXPORT CourseItem : public Serializable
{
public:
    CourseItem();

    // Svi kursevi imaju isti broj atributa i iste nazive atributa, pa ovi metodi mogu biti staticki.
    static int numberOfAttributes();
    static QString attributeName(int idx);

    // Naredni metod sluzi za dohvatanje odgovarajuceg atributa na osnovu datog indeksa.
    // Vraca QVariant kako bismo mogli da vracamo razlicite tipove podataka.
    QVariant operator[](int idx) const;

    // Definisemo metod za menjanje informacija o kursu.
    void setData(int idx, const QVariant & value);

    // Metodi za (de)serijalizaciju
    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

private:
    static const int NUMBER_OF_ATTRIBUTES = 2;

    QString m_name;
    unsigned m_espb;
};

#endif // COURSEITEM_H
