#ifndef KLIJENT_H
#define KLIJENT_H

#include <QObject>
#include <QTcpSocket>

class Klijent : public QObject {

    Q_OBJECT
public:
    Klijent(QObject* parent = nullptr);
    ~Klijent();
    bool tvojPotez;
    bool povezi(QString adresa);

signals:
    void posaljiPoziciju(int x, int y);
    void posaljiBrodove(std::string brodovi);
    void posaljiPoruku(std::string poruka);

public slots:
    void procitajPoziciju(int x, int y);
    void komunikacija();
    void procitajBrodove(std::string brodovi);
    void disconnected();
    void procitajPoruku(std::string poruka);

private:
    QTcpSocket* m_soket;
    bool m_klijent1_ind;

};

#endif // KLIJENT_H
