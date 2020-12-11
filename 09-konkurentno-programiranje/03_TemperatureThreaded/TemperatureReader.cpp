#include "TemperatureReader.h"
#include "ui_TemperatureReader.h"
#include "Room.h"
#include "CellThread.h"

#include <QMessageBox>
#include <QMutexLocker>

TemperatureReader::TemperatureReader(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::TemperatureReader)
    , _timer(this)
{
    _ui->setupUi(this);

    // Povezivanje signala i slot-metoda u okviru formulara
    QObject::connect(_ui->pbStartReading, &QPushButton::clicked,
                     this, &TemperatureReader::onPbStartReading);
}

TemperatureReader::~TemperatureReader()
{
    // Brisemo auto-generisanu klasu koja implementira formular
    delete _ui;
}

Room &TemperatureReader::getRoom()
{
    return *_room;
}

QMutex &TemperatureReader::getMutexForRoom()
{
    return _mutexForRoom;
}

void TemperatureReader::onPbStartReading()
{
    // Dohvatamo broj iz QLineEdit polja
    // i pokusavamo da ga parsiramo u celi broj
    const auto number_str = _ui->leNumOfRc->text();
    bool parsed;
    const auto rcNumber = number_str.toInt(&parsed);

    // Ako je korisnik uneo nesto sto nije broj ili je uneo nepozitivan broj,
    // onda mu treba prikazati poruku da ispravi unos
    if (!parsed || rcNumber <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Morate uneti ispravan pozitivan broj");
        msgBox.exec();
        return;
    }

    // Iskljucujemo sve kontrole za unos podataka
    _ui->groupBox->setDisabled(true);

    // Kreiramo objekat sobe na osnovu broja celija u redu/koloni
    // i pripremamo QTableWidget za prikazivanje
    _room = new Room(rcNumber, this);
    populateTableWidget();

    // Pravimo niti koje ce racunati vrednost jednog polja u matrici na osnovu susednih polja.
    startThreads();

    // Postavljamo tajmer koji ce pokrenuti niti na svaku 1.5 sekundu
    QObject::connect(&_timer, &QTimer::timeout,
                     this, &TemperatureReader::startThreads);
    _timer.start(1500);
}

void TemperatureReader::populateTableWidget()
{
    const auto rcNumber = _room->numberOfRowsAndColumns();

    _ui->twRoomMatrix->setRowCount(rcNumber);
    _ui->twRoomMatrix->setColumnCount(rcNumber);
    for (auto i = 0; i < rcNumber; ++i)
    {
        for (auto j = 0; j < rcNumber; ++j)
        {
            auto cellValue = _room->cellValue(i, j);
            // QTableWidgetItem-i se kreiraju bez roditelja,
            // ali kad se dodaju nekom QTableWidget-u, onda on preuzima vlasnistvo nad njima
            auto tableItem = new QTableWidgetItem(QString::number(cellValue));
            _ui->twRoomMatrix->setItem(i, j, tableItem);
        }
    }
}

void TemperatureReader::startThreads()
{
    // Ovde pristupamo objektu sobe za citanje broja kolona,
    // medjutim, moguce je da neka nit jos uvek radi,
    // pa imamo konkurentno citanje, te moramo sinhronizovati niti.
    QMutexLocker lock(&_mutexForRoom);

    for (auto i = 0; i < _room->numberOfRowsAndColumns(); ++i)
    {
        for (auto j = 0; j < _room->numberOfRowsAndColumns(); ++j)
        {
            auto thread = new CellThread(i, j, this);
            QObject::connect(thread, &CellThread::threadFinished,
                             this, &TemperatureReader::onThreadFinished);
            QObject::connect(thread, &CellThread::finished,
                             thread, &CellThread::deleteLater);
            thread->start();
        }
    }
}

void TemperatureReader::onThreadFinished(int i, int j)
{
    // I ovde imamo konkurentno citanje, te moramo sinhronizovati niti.
    QMutexLocker lock(&_mutexForRoom);

    // Azuriramo prikaz matrice u prikazu.
    // S obzirom da smo u metodu populateTableWidget() konstruisali tabelu i popunili je item-ima,
    // sada mozemo jednostavno da menjamo sadrzaj tih item-a.
    auto cellValue = _room->cellValue(i, j);
    _ui->twRoomMatrix->item(i, j)->setText(QString::number(cellValue));
}
