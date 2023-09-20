#include "include/Klijent.h"
#include "include/Multiplayer.h"
#include <iostream>
#include <ostream>

Klijent::Klijent(QObject* parent)
    : QObject(parent)
{
    m_soket = new QTcpSocket(this);
}

bool Klijent::povezi(QString adresa) {
    connect(m_soket, &QTcpSocket::readyRead, this, &Klijent::komunikacija);
    connect(m_soket, &QTcpSocket::disconnected, this, &Klijent::disconnected);

    m_soket->connectToHost(QHostAddress(adresa), 12345);

    return m_soket->waitForConnected();
}

void Klijent::disconnected() {
    delete m_soket;
}

void Klijent::komunikacija() {

    QString poruka = m_soket->readAll();
    if(poruka == "Klijent1") {
        m_klijent1_ind = true;
        tvojPotez = true;
        Multiplayer::aktivnaPartija->postaviIndikator(m_klijent1_ind);
    }
    else if(poruka == "Klijent2") {
        m_klijent1_ind = false;
        tvojPotez = false;
        Multiplayer::aktivnaPartija->postaviIndikator(m_klijent1_ind);
    }
    else if(poruka == "Oba klijenta povezana!") {
        Multiplayer::obaPovezana = true;
    }
    else if(poruka == "Protivnik odustao") {
        Multiplayer::aktivnaPartija->postaviProtivnikOdustao(true);
        Multiplayer::aktivnaPartija->postaviIzasaoKlijent(true);
        emit posaljiPoruku(poruka.toStdString());
    }
    else if(poruka.length() > 10) {
        emit posaljiBrodove(poruka.toStdString());
    }
    else {
        auto koordinate = poruka.split(',');
        int x = koordinate[0].toInt();
        int y = koordinate[1].toInt();

        emit posaljiPoziciju(x, y);
    }
}

void Klijent::procitajPoziciju(int x, int y) {

    if(m_soket->state() == QAbstractSocket::ConnectedState) {

        std::string x_str = std::to_string(x);
        std::string y_str = std::to_string(y);
        QByteArray podaci = QByteArray::fromStdString(x_str + "," + y_str);

        m_soket->write(podaci);
        m_soket->waitForBytesWritten();
    }
    else {
        std::cout << "Greska!" << std::endl;
    }
}

void Klijent::procitajBrodove(std::string brodovi) {
    if(m_soket->state() == QAbstractSocket::ConnectedState) {

        QByteArray podaci = QByteArray::fromStdString(brodovi);

        m_soket->write(podaci);
        m_soket->waitForBytesWritten();
    }
    else {
        std::cout << "Greska!" << std::endl;
    }
}

void Klijent::procitajPoruku(std::string poruka) {
    if(m_soket->state() == QAbstractSocket::ConnectedState) {

        QByteArray podaci = QByteArray::fromStdString(poruka);

        m_soket->write(podaci);
        m_soket->waitForBytesWritten();
    }
    else {
        std::cout << "Greska!" << std::endl;
    }
}

Klijent::~Klijent() {
    ;
}
