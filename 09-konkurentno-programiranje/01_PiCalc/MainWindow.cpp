#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QRandomGenerator>

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

        // Zelimo da azuriramo QListWidget u prozoru na prikazuje svaki 10. procenat progresa.
        // Medjutim, posto se to azuriranje vrsi tokom izvrsavanja metoda koji zivi u glavnoj niti,
        // GKI je zamrznut i izmene ce biti vidljive tek kada ovaj metod zavrsi sa izvrsavanjem.
        if (count % iterUpdate == 10)
        {
            ui->lwProgress->addItem(QString::number(count / iterUpdate * 10u) + "%");
        }
    }

    auto pi = 4.0 * hits / count;

    ui->lePi->setText(QString::number(pi));
    ui->pbStartCalculating->setEnabled(true);
}

