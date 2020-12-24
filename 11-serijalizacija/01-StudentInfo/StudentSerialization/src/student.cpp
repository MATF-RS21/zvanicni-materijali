#include <QVariantMap>
#include <QVariantList>

#include "../includes/student.h"
#include "../includes/courseitem.h"

Student::Student(const QString &name, const QString &surname, const QString &index, const QString &personalNumber, bool enrolled, const QVector<CourseItem *> courseItems)
    : m_name(name)
    , m_surname(surname)
    , m_index(index)
    , m_personalNumber(personalNumber)
    , m_enrolled(enrolled)
    , m_courseItems(courseItems)
{

}

Student::~Student()
{
    qDeleteAll(m_courseItems);
}

QString Student::getName() const
{
    return m_name;
}

QString Student::getSurname() const
{
    return m_surname;
}

QString Student::getIndex() const
{
    return m_index;
}

QString Student::getPersonalNumber() const
{
    return m_personalNumber;
}

bool Student::getEnrolled() const
{
    return m_enrolled;
}

QVector<CourseItem*> & Student::getCourseItems()
{
    return m_courseItems;
}

void Student::setAttribute(Student::Attributes attr, QVariant value)
{
    switch (attr)
    {
    case Student::Attributes::Name:
        m_name = value.toString();
        break;
    case Student::Attributes::Surname:
        m_surname = value.toString();
        break;
    case Student::Attributes::Index:
        m_index = value.toString();
        break;
    case Student::Attributes::PersonalNumber:
        m_personalNumber = value.toString();
        break;
    case Student::Attributes::Enrolled:
        m_enrolled = value.toBool();
        break;
    }
}

QVariant Student::toVariant() const
{
    QVariantMap map;
    map.insert("name", m_name);
    map.insert("surname", m_surname);
    map.insert("index", m_index);
    map.insert("pno", m_personalNumber);
    map.insert("enrolled", m_enrolled);

    if (m_enrolled) {
        QVariantList courseItems;
        for (const auto & course : m_courseItems) {
            courseItems.append(course->toVariant());
        }
        map.insert("courseItems", courseItems);
    }

    return map;
}

void Student::fromVariant(const QVariant &variant)
{
    const auto map = variant.toMap();
    m_name = map.value("name").toString();
    m_surname = map.value("surname").toString();
    m_index = map.value("index").toString();
    m_personalNumber = map.value("pno").toString();
    m_enrolled = map.value("enrolled").toBool();

    if (m_enrolled) {
        // Ne zaboravimo da se oslobodimo stare memorije!!!
        qDeleteAll(m_courseItems);
        m_courseItems.clear();

        const auto courseItems = map.value("courseItems").toList();
        for(const auto& course : courseItems) {
            auto courseItem = new CourseItem();
            courseItem->fromVariant(course);
            m_courseItems.push_back(courseItem);
        }
    }
}
