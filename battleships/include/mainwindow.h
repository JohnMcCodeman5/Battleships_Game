#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFile>
#include <QFileSystemWatcher>
#include <include/partija.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QString> nadjiLokalneAdrese();

private slots:
    void on_pushButtonNazad_3_clicked();

    void on_pushButtonRezultati_clicked();

    void on_pushButtonNazad_clicked();

    void on_pushButtonSingleplayer_clicked();

    void on_pushButtonMultiplayer_clicked();

    void on_pushButtonNazad_2_clicked();

    void on_pushButtonZapocniPartiju_clicked();

    void prikaziRezultat(QString);

    void on_pushButtonZapocni_clicked();

    void on_pushButtonPovezivanje_clicked();

signals:
    void promenjenFajl(QString);

private:
    Ui::MainWindow *ui;
    Partija *partija = nullptr;


};
#endif // MAINWINDOW_H
