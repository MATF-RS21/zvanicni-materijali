#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "PiThread.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbStartCalculating, &QPushButton::clicked, this, &MainWindow::calculatePiValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculatePiValue()
{
    ui->pbStartCalculating->setEnabled(false);

    // Cistimo widget za naredni prikaz progresa
    ui->lwProgress->clear();

    // Kreiramo nit koja ce racunati vrednost broja Pi
    PiThread *thread = new PiThread(this);

    // Povezujemo odgovarajuce signale i slotove:
    // 1. Kada nit emituje da smo napravili progres,
    // treba da azuriramo progres u widgetu
    connect(thread, &PiThread::progressIsMade, this, &MainWindow::onProgressIsMade);
    // 2. Kada nit emituje da je zavrsila za izracunavanjem vrednosti,
    // treba da tu vrednost prikazemo
    connect(thread, &PiThread::piIsCalculated, this, &MainWindow::onPiIsCalculated);
    // 3. Kada je nit zavrsena,
    // potrebno ju je unistiti
    connect(thread, &PiThread::finished, thread, &PiThread::deleteLater);

    // Konacno, pokrecemo nit kako bi se izvrsila
    thread->start();
}

void MainWindow::onProgressIsMade(QString percentage)
{
    ui->lwProgress->addItem(percentage);
}

void MainWindow::onPiIsCalculated(double piValue)
{
    ui->lePi->setText(QString::number(piValue));
    ui->pbStartCalculating->setEnabled(true);
}
