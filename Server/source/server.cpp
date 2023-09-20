#include "include/server.h"

Server::Server(QObject *parent)
    : QObject(parent)
{
    m_server = new QTcpServer(this);
    m_klijent1 = nullptr;
    m_klijent2 = nullptr;

    connect(m_server, &QTcpServer::newConnection, this, &Server::konekcija);

    m_server->listen(QHostAddress::AnyIPv4, 12345);
}

Server::~Server() {
    delete m_server;
}

void Server::konekcija() {

    QTcpSocket* soket = m_server->nextPendingConnection();
    //bool klijent1_ind = false;

    if(soket) {
        if(m_klijent1 == nullptr) {
            m_klijent1 = soket;
            //klijent1_ind = true;
            m_klijent1->write("Klijent1");

        }
        else {
            m_klijent2 = soket;
            m_klijent2->write("Klijent2");
            m_klijent1->write("Oba klijenta povezana!");
        }

        connect(soket, &QTcpSocket::readyRead, this, &Server::komunikacija);
        connect(soket, &QTcpSocket::disconnected, this, &Server::klijentIzasao);
    }

    soket->flush();
    soket->waitForBytesWritten();
}

void Server::komunikacija() {
    QTcpSocket* soketPosiljalac = dynamic_cast<QTcpSocket*>(sender());
    if(soketPosiljalac == m_klijent1 && m_klijent2 != nullptr)
        m_klijent2->write(soketPosiljalac->readAll());
    else
        m_klijent1->write(soketPosiljalac->readAll());
}

void Server::klijentIzasao() {
    m_klijent1 = nullptr;
    m_klijent2 = nullptr;
}
