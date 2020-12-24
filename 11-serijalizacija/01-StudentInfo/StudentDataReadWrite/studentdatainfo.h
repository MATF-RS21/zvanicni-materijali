#ifndef STUDENTDATAINFO_H
#define STUDENTDATAINFO_H

#include <QString>
#include <QVector>
#include <QStringList>

class Student;
class Serializer;

class StudentDataInfo
{
public:
    StudentDataInfo();
    ~StudentDataInfo();

    void execute(QString command);

private:
    void executeList() const;
    void executeNew();
    void executeLoad(QString directory, QStringList files);
    void executeWrite(QString directory, QString fileType) const;

    // Podaci
    QVector<Student *> m_students;
    // Klase za ucitavanje i skladistenje podataka
    Serializer *m_xmlSerializer;
    Serializer *m_jsonSerializer;
    Serializer *m_binarySerializer;
};

#endif // STUDENTDATAINFO_H
