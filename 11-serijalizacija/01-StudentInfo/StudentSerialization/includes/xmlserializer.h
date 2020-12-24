#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <QXmlStreamWriter>

#include "StudentSerialization_global.h"
#include "serializer.h"

class STUDENTSERIALIZATION_EXPORT XMLSerializer : public Serializer
{
public:
    XMLSerializer();

    void save(const Serializable &serializable, const QString &filepath, const QString &rootName = "") override;
    void load(Serializable &serializable, const QString &filepath) override;

private:
    // Metod writeVariantToStream() se koristi za ispisivanje proizvoljnog QVariant objekta.
    // On zapravo kreira novi XML element i poziva odgovarajuce pomocne metode ispod.
    void writeVariantToStream(const QString& nodeName, const QVariant& variant, QXmlStreamWriter& stream);
    void writeVariantValueToStream(const QVariant& variant, QXmlStreamWriter& stream);
    void writeVariantListToStream(const QVariant& variantList, QXmlStreamWriter& stream);
    void writeVariantMapToStream(const QVariant& variantMap, QXmlStreamWriter& stream);

    // Metod readVariantFromStream() se koristi za ucitavanje proizvoljnog QVariant objekta.
    // On zapravo cita sledeci XML element i poziva odgovarajuce pomocne metode ispod.
    QVariant readVariantFromStream(QXmlStreamReader& stream);
    QVariant readVariantValueFromStream(QXmlStreamReader& stream);
    QVariant readVariantListFromStream(QXmlStreamReader& stream);
    QVariant readVariantMapFromStream(QXmlStreamReader& stream);
};

#endif // XMLSERIALIZER_H
