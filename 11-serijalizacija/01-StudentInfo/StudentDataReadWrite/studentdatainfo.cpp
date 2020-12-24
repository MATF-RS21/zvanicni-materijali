#include <iostream>
#include <string>

#include <QFile>
#include <QDir>

#include "studentdatainfo.h"

#include "includes/student.h"
#include "includes/courseitem.h"
#include "includes/xmlserializer.h"
#include "includes/jsonserializer.h"
#include "includes/binaryserializer.h"

StudentDataInfo::StudentDataInfo()
{
    // Inicijalizacija upravljaca podacima
    m_xmlSerializer = new XMLSerializer();
    m_jsonSerializer = new JSONSerializer();
    m_binarySerializer = new BinarySerializer();
}

StudentDataInfo::~StudentDataInfo()
{
	qDeleteAll(m_students);
	delete m_xmlSerializer;
	delete m_jsonSerializer;
	delete m_binarySerializer;
}

void StudentDataInfo::execute(QString command)
{
    std::cout << "\n";

    if (command == "list") {
        executeList();
    }
    else if (command == "new") {
        executeNew();
    }
    else if (command == "load") {
        std::cout << "Enter the data directory path: ";
        std::string dirName;
        std::cin.get();
        std::getline(std::cin, dirName);
        auto files = QDir(QString::fromStdString(dirName)).entryList();
        executeLoad(QString::fromStdString(dirName), files);
    }
    else if (command == "write") {
        std::cout << "Enter the data directory path: ";
        std::string directory;
        std::cin.get();
        std::getline(std::cin, directory);
        std::cout << "Enter the file type: ";
        std::string fileType;
        std::cin >> fileType;
        executeWrite(QString::fromStdString(directory), QString::fromStdString(fileType));
    }
}

void StudentDataInfo::executeList() const
{
    if (m_students.empty()) {
        return;
    }

    std::cout << std::string(80, '=') << "\n";
    for (const auto & student : m_students) {
        const auto studData = student->toVariant().toMap();
        for (const auto & key : studData.keys()) {
            const auto value = studData[key];
            switch (value.userType()) {
                case QVariant::String:
                    std::cout << "\t" << key.toStdString() << " = " << value.toString().toStdString() << "\n";
                    break;
                case QVariant::Bool:
                    std::cout << "\t" << key.toStdString() << " = " << value.toBool() << "\n";
                    break;
                default:
                    std::cout << "\t" << key.toStdString() << " has the type " << QVariant::typeToName(value.userType()) << "\n";
            }
        }
        std::cout << std::string(80, '=') << "\n";
    }
}

void StudentDataInfo::executeNew()
{
    // TODO: Implementirati za domaci.
    // Metod treba da trazi od korisnika da unese podatke za novog studenta
    // i da na osnovu njih kreira novog studenta i zapamti ga u QVector studenata.
}

void StudentDataInfo::executeLoad(QString directory, QStringList files)
{
    for (const auto & fileName : files) {
        if (fileName == "." || fileName == "..") {
            continue;
        }
        auto student = new Student();

        auto fullFileName = directory + "/" + fileName;

        if (fileName.endsWith(".xml")) {
            m_xmlSerializer->load(*student, fullFileName);
        }
        else if (fileName.endsWith(".json")) {
            m_jsonSerializer->load(*student, fullFileName);
        }
        else if (fileName.endsWith(".bin")) {
            m_binarySerializer->load(*student, fullFileName);
        }
        else {
            delete student;
            throw "Unknown file type: " + fileName + "\nEnding program...\n";
        }
        m_students.push_back(student);
    }
}

void StudentDataInfo::executeWrite(QString directory, QString fileType) const
{
    for (auto i = 0; i < m_students.size(); ++i) {
        const auto student = m_students[i];
        const auto fileName = directory + "/" + QString::number(i+1) + "." + fileType;
        if (fileName.endsWith(".xml")) {
            m_xmlSerializer->save(*student, fileName, "student");
        }
        else if (fileName.endsWith(".json")) {
            m_jsonSerializer->save(*student, fileName);
        }
        else if (fileName.endsWith(".bin")) {
            m_binarySerializer->save(*student, fileName);
        }
        else {
            delete student;
            throw "Unknown file type: " + fileName + "\nEnding program...\n";
        }
    }
}
