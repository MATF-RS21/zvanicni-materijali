#include <QFile>
#include <QDataStream>

#include "../includes/binaryserializer.h"

BinarySerializer::BinarySerializer()
{

}

void BinarySerializer::save(const Serializable &serializable, const QString &filepath, const QString &rootName)
{
    Q_UNUSED(rootName);

    QFile file(filepath);
    file.open(QFile::WriteOnly);

    // Kreiramo binarni izlazni tok
    QDataStream dataStream(&file);
    // QDataStream vec podrzava binarni izvoz QVariant objekta
    dataStream << serializable.toVariant();

    file.close();
}

void BinarySerializer::load(Serializable &serializable, const QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);

    // Kreiramo binarni ulazni tok
    QDataStream dataStream(&file);
    QVariant variant;
    // QDataStream vec podrzava binarni uvoz u QVariant objekat
    dataStream >> variant;
    serializable.fromVariant(variant);

    file.close();
}
