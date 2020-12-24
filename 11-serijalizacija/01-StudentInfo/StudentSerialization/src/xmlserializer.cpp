#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "../includes/xmlserializer.h"

XMLSerializer::XMLSerializer()
{

}

void XMLSerializer::save(const Serializable &serializable, const QString &filepath, const QString &rootName)
{
    QFile file(filepath);
    file.open(QFile::WriteOnly);
    // Pravimo izlazni XML tok za datoteku i podesavamo automatsko formatiranje (neminimizovan zapis).
    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    // Pravimo zaglavlje dokumenta
    stream.writeStartDocument();
    // Potrebno je da deserijalizujemo QVariant u XML. Medjutim, ovo mozemo uraditi na vise nacina,
    // stoga je potrebno da sami napisemo funkciju koja ce "konvertovati" QVariant u XML.
    writeVariantToStream(rootName, serializable.toVariant(), stream);
    // Pravimo podnozje dokumenta
    stream.writeEndDocument();
    file.close();
}

void XMLSerializer::load(Serializable &serializable, const QString &filepath)
{
    // Primetimo da je arhitektura ista kao za upisivanje podataka.
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    QXmlStreamReader stream(&file);
    stream.readNextStartElement();
    serializable.fromVariant(readVariantFromStream(stream));
    file.close();
}

void XMLSerializer::writeVariantToStream(const QString &nodeName, const QVariant &variant, QXmlStreamWriter &stream)
{
    // Otvaramo XML etiketu, na primer, <student>
    stream.writeStartElement(nodeName);

    // Zapisujemo tip QVariant objekta, kako bismo lakse deserijalizovali kasnije, u XML atribut.
    stream.writeAttribute("type", variant.typeName());

    // Nije svejedno da li QVariant predstavlja listu, mapu ili skalarni podatak.
    // Zbog toga imamo pomocne metode koji ce biti pozvani u zavisnosti od tipa QVariant-a.
    switch (variant.type()) {
    case QVariant::Type::List:
        writeVariantListToStream(variant, stream);
        break;
    case QVariant::Type::Map:
        writeVariantMapToStream(variant, stream);
        break;
    default:
        writeVariantValueToStream(variant, stream);
        break;
    }

    // Zatvaramo XML etiketu, na primer, </student>
    stream.writeEndElement();
}

// Serijalizacija skalarnog podatka, na primer:
// <espb type="unsigned">5</espb>
void XMLSerializer::writeVariantValueToStream(const QVariant &variant, QXmlStreamWriter &stream)
{
    stream.writeCharacters(variant.toString());
}

void XMLSerializer::writeVariantListToStream(const QVariant &variant, QXmlStreamWriter &stream)
{
    const auto variantList = variant.toList();

    for(const auto& element : variantList) {
        // Rekurzivno pozivamo glavni metod za "konverziju" QVariant-a u XML,
        // zato sto lista ne mora da sadrzi samo skalarne vrednosti,
        // vec moze imati i liste i mape.
        // Takodje, s obzirom da prolazimo kroz listu, nisu nam poznata imena,
        // pa koristimo "genericko" ime <item>.
        writeVariantToStream("item", element, stream);
    }
}

void XMLSerializer::writeVariantMapToStream(const QVariant &variant, QXmlStreamWriter &stream)
{
    const auto variantMap = variant.toMap();
    QMapIterator<QString, QVariant> i(variantMap);

    while (i.hasNext()) {
        i.next();
        // S obzirom da je ovoga puta mapa u pitanju, vazno nam je da koristimo ispravno ime,
        // te zbog toga kao prvi argument saljemo kljuc kao ime.
        writeVariantToStream(i.key(), i.value(), stream);
    }
}

QVariant XMLSerializer::readVariantFromStream(QXmlStreamReader &stream)
{
    QXmlStreamAttributes attributes = stream.attributes();
    QString typeString = attributes.value("type").toString();
    QVariant variant;

    switch (QVariant::nameToType(typeString.toStdString().c_str())) {
    case QVariant::Type::List:
        variant = readVariantListFromStream(stream);
        break;
    case QVariant::Type::Map:
        variant = readVariantMapFromStream(stream);
        break;
    default:
        variant = readVariantValueFromStream(stream);
        break;
    }

    return variant;
}

QVariant XMLSerializer::readVariantValueFromStream(QXmlStreamReader &stream)
{
    // Citamo atribut "type" XML elementa
    QXmlStreamAttributes attributes = stream.attributes();
    QString typeString = attributes.value("type").toString();
    // Citamo sadrzaj XML elementa
    QString dataString = stream.readElementText();
    // Kreiramo QVariant na osnovu teksta koji predstavlja sadrzaj
    QVariant variant(dataString);
    // Vrsimo konverziju u odgovarajuci tip na osnovu vrednosti atributa "type"
    variant.convert(QVariant::nameToType(typeString.toStdString().c_str()));
    return variant;
}

QVariant XMLSerializer::readVariantListFromStream(QXmlStreamReader &stream)
{
    QVariantList list;
    // Citamo sve dok ne naidjemo na sledecu otvorenu etiketu.
    // Kada naidjemo na otvorenu etiketu, metod ce vratiti true,
    // sto znaci da smo spremni da obradjujemo taj novi element.
    while(stream.readNextStartElement()) {
        list.append(readVariantFromStream(stream));
    }
    return list;
}

QVariant XMLSerializer::readVariantMapFromStream(QXmlStreamReader &stream)
{
    QVariantMap map;
    while(stream.readNextStartElement()) {
        // Unosimo u mapu par ciji je kljuc naziv XML elementa, a vrednost je deserijalizovana vrednost
        map.insert(stream.name().toString(), readVariantFromStream(stream));
    }
    return map;
}
