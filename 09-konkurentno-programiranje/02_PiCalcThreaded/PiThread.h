#ifndef PITHREAD_H
#define PITHREAD_H

#include <QThread>
#include <QString>

class PiThread : public QThread
{
    Q_OBJECT
public:
    PiThread(QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void progressIsMade(QString percentage);
    void piIsCalculated(double piValue);
};

#endif // PITHREAD_H
