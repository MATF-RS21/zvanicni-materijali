#ifndef STUDENT_H
#define STUDENT_H

#include <QVector>

#include "serializable.h"
#include "StudentSerialization_global.h"

class CourseItem;

class STUDENTSERIALIZATION_EXPORT Student : public Serializable
{
public:
    Student(const QString & name = "",
            const QString & surname = "",
            const QString & index = "",
            const QString & personalNumber = "",
            bool enrolled = false,
            const QVector<CourseItem*> courseItems = {});
    ~Student();

    enum Attributes
    {
        Name,
        Surname,
        Index,
        PersonalNumber,
        Enrolled,
        CourseItems
    };

    QString getName() const;
    QString getSurname() const;
    QString getIndex() const;
    QString getPersonalNumber() const;
    bool getEnrolled() const;
    QVector<CourseItem *> &getCourseItems();

    void setAttribute(Attributes attr, QVariant value);

    // Metodi za (de)serijalizaciju
    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

private:
    QString m_name;
    QString m_surname;
    QString m_index;
    QString m_personalNumber;
    bool m_enrolled;
    QVector<CourseItem*> m_courseItems;
};

#endif // STUDENT_H
