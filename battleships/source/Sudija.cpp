#include "../include/Sudija.h"

void Sudija::DodajDobitnePoene(int id){
    if(id == 1){
        m_poeni_1 += (++m_kombo_1) * 5;

    }
    else {
        if(m_poeni_1 < 100)
            m_poeni_1 = 100;
    }
}

void Sudija::kazniIgraca(int id){
    if(id == 1){
        m_poeni_1 -= 20;
    }else{
        m_poeni_2 -= 20;
    }
}

void Sudija::resetujKombo(int id){
    if(id == 1){
        m_kombo_1 = 0;
    }else{
        m_kombo_2 = 0;
    }
}

QMap<QString, int> Sudija::DohvatiRezultate(){
    return m_rezultati;
}

void Sudija::upisiRezultat(QString ime){
    if(m_poeni_1 > m_poeni_2){
        m_rezultati[ime] = m_poeni_1;
    }
    else{
        m_rezultati[ime] = m_poeni_2;
    }
}




