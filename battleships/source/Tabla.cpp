#include "./include/Tabla.h"

Tabla::Tabla(int n)
    : m_dimenzijaTable(n)
{
   inicijalizujTablu();
}

void Tabla::inicijalizujTablu(){
    m_statusPozicija = QVector <QVector <Status> > (m_dimenzijaTable);
    for(int i = 0; i < m_dimenzijaTable; i++) {
        m_statusPozicija[i] = QVector<Status> (m_dimenzijaTable);
    }
    for(int i = 0; i < m_dimenzijaTable; i++)
        for(int j = 0; j < m_dimenzijaTable; j++)
            m_statusPozicija[i][j] = NEUTRALNO;
};

QVector< QVector<Status> > Tabla::getSatusPozicija(){
    return m_statusPozicija;
}

int Tabla::getDimenzijaTable() {
    return m_dimenzijaTable;
}


QVector<Brod*> Tabla::getBrodovi() {
    return m_brodovi;
}

Brod* Tabla::getBrod(int i){
    return m_brodovi[i];
}

Status Tabla::statusPozicije(QPair<int, int> poz) {
    return m_statusPozicija[poz.first][poz.second];
};

void Tabla::setStatusPozicije(QPair<int, int> poz, Status status) {
    m_statusPozicija[poz.first][poz.second] = status;
};


void Tabla::dodajBrod(Brod* brod){
    m_brodovi.push_back(brod);
}


void Tabla::obrisiBrodove(){
    m_brodovi.clear();
}


QPair<int, int> Tabla::nadjiKrajBroda(QPair<int, int> pocetak, int rotacija, int duzina) {
    int x = pocetak.first;
    int y = pocetak.second;

    if(rotacija == 0)
        x += duzina-1;
    else
        y += duzina-1;

    QPair<int, int> kraj = QPair<int, int>(x, y);
    return kraj;
};

bool Tabla::korektnoPolje(int x, int y) {
    return x >= 0 && x < 10 && y >= 0 && y < 10;
}

bool Tabla::dozvoljenoMestoZaBrod(QPair<int, int> pocetak, QPair<int, int> kraj){
    int x1 = pocetak.first;
    int y1 = pocetak.second;

    int x2 = kraj.first;
    int y2 = kraj.second;

    if (x1 == x2) {
        while(y1 <= y2){
            if(korektnoPolje(x1, y1) && m_statusPozicija[x1][y1] != NEUTRALNO)
                return false;
            y1++;
        }
    }
    else{
        while(x1 <= x2){
            if(korektnoPolje(x1, y1) && m_statusPozicija[x1][y1] != NEUTRALNO)
                return false;
            x1++;
        }
    }

    return true;
};

void Tabla::oznaciPostavljenBrod(QPair<int, int> pocetak, QPair<int, int> kraj) {
    int x1 = pocetak.first;
    int y1 = pocetak.second;

    int x2 = kraj.first;
    int y2 = kraj.second;

    if(x1 == x2 && y1 == y2) {
        m_statusPozicija[x1][y1] = MINA;
    }
    else {
        if (x1 == x2) {
            while(y1 <= y2){
                m_statusPozicija[x1][y1] = DEO_BRODA;
                y1++;
            }
        }
        else{
            while(x1 <= x2){
                m_statusPozicija[x1][y1] = DEO_BRODA;
                x1++;
            }
        }
    }
};

