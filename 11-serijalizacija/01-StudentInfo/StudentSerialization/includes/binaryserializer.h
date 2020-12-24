#ifndef BINARYSERIALIZER_H
#define BINARYSERIALIZER_H

#include "StudentSerialization_global.h"
#include "serializer.h"

class STUDENTSERIALIZATION_EXPORT BinarySerializer : public Serializer
{
public:
    BinarySerializer();

    void save(const Serializable &serializable, const QString &filepath, const QString &rootName = "") override;
    void load(Serializable &serializable, const QString &filepath) override;
};

#endif // BINARYSERIALIZER_H
