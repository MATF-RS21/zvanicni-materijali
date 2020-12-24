#include "../includes/courseitem.h"

CourseItem::CourseItem()
    : m_name("")
    , m_espb(0u)
{
}

int CourseItem::numberOfAttributes()
{
    return CourseItem::NUMBER_OF_ATTRIBUTES;
}

QString CourseItem::attributeName(int idx)
{
    // Dogovaramo se da indeks 0 odgovara imenu, a indeks 1 broju bodova.
    switch (idx) {
        case 0:
            return "Course name";
        case 1:
            return "ESPB";
        // Indeks je nevalidan - vrati praznu nisku
        default:
            return "";
    }
}

QVariant CourseItem::operator[](int idx) const
{
    // Dogovaramo se da indeks 0 odgovara imenu, a indeks 1 broju bodova.
    switch (idx) {
        case 0:
            return QVariant(m_name);
        case 1:
            return QVariant(m_espb);
        // Indeks je nevalidan - vrati "nevalidan" QVariant
        default:
            return QVariant();
    }
}

void CourseItem::setData(int idx, const QVariant &value)
{
    // Dogovaramo se da indeks 0 odgovara imenu, a indeks 1 broju bodova.
    switch (idx) {
        case 0:
            m_name = value.toString();
            break;
        case 1:
            bool parsed = false;
            auto parsedValue = value.toUInt(&parsed);
            if (parsed) {
                m_espb = parsedValue;
            }
            break;
        // Indeks je nevalidan - nema promene
    }
}

QVariant CourseItem::toVariant() const
{
    QVariantMap map;
    map.insert("name", m_name);
    map.insert("espb", m_espb);
    return map;
}

void CourseItem::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    m_name = map.value("name").toString();
    m_espb = map.value("espb").toUInt();
}

