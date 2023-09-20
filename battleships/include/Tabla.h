#ifndef TABLA_HPP
#define TABLA_HPP

#include <QVector>
#include "Brod.h"
#include <QPair>
#include <QSet>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <algorithm>

#define KVADRAT 44

enum Status {
    NEUTRALNO = 0,
    PROMASEN = 1,
    POGODJEN = 2,
    DEO_BRODA = 3,
    MINA = 4,
    POGODJENA_MINA = 5
};

class Tabla{

public:
    Tabla(int n = 10);
    ~Tabla();
    void inicijalizujTablu();
    Status statusPozicije(QPair<int, int>);
    void setStatusPozicije(QPair<int, int>, Status status);
    void postaviRandomBrodove(bool m);
    QPair<int, int> nadjiKrajBroda(QPair<int, int> pocetak, int rotacija, int duzina);
    bool dozvoljenoMestoZaBrod(QPair<int, int> pocetak, QPair<int, int> kraj);
    void oznaciPostavljenBrod(QPair<int, int> pocetak, QPair<int, int> kraj);
    QVector<Brod*> getBrodovi();
    QVector< QVector<Status> > getSatusPozicija();
    static bool korektnoPolje(int x, int y);
    int getDimenzijaTable();
    bool sekuSe(QRectF p1, QRectF p2, bool, bool);
    void dodajBrod(Brod*);
    float ccw(QPair<float,float>,QPair<float,float>,QPair<float,float>);
    Brod* getBrod(int);
    QPair<int,int> proveriKolizije(bool);
    void obrisiBrodove();

private:
    QVector<Brod*> m_brodovi;
    QVector< QVector<Status> > m_statusPozicija;
    int m_dimenzijaTable;

};

#endif // TABLA_HPP
