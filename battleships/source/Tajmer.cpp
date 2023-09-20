#include "include/Tajmer.h"
#include <iostream>

Tajmer::Tajmer(QObject *parent)
    : QThread(parent)
{

}


void Tajmer::run(){
    m_sat = new QElapsedTimer();

    m_sat->start();
    ispisiVreme();

    while(m_sek >= 0){
        if(m_sat->elapsed() >= 1000){
            ispisiVreme();
            m_sat->start();
        }

        if(m_sek == 0){
            emit tajmerIstekao();
            m_interfejs->labelTajmer->setText("CPU");
            m_interfejs->label->setText("Protivnik je na potezu");
            while(m_sek < 10){
                m_sat->start();
            }
        }
    }
}



void Tajmer::setInterfejs(Ui::Partija* ui){
    m_interfejs = ui;
}



void Tajmer::ispisiVreme(){
    m_interfejs->labelTajmer->setText(QString::number(m_sek >= 0 ? m_sek - 1 : 0));
    if(m_sek > 0){
        m_sek--;
    }
}


void Tajmer::resetujSek(){
    m_sek = 11;
}


int Tajmer::saljiSekunde(int s){
    return s;
}

void Tajmer::prekiniBrojanje(){
    m_sek = -1;
}

void Tajmer::dodajSekunde(int koliko){
    if(m_sek + koliko >= 11){
        m_sek = 11;
    }else{
        m_sek = m_sek + koliko;
    }
}
