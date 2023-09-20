#ifndef TAJMER_H
#define TAJMER_H

#include <QThread>
#include <QString>
#include <QElapsedTimer>
#include <QTimer>
#include <QLabel>
#include "ui_partija.h"

class Tajmer : public QThread{
    Q_OBJECT

public:
    Tajmer(QObject *parent = nullptr);
    int saljiSekunde(int s);
    void setInterfejs(Ui::Partija*);
    void ispisiVreme();
    void resetujSek();
    void prekiniBrojanje();
    void dodajSekunde(int);

protected:
    void run() override;
    QElapsedTimer *m_sat;
    Ui::Partija *m_interfejs;
    int m_sek = 10;

signals:
    void tajmerIstekao();
};

#endif // TAJMER_H
