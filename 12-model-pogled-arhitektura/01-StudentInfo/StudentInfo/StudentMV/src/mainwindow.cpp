#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include "include/model.h"

#include "includes/student.h"
#include "includes/xmlserializer.h"

#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , m_studentModel(nullptr)
{
    // Podesavanje GKI
    ui->setupUi(this);

    // Inicijalizacija upravljaca podacima
    m_xmlSerializer = new XMLSerializer();
    connect(ui->pbLoadXML, &QPushButton::clicked, this, &MainWindow::loadXMLData);

    // Podesavanje stacked widget-a i dugmica za njegovo listanje
    ui->stackedWidget->setCurrentIndex(0);
    ui->pbPreviousView->setEnabled(false);
    connect(ui->pbPreviousView, &QPushButton::clicked, this, [&]()
    {
        const auto nextIndex = ui->stackedWidget->currentIndex() - 1;
        ui->stackedWidget->setCurrentIndex(nextIndex);
        if (nextIndex == 0)
        {
            ui->pbPreviousView->setEnabled(false);
        }
        ui->pbNextView->setEnabled(true);
    });
    connect(ui->pbNextView, &QPushButton::clicked, this, [&]()
    {
        const auto nextIndex = ui->stackedWidget->currentIndex() + 1;
        ui->stackedWidget->setCurrentIndex(nextIndex);
        if (nextIndex == ui->stackedWidget->count()-1)
        {
            ui->pbNextView->setEnabled(false);
        }
        ui->pbPreviousView->setEnabled(true);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_xmlSerializer;
    delete m_studentModel;
}

QStringList MainWindow::showFileDialog(const QString &filter, QFileDialog::FileMode fileMode)
{
    // Kreiramo dijalog za biranje datoteka sa sistema
    QFileDialog fileDialog(this);
    // Postavljamo da korisnik mora da odabere datoteku (ili vise njih - otud "s" ispod) koja postoji
    fileDialog.setFileMode(fileMode);
    // Postavljamo filter (samo neke datoteke)
    fileDialog.setNameFilter(filter);
    // Mozemo postaviti podrazumevani prikaz datoteka - detaljni ili samo listu
    fileDialog.setViewMode(QFileDialog::ViewMode::Detail);
    // Sve datoteke koje je korisnik izabrao se cuvaju u listi niski
    QStringList fileNames;
    if (fileDialog.exec()) {
        fileNames = fileDialog.selectedFiles();
    }

    return fileNames;
}

void MainWindow::connectViewAndModel(const QVector<Student *> &students)
{
    delete m_studentModel;
    m_studentModel = new TreeModel(students);
    QItemSelectionModel *selections = new QItemSelectionModel(m_studentModel);

    QSortFilterProxyModel *filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(m_studentModel);

    // Postavljamo model za prikaz u vidu liste
    QVector<QListView *> listViews{ui->lv0, ui->lv1, ui->lv2, ui->lv3, ui->lv4};
    int count = 0;
    for (auto listView : listViews)
    {
        listView->setModel(filterModel);
        listView->setSelectionModel(selections);
        listView->setViewMode(QListView::ListMode);
        listView->setFlow(QListView::TopToBottom);
        listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listView->setAlternatingRowColors(false);
        listView->viewport()->setAttribute(Qt::WA_StaticContents);
        listView->setAttribute(Qt::WA_MacShowFocusRect, false);
        listView->setModelColumn(count++);
    }

    // Postavljamo model za tabelarni prikaz
    ui->tableView->setModel(filterModel);
    ui->tableView->setSelectionModel(selections);
    ui->tableView->horizontalHeader()->setSectionsMovable(true);
    ui->tableView->verticalHeader()->setSectionsMovable(true);
    // Set StaticContents to enable minimal repaints on resizes.
    ui->tableView->viewport()->setAttribute(Qt::WA_StaticContents);

    // Postavljamo model za prikaz u obliku drveta
    ui->treeView->setModel(filterModel);
    ui->treeView->setSelectionModel(selections);
    ui->treeView->setUniformRowHeights(true);
    ui->treeView->header()->setStretchLastSection(false);
    ui->treeView->viewport()->setAttribute(Qt::WA_StaticContents);
    // Disable the focus rect to get minimal repaints when scrolling on Mac.
    ui->treeView->setAttribute(Qt::WA_MacShowFocusRect, false);
}

void MainWindow::loadXMLData()
{
    auto fileNames = showFileDialog("XML files (*.xml)", QFileDialog::FileMode::ExistingFiles);
    // Ako korisnik nije odabrao nijednu datoteku, ignorisemo akciju
    if (fileNames.empty()) {
        return;
    }

    loadData(m_xmlSerializer, fileNames);
}

void MainWindow::loadData(Serializer *serializer, QStringList &fileNames)
{
    QVector<Student *> students;
    for (const auto & fileName : fileNames) {
        Student *student = new Student();
        serializer->load(*student, fileName);
        students.push_back(student);
    }

    connectViewAndModel(students);
}
