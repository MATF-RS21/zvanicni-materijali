#ifndef COURSEITEM_H
#define COURSEITEM_H

#include <QVariant>

#include "StudentSerialization_global.h"
#include "serializable.h"
#include "iattributable.h"

class STUDENTSERIALIZATION_EXPORT CourseItem : public Serializable, public IAttributable
{
private:
    static const int NUMBER_OF_ATTRIBUTES = 2;
    enum Attributes
    {
        Name,
        Espb,
        NumberOfAttributes
    };

public:
    CourseItem();

    // Metodi za (de)serijalizaciju
    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    int numberOfAttributes() const override;
    QString attributeName(int idx) const override;
    QVariant attribute(int idx) const override;
    void setAttribute(int idx, const QVariant & value) override;

private:
    QString m_name;
    unsigned m_espb;
};

#endif // COURSEITEM_H
