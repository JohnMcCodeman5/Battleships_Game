#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject* parent = nullptr);
    ~Server();

public slots:
    void konekcija();
    void komunikacija();
    void klijentIzasao();

private:
    QTcpServer* m_server;
    QTcpSocket* m_klijent1;
    QTcpSocket* m_klijent2;
};

#endif // SERVER_H
