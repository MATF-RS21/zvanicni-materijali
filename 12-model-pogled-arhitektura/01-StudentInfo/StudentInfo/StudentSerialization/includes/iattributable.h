#ifndef IATTRIBUTABLE_H
#define IATTRIBUTABLE_H

#include <QString>
#include <QVariant>

class IAttributable
{
public:
    virtual ~IAttributable() = default;

    virtual int numberOfAttributes() const = 0;
    virtual QString attributeName(int idx) const = 0;
    virtual QVariant attribute(int idx) const = 0;
    virtual void setAttribute(int idx, const QVariant & value) = 0;
};

#endif // IATTRIBUTABLE_H
