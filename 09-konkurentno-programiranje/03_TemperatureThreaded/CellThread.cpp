#include "CellThread.h"
#include "TemperatureReader.h"
#include "Room.h"

#include <QMutexLocker>

CellThread::CellThread(const int i, const int j, QObject *parent)
    : QThread(parent)
    , _i(i)
    , _j(j)
{
}

void CellThread::run()
{
    // Znamo da ce nit kao roditelja dobiti pokazivac na prozor,
    // pa mozemo izvrsiti dinamicko kastovanje u prozor,
    // kako bismo mogli da dohvatimo objekat sobe i muteks radi sinhronizacije
    TemperatureReader *window = qobject_cast<TemperatureReader *>(parent());

    // Zakljucavamo muteks kako bismo sprecili da druge niti konkurentno pristupaju podacima
    QMutexLocker lock(&window->getMutexForRoom());

    // Sada mozemo bezbedno da pristupimo objektu sobe za citanje i menjanje.
    // Ponovo, obratite paznju da se cuva referenca da bi se izbeglo kopiranje.
    auto &room = window->getRoom();

    // Racunamo razliku u temperaturi izmedju tekuce celije i okolnih celija
    auto tempDiff = 0.0;

    // Dodajemo razliku u temperaturi od okolnih celija (konkurentno citanje)
    tempDiff += room.getTemperatureDiffFromCellAbove(_i, _j);
    tempDiff += room.getTemperatureDiffFromCellBelow(_i, _j);
    tempDiff += room.getTemperatureDiffFromCellLeft(_i, _j);
    tempDiff += room.getTemperatureDiffFromCellRight(_i, _j);

    // Azuriramo temperaturu (konkurentno pisanje)
    room.updateNewTemperatureForCell(_i, _j, tempDiff);

    // Emitujemo da smo zavrsili posao
    emit threadFinished(_i, _j);
}
