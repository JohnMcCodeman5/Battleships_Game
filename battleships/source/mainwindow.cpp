#include "../include/mainwindow.h"
#include "include/Multiplayer.h"
#include "include/Singleplayer.h"
#include "ui_mainwindow.h"
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Battleships");
    this->setFixedSize(this->width(), this->height());

    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButtonZapocni->setDisabled(true);

    QFileSystemWatcher watcher;
    watcher.addPath("../battleships/resources/rezultati.csv");

    connect(&watcher,SIGNAL(fileChanged(QString)),this,SLOT(prikaziRezultat(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonNazad_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::prikaziRezultat(QString ime_fajla)
{
    QFile fajl(ime_fajla);

    QString podaci;
    QStringList redovi;
    QStringList red;
    podaci.clear();
    redovi.clear();
    red.clear();

    if(fajl.open(QFile::ReadOnly))
    {
        podaci=fajl.readAll();
        redovi=podaci.split("\n");
        fajl.close();
    }

    for(int i=0;i<10 && i<redovi.size()-1;i++)
    {
        red=redovi.at(i).split(",");

        for(int j=0;j<red.size();j++)
        {
            ui->tableWidgetRezultati->setItem(i,j,new QTableWidgetItem(red[j].trimmed()));
        }
    }

    fajl.close();
}

void MainWindow::on_pushButtonRezultati_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    prikaziRezultat("../battleships/resources/rezultati.csv");
}

void MainWindow::on_pushButtonSingleplayer_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButtonMultiplayer_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButtonNazad_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButtonNazad_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}



void MainWindow::on_pushButtonZapocniPartiju_clicked(){
    bool tezinaPartije = false;
    tezinaPartije = ui->radioButton_2->isChecked();
    partija = new Singleplayer(this, tezinaPartije);
    partija->show();
    this->hide();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButtonZapocni_clicked()
{
    QString adresa = ui->lineEditInputPort->text();
    if(adresa != ""){
        partija = new Multiplayer(this, adresa);
        partija->show();
        this->hide();
        ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::on_pushButtonPovezivanje_clicked()
{
    auto adresa = ui->lineEditInputPort->text();
    auto deloviAdrese = adresa.split(".");

    auto lokalneAdrese = nadjiLokalneAdrese();
    auto ipV4adresa = lokalneAdrese[1];

    auto deloviIpV4adrese = ipV4adresa.split(".");

    if(deloviAdrese.length() != deloviIpV4adrese.length()) {
        ui->lineEditInputPort->setText("");
        return;
    }

    if(deloviAdrese[0] != deloviIpV4adrese[0]
            || deloviAdrese[1] != deloviIpV4adrese[1]
            || deloviAdrese[2] != deloviIpV4adrese[2]) {
        ui->lineEditInputPort->setText("");
        return;
    }

    ui->pushButtonZapocni->setDisabled(false);
}

QVector<QString> MainWindow::nadjiLokalneAdrese() {
    QVector<QString> lokalneAdrese;
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (int i = 0; i < interfaces.count(); i++)
    {
        QList<QNetworkAddressEntry> entries = interfaces.at(i).addressEntries();
        for (int j = 0; j < entries.count(); j++)
        {
            if (entries.at(j).ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                lokalneAdrese.append(entries.at(j).ip().toString());
            }
        }
    }

    return lokalneAdrese;
}
