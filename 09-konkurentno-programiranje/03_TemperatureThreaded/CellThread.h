#ifndef CELLTHREAD_H
#define CELLTHREAD_H

#include <QThread>

class CellThread : public QThread
{
    Q_OBJECT

public:
    CellThread(const int i, const int j, QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void threadFinished(int i, int j);

private:
    int _i;
    int _j;
};

#endif // CELLTHREAD_H
