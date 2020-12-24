#include <QJsonDocument>
#include <QFile>

#include "../includes/jsonserializer.h"

JSONSerializer::JSONSerializer()
{

}

void JSONSerializer::save(const Serializable &serializable, const QString &filepath, const QString &rootName)
{
    // JSON serijalizator ne koristi parametar rootName
    Q_UNUSED(rootName);

    // Napomena: metod QJsonDocument::fromVariant() moze da prihvati jedan od naredna tri objekta: QVariantMap, QVariantList ili QStringList.
    // Zbog toga je potrebno da svi Serializable objekti vracaju neki od ta tri tipa kao povratnu vrednost metoda toVariant().
    QJsonDocument doc = QJsonDocument::fromVariant(serializable.toVariant());
    QFile file(filepath);
    file.open(QFile::WriteOnly);
    file.write(doc.toJson(QJsonDocument::JsonFormat::Indented)); // Neminimizovan zapis (moze i QJsonDocument::JsonFormat::Compact)
    file.close();
}

void JSONSerializer::load(Serializable &serializable, const QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    // Napomena: metod QJsonDocument::fromJson() moze da vrati jedan od naredna dva tipa objekta: QVariantMap ili QVariantList,
    // u zavisnosti od tipa dokumenta. S obzirom da mi koristimo samo mape, onda mozemo biti sigurni da ce sve raditi korektno.
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    serializable.fromVariant(doc.toVariant());
}
