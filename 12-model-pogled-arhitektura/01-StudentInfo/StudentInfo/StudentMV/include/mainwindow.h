#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Serializer;
class Student;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    QStringList showFileDialog(const QString &filter, QFileDialog::FileMode fileMode);
    void loadXMLData();

private:
    void connectViewAndModel(const QVector<Student *> &students);
    void loadData(Serializer *serializer, QStringList &fileNames);

private:
    Ui::MainWindow *ui;

    Serializer *m_xmlSerializer;
    QAbstractItemModel* m_studentModel;
};
#endif // MAINWINDOW_H
