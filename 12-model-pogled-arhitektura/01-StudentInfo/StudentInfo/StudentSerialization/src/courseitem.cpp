#include "../includes/courseitem.h"

CourseItem::CourseItem()
    : m_name("")
    , m_espb(0u)
{
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

int CourseItem::numberOfAttributes() const
{
    return Attributes::NumberOfAttributes;
}

QString CourseItem::attributeName(int idx) const
{
    switch (idx) {
    case Attributes::Name:
        return "Course name";
    case Attributes::Espb:
        return "ESPB";
    default:
        return {};
    }
}

QVariant CourseItem::attribute(int idx) const
{
    switch (idx) {
    case Attributes::Name:
        return QVariant(m_name);
    case Attributes::Espb:
        return QVariant(m_espb);
    default:
        return {};
    }
}

void CourseItem::setAttribute(int idx, const QVariant &value)
{
    switch (idx) {
    case Attributes::Name:
        m_name = value.toString();
        break;
    case Attributes::Espb: {
        bool parsed = false;
        auto parsedValue = value.toUInt(&parsed);
        if (parsed) {
            m_espb = parsedValue;
        }
    }
        break;
    default:
        break;
    }
}