void Tabla::postaviRandomBrodove(bool m) {
    bool prviPut = true;

    for(int i = 4; i >= 1; i--){

        int prvi, drugi, rotacija;
        QPair<int, int> pocetakRandomBroda;
        QPair<int, int> krajRandomBroda;

        while(1) {
            prvi = rand() % 10;
            drugi = rand() % 10;

            pocetakRandomBroda = QPair<int, int>(prvi, drugi);
            rotacija = rand() % 2;
            if(i<=4)
                krajRandomBroda = nadjiKrajBroda(pocetakRandomBroda, rotacija, i+1);
            else
                krajRandomBroda = pocetakRandomBroda;

            if(!korektnoPolje(krajRandomBroda.first, krajRandomBroda.second))
                continue;

            if(dozvoljenoMestoZaBrod(pocetakRandomBroda, krajRandomBroda))
                break;
        }


        oznaciPostavljenBrod(pocetakRandomBroda, krajRandomBroda);

        if(prviPut == false){
            m_brodovi.append(new Brod(i-1, pocetakRandomBroda, krajRandomBroda));
            int velicina_brodova = m_brodovi.size();
            m_brodovi[velicina_brodova-1]->setRotiran(rotacija);
            m_brodovi[velicina_brodova-1]->setFlags(Brod::ItemIsMovable);
        }
        else{
            m_brodovi.append(new Brod(i, pocetakRandomBroda, krajRandomBroda));
            int velicina_brodova = m_brodovi.size();
            m_brodovi[velicina_brodova-1]->setRotiran(rotacija);
            m_brodovi[velicina_brodova-1]->setFlags(Brod::ItemIsMovable);
        }

        if(i == 1 && prviPut){
            i++;
            prviPut = false;
        }
    }

    //provera za mine

    if(m){
        for(int i = 5; i <= 6; i++){
            int prvi, drugi;
            QPair<int, int> pocetakRandomBroda;
            QPair<int, int> krajRandomBroda;

            while(1) {
                prvi = rand() % 10;
                drugi = rand() % 10;

                pocetakRandomBroda = QPair<int, int>(prvi, drugi);
                krajRandomBroda = pocetakRandomBroda;

                if(!korektnoPolje(krajRandomBroda.first, krajRandomBroda.second))
                    continue;

                if(dozvoljenoMestoZaBrod(pocetakRandomBroda, krajRandomBroda))
                    break;
            }

            oznaciPostavljenBrod(pocetakRandomBroda, krajRandomBroda);


            m_brodovi.append(new Brod(i, pocetakRandomBroda, krajRandomBroda));
            int velicina_brodova = m_brodovi.size();
            m_brodovi[velicina_brodova-1]->setFlags(Brod::ItemIsMovable);

        }
    }
};


Tabla::~Tabla() {
    for(auto brod: m_brodovi)
        delete brod;
}


bool Tabla::sekuSe(QRectF p1, QRectF p2, bool rot1, bool rot2){
    float x1,x2,x1p,x2p,y1,y2,y1p,y2p;

    //prva duz
    if (!rot1){
        x1 = p1.x();
        y1 = p1.y() - KVADRAT / 2;

        x1p = x1 + p1.width();
        y1p = y1;
    }else{
        x1 = p1.x() + KVADRAT / 2;
        y1 = p1.y();

        x1p = x1;
        y1p = y1 - p1.width();
    }

    //druga duz
    if (!rot2){
        x2 = p2.x();
        y2 = p2.y() - KVADRAT / 2;

        x2p = x2 + p2.width();
        y2p = y2;
    }else{
        x2 = p2.x() + KVADRAT / 2;
        y2 = p2.y();

        x2p = x2;
        y2p = y2 - p2.width();
    }

    return ccw(QPair<int,int>(x1,y1),QPair<int,int>(x2,y2),QPair<int,int>(x2p,y2p)) != ccw(QPair<int,int>(x1p,y1p),QPair<int,int>(x2,y2),QPair<int,int>(x2p,y2p)) && ccw(QPair<int,int>(x1,y1),QPair<int,int>(x1p,y1p),QPair<int,int>(x2,y2)) != ccw(QPair<int,int>(x1,y1),QPair<int,int>(x1p,y1p),QPair<int,int>(x2p,y2p));
}




float Tabla::ccw(QPair<float,float>A, QPair<float,float> B, QPair<float,float> C){
     return (C.second-A.second) * (B.first-A.first) > (B.second-A.second) * (C.first-A.first);
}




QPair<int,int> Tabla::proveriKolizije(bool m){

    int k = m ? 7 : 5;
    for(int i = 0; i < k; i++){
        if(!m_brodovi[i]->getNaTabli()){
            return QPair<int,int>(-1,-1);
        }
    }

    QRectF* prostor[k];
    for(int i = 0; i < k; i++){
        if(m_brodovi[i]->getRotiran()){
            prostor[i] = new QRectF(m_brodovi[i]->pos().x() - KVADRAT, m_brodovi[i]->pos().y(), KVADRAT, KVADRAT*(m_brodovi[i]->getVelicinaBroda()));
        }else{
            prostor[i] = new QRectF(m_brodovi[i]->pos().x(), m_brodovi[i]->pos().y(), KVADRAT*(m_brodovi[i]->getVelicinaBroda()), KVADRAT);
        }
    }

    for(int first=0;first<k;++first)
    {
        for(int second=0;second<k;++second)
        {
            if(first == second){
                continue;
            }

            if(prostor[first]->intersects(*prostor[second]) || prostor[first]->contains(*prostor[second]))
            {
                delete prostor[0];
                delete prostor[1];
                delete prostor[2];
                delete prostor[3];
                delete prostor[4];
                if(m){
                    delete prostor[5];
                    delete prostor[6];
                }
                return QPair<int,int>(first, second);
            }
        }

    }

    delete prostor[0];
    delete prostor[1];
    delete prostor[2];
    delete prostor[3];
    delete prostor[4];
    if(m){
        delete prostor[5];
        delete prostor[6];
    }
    return QPair<int,int>(11,11);
}
