#ifndef STUDENT_H
#define STUDENT_H

#include <QVector>

#include "StudentSerialization_global.h"
#include "serializable.h"
#include "iattributable.h"

class CourseItem;

class STUDENTSERIALIZATION_EXPORT Student : public Serializable, public IAttributable
{
private:
    enum Attributes
    {
        Name,
        Surname,
        Index,
        PersonalNumber,
        Enrolled,
        NumberOfAttributes
    };

public:
    Student(const QString & name = "",
            const QString & surname = "",
            const QString & index = "",
            const QString & personalNumber = "",
            bool enrolled = false,
            const QVector<CourseItem*> courseItems = {});

    // Metodi za (de)serijalizaciju
    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    int numberOfAttributes() const override;
    QString attributeName(int idx) const override;
    QVariant attribute(int idx) const override;
    void setAttribute(int idx, const QVariant & value) override;

    QVector<CourseItem *> getCourseItems() const;

private:
    QString m_name;
    QString m_surname;
    QString m_index;
    QString m_personalNumber;
    bool m_enrolled;
    QVector<CourseItem*> m_courseItems;
};

#endif // STUDENT_H
