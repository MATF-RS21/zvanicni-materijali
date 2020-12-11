#include "PiThread.h"

#include <QRandomGenerator>

PiThread::PiThread(QObject *parent)
    : QThread(parent)
{
}

void PiThread::run()
{
    auto hits = 0u, count = 0u;
    const auto iterations = 100'000'000u;
    const auto iterUpdate = 10'000'000u;

    while (count < iterations)
    {
        const auto x = QRandomGenerator::global()->generateDouble() * 2 - 1;
        const auto y = QRandomGenerator::global()->generateDouble() * 2 - 1;

        if (x * x + y * y <= 1.0)
        {
            ++hits;
        }
        ++count;

        // Kada je ostvaren dovoljni progres, emitujemo dogadjaj glavnoj niti da radi azuriranje prikaza.
        // Primetimo da ce ovoga puta svaki procenat biti prikazan u ispravnom trenutku,
        // a ne samo na kraju, kao u prethodnom primeru.
        if (count % iterUpdate == 10)
        {
            const auto percentage = QString::number(count / iterUpdate * 10u) + "%";
            emit progressIsMade(percentage);
        }
    }

    auto pi = 4.0 * hits / count;

    // Kada smo zavrsili izracunavanje, emitujemo dobijenu vrednost
    emit piIsCalculated(pi);
}
