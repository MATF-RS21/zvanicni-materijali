#include "Room.h"

#include <QRandomGenerator>

Room::Room(int n, QObject *parent)
    : QObject(parent)
{
    for (auto i = 0; i < n; ++i)
    {
        QVector<double> row;
        for (auto j = 0; j < n; ++j)
        {
            // Generisemo nasumicnu temperaturu u intervalu [15, 30)
            const auto randomTemp = QRandomGenerator::global()->generateDouble() * 15 + 15;
            row.push_back(randomTemp);
        }
        _matrix.push_back(row);
    }
}

int Room::numberOfRowsAndColumns() const
{
    return _matrix.size();
}

double Room::cellValue(int i, int j) const
{
    return _matrix[i][j];
}

double Room::getTemperatureDiffFromCellAbove(int i, int j) const
{
    if (i <= 0)
    {
        return 0.0;
    }
    return TEMP_COEFFICIENT * (_matrix[i-1][j] - _matrix[i][j]);
}

double Room::getTemperatureDiffFromCellBelow(int i, int j) const
{
    if (i >= _matrix.size() - 1)
    {
        return 0.0;
    }
    return TEMP_COEFFICIENT * (_matrix[i+1][j] - _matrix[i][j]);
}

double Room::getTemperatureDiffFromCellLeft(int i, int j) const
{
    if (j <= 0)
    {
        return 0.0;
    }
    return TEMP_COEFFICIENT * (_matrix[i][j-1] - _matrix[i][j]);
}

double Room::getTemperatureDiffFromCellRight(int i, int j) const
{
    if (j >= _matrix.size() - 1)
    {
        return 0.0;
    }
    return TEMP_COEFFICIENT * (_matrix[i][j+1] - _matrix[i][j]);
}

void Room::updateNewTemperatureForCell(int i, int j, double tempDiff)
{
    _matrix[i][j] += tempDiff;
}
