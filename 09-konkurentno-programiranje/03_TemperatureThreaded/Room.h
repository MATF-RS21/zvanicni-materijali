#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QVector>
#include <QString>

class Room : public QObject
{
    Q_OBJECT
public:
    explicit Room(int n, QObject *parent = nullptr);

    // Zabranjujemo kopiranje i pomeranje sobe
    Room(const Room &) = delete;
    Room& operator=(const Room &) = delete;
    Room(Room &&) = delete;
    Room& operator=(Room &&) = delete;

    int numberOfRowsAndColumns() const;
    double cellValue(int i, int j) const;

    double getTemperatureDiffFromCellAbove(int i, int j) const;
    double getTemperatureDiffFromCellBelow(int i, int j) const;
    double getTemperatureDiffFromCellLeft(int i, int j) const;
    double getTemperatureDiffFromCellRight(int i, int j) const;
    void updateNewTemperatureForCell(int i, int j, double tempDiff);

private:
    QVector<QVector<double>> _matrix;
    const double TEMP_COEFFICIENT = 0.1;
};

#endif // ROOM_H
