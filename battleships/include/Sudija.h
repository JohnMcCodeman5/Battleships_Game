#ifndef SUDIJA_H
#define SUDIJA_H


#include <QWidget>
#include <QMap>
#include <QString>

class Sudija{

public:
    Sudija() = default;

    void DodajDobitnePoene(int);
    void kazniIgraca(int);
    void resetujKombo(int);

    QMap<QString, int> DohvatiRezultate();
    void upisiRezultat(QString);

private:
    int m_poeni_1;
    int m_poeni_2;
    unsigned m_kombo_1;
    unsigned m_kombo_2;
    QMap<QString, int> m_rezultati;

};

#endif // SUDIJA_H
