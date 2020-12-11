#ifndef TEMPERATUREREADER_H
#define TEMPERATUREREADER_H

#include <QWidget>
#include <QMutex>
#include <QTimer>

class Room;

QT_BEGIN_NAMESPACE
namespace Ui { class TemperatureReader; }
QT_END_NAMESPACE

class TemperatureReader : public QWidget
{
    Q_OBJECT

public:
    TemperatureReader(QWidget *parent = nullptr);
    ~TemperatureReader();

    // Ovde je neophodno da vracamo reference kako ne bi doslo do kopiranja u nitima!!!
    // Obratite paznju da suvisna kopiranja ovog tipa na ispitu nose negativne poene.
    Room &getRoom();
    QMutex &getMutexForRoom();

public slots:
    void onPbStartReading();
    void onThreadFinished(int i, int j);

private slots:
    void startThreads();

private:
    void populateTableWidget();

    Ui::TemperatureReader *_ui;

    Room *_room; // Pokazivac, zato sto ce se dinamicki alocirati
    QMutex _mutexForRoom;
    QTimer _timer;
};
#endif // TEMPERATUREREADER_H
