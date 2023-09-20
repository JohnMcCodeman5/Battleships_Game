#include "../include/Singleplayer.h"
#include "ui_partija.h"

Singleplayer* Singleplayer::m_aktivnaPartija = nullptr;

Singleplayer::Singleplayer(QWidget* parent, bool tezinaBota)
    : m_parent(parent),
      m_tezinaBota(tezinaBota)

{
    Singleplayer::m_aktivnaPartija = this;
    m_tajmer = new Tajmer();
    m_tajmer->setInterfejs(ui);
    connect(m_tajmer, SIGNAL(tajmerIstekao()), this, SLOT(potezBota()));
    connect(this, &Singleplayer::botNaPotezu, this, &Singleplayer::potezBota);
    connect(this, &Singleplayer::odustao, this, &Singleplayer::ugasiTajmer);
}

void Singleplayer::poljeKliknuto(QTableWidgetItem* polje) {
    int red = polje->row();
    int kolona = polje->column();
    if(m_prviKlik[red][kolona] && !m_zakljucanaTabla) {
        QPair<int,int> pozicija = QPair<int,int>();
        pozicija.first = red;
        pozicija.second = kolona;

        bool igracNaPotezu = Singleplayer::m_aktivnaPartija->odigrajPotezIgraca(pozicija);
        if(!igracNaPotezu){
            emitLater(this,SIGNAL(botNaPotezu()),1000);
        }
    }

    proveriStatusIgre();
}

bool Singleplayer::getTezina() {
    return m_tezinaBota;
}


bool Singleplayer::getMine(){
    return m_mine;
}


QWidget* Singleplayer::getParent() {
    return m_parent;
}

bool Singleplayer:: getBlokiranIgrac(){
    return m_blokiran_igrac;
}

void Singleplayer:: setBlokiranIgrac(bool b){
    m_blokiran_igrac = b;
}

bool Singleplayer::odigrajPotezIgraca(QPair<int, int> pozicija) {

    bool igraj_ponovo = false;

    int red = pozicija.first;
    int kolona = pozicija.second;
    m_prviKlik[red][kolona] = false;
    int brodIdx = -1;
    if(m_tabla2->statusPozicije(pozicija) != NEUTRALNO && m_tabla2->statusPozicije(pozicija) != PROMASEN && m_tabla2->statusPozicije(pozicija) != MINA){
        m_tabla2->setStatusPozicije(pozicija, POGODJEN);
        Partija::pustiMuziku(":/sounds/resources/sound/exs_sound.wav", 0.8);
        ui->label_2->setPixmap(QPixmap(":/resources/resources/img/explosion.png"));
        ui->label_2->raise();
        ui->label_2->setScaledContents(true);
        ui->label_2->setGeometry(pozicija.second*40+580, pozicija.first*40+70,40,40);

        ui->tableWidget_2->item(red,kolona)->setBackground(QPixmap(":/resources/resources/img/fire.jpg"));

        m_aktivnaPartija->m_sudija->DodajDobitnePoene(1);

        if(m_je_singleplayer){
          m_tajmer->dodajSekunde(2);
        }

        brodIdx = odrediKomBroduPripadaPolje(pozicija, 2);
        m_pogodjeniDeloviBrodova2[brodIdx] += 1;
        igraj_ponovo = true;
    }
    else if(m_tabla2->statusPozicije(pozicija) == MINA){
        m_tabla2->setStatusPozicije(pozicija, POGODJENA_MINA);

        if(m_je_singleplayer){
          ui->labelTajmer->setText("CPU");
          m_tajmer->resetujSek();
        }

        ui->tableWidget_2->item(red,kolona)->setBackground(QPixmap(":/resources/resources/img/mine_scaled.png"));
        m_aktivnaPartija->m_sudija->kazniIgraca(1);
        m_blokiran_igrac = true;
        igraj_ponovo = false;
    }
    else{

        if(m_je_singleplayer){
          ui->labelTajmer->setText("CPU");
          m_tajmer->resetujSek();
        }
        Partija::pustiMuziku(":/sounds/resources/sound/splash.wav", 0.8);
        m_tabla2->setStatusPozicije(pozicija, PROMASEN);
        ui->tableWidget_2->item(red,kolona)->setBackground(Qt::transparent);
        ui->label_2->setPixmap(QPixmap(":/resources/resources/img/water.png"));
        ui->label_2->setScaledContents(true);
        ui->label_2->setGeometry(pozicija.second*40+570, pozicija.first*40+60,60,60);
        m_aktivnaPartija->m_sudija->resetujKombo(1);
        igraj_ponovo = false;
    }

    if(!igraj_ponovo && !m_blokiran_bot){
        ui->label->setText("Protivnik na potezu!");
        m_zakljucanaTabla = true;
    }
    else if(!igraj_ponovo && m_blokiran_bot) {
        igraj_ponovo = true;
        m_blokiran_bot = false;
    }

    if(brodIdx != -1 && m_pogodjeniDeloviBrodova2[brodIdx] == duzinaBroda(brodIdx,2)){
        QLabel *label = new QLabel("", this);
        QPixmap pixmap = QPixmap(":/resources/resources/img/brod1.png");

        switch(duzinaBroda(brodIdx,2)){
            case 3:
                pixmap = QPixmap(":/resources/resources/img/brod2.png");
            break;
            case 4:
                pixmap = QPixmap(":/resources/resources/img/brod3.png");
            break;
            case 5:
                pixmap = QPixmap(":/resources/resources/img/brod4.png");
            break;
        }

        int pocetak_broda_x = m_tabla2->getBrod(brodIdx)->getPocetak().first;
        int pocetak_broda_y = m_tabla2->getBrod(brodIdx)->getPocetak().second;
        int kraj_broda_y = m_tabla2->getBrod(brodIdx)->getKraj().second;
        if(pocetak_broda_y == kraj_broda_y){
            QTransform transform;
            transform.rotate(90);
            pixmap = pixmap.transformed(transform);
            if(m_randPokrenut > 0){
                label->setGeometry(pocetak_broda_y*40+590, pocetak_broda_x*40+80, 40, duzinaBroda(brodIdx,1)*40);
            }
            else{
                label->setGeometry((pocetak_broda_y)*40+590, (pocetak_broda_x)*40+80, 40, duzinaBroda(brodIdx,2)*40);
            }
        }else{
            if(m_randPokrenut > 0){
                label->setGeometry(pocetak_broda_y*40+590, pocetak_broda_x*40+80, duzinaBroda(brodIdx,1)*40,40);
            }
            else{
                label->setGeometry((pocetak_broda_y)*40+590, (pocetak_broda_x)*40+80, duzinaBroda(brodIdx,2)*40, 40);
            }
        }
        label->setPixmap(pixmap);
        label->setAlignment(Qt::AlignCenter);
        label->setScaledContents(true);
        label->show();
    }
    auto flags = ui->tableWidget_2->item(red, kolona)->flags();
    ui->tableWidget_2->item(red, kolona)->setFlags(flags & (Qt::ItemIsSelectable | Qt::ItemIsEditable));
    ui->tableWidget_2->item(red, kolona)->setSelected(false);

    return igraj_ponovo;
}

bool Singleplayer::odigrajEasyPotezBota() {

    if(!m_blokiran_bot){
        QPair<int, int> randomPozicja;
        while(1) {
            int x = rand() % m_tabla1->getDimenzijaTable();
            int y = rand() % m_tabla1->getDimenzijaTable();

            randomPozicja = QPair<int, int>(x, y);

            if(m_tabla1->statusPozicije(randomPozicja) != PROMASEN && m_tabla1->statusPozicije(randomPozicja) != POGODJEN && m_tabla1->statusPozicije(randomPozicja) != POGODJENA_MINA)
                break;
        }

        if(m_tabla1->statusPozicije(randomPozicja) == NEUTRALNO){
            m_tabla1->setStatusPozicije(randomPozicja, PROMASEN);
            Partija::pustiMuziku(":/sounds/resources/sound/splash.wav", 0.8);
            m_tabla1->setStatusPozicije(randomPozicja, PROMASEN);
            ui->tableWidget->item(randomPozicja.first, randomPozicja.second)->setData(Qt::DecorationRole, QPixmap(":/resources/resources/img/res.png"));
            ui->label_2->setPixmap(QPixmap(":/resources/resources/img/water.png"));
            ui->label_2->setScaledContents(true);
            ui->label_2->setGeometry(randomPozicja.second*40 + 10, randomPozicja.first*40+60,60,60);
            ui->label->setText("Tvoj potez!");
            m_zakljucanaTabla = false;
            return false;
        }
        else if(m_tabla1->statusPozicije(randomPozicja) == MINA){
              m_tabla1->setStatusPozicije(randomPozicja, POGODJENA_MINA);
              ui->tableWidget->item(randomPozicja.first, randomPozicja.second)->setBackground(QPixmap(":/resources/resources/img/fire.jpg"));

              m_aktivnaPartija->m_sudija->kazniIgraca(2);
              ui->label->setText("Tvoj potez!");
              m_blokiran_bot = true;
              m_zakljucanaTabla = false;
              return false;
        }

        else{
            m_tabla1->setStatusPozicije(randomPozicja, POGODJEN);

            Partija::pustiMuziku(":/sounds/resources/sound/exs_sound.wav", 0.8);
            QLabel *label = new QLabel("", this);
            label->setPixmap(QPixmap(":/resources/resources/img/flames.png"));
            label->setGeometry(randomPozicja.second*40+31, randomPozicja.first*40+81, 40, 40);
            label->setAlignment(Qt::AlignCenter);
            label->setScaledContents(true);

            ui->label_2->setPixmap(QPixmap(":/resources/resources/img/explosion.png"));
            ui->label_2->setScaledContents(true);
            ui->label_2->setGeometry(randomPozicja.second*40 + 10, randomPozicja.first*40+60,60,60);
            QTimer::singleShot(1000, label, &QLabel::show);
            int brodIdx = odrediKomBroduPripadaPolje(randomPozicja, 1);
            m_pogodjeniDeloviBrodova1[brodIdx] += 1;
        }

        return true;
    }
    else{
        m_blokiran_bot = false;
    }
    return false;
}


QPair<int, int> Singleplayer::odrediPotez(){
    QPair<int, int> pom;
    int x = m_aktivnaPartija->m_Prethodna_Pozicija.first;
    int y = m_aktivnaPartija->m_Prethodna_Pozicija.second;
    if(m_aktivnaPartija->m_sled == LEVO && Tabla::korektnoPolje(x, y + 1))
        pom = QPair<int, int>(x, y+1);
    if(m_aktivnaPartija->m_sled == DESNO && Tabla::korektnoPolje(x, y - 1))
        pom = QPair<int, int>(x , y - 1);
    if(m_aktivnaPartija->m_sled == GORE && Tabla::korektnoPolje(x - 1, y))
        pom = QPair<int, int>(x - 1, y);
    if(m_aktivnaPartija->m_sled == DOLE && Tabla::korektnoPolje(x + 1, y))
        pom = QPair<int, int>(x + 1, y);
    return pom;
}
void Singleplayer::setPokret(int pomerac){
    if(pomerac == 0)
        m_aktivnaPartija->m_sled = START;
    if(pomerac == 1)
        m_aktivnaPartija->m_sled = LEVO;
    if(pomerac == 2)
        m_aktivnaPartija->m_sled = DESNO;
    if(pomerac == 3)
        m_aktivnaPartija->m_sled = GORE;
    if(pomerac == 4)
        m_aktivnaPartija->m_sled = DOLE;
}

bool Singleplayer::odigrajHardPotezBota(){
    if(!m_blokiran_bot){
        QPair<int, int> currentPozicja;
        int pomerac = 0;

        while(1){
            if(m_aktivnaPartija->m_sled == START){
                int x = rand() % m_tabla1->getDimenzijaTable();
                int y = rand() % m_tabla1->getDimenzijaTable();
                currentPozicja = QPair<int, int>(x, y);

                if(m_tabla1->statusPozicije(currentPozicja) != PROMASEN &&
                   m_tabla1->statusPozicije(currentPozicja) != POGODJEN &&
                   m_tabla1->statusPozicije(currentPozicja) != POGODJENA_MINA)
                    break;
            }
            else{
                currentPozicja = odrediPotez();
                if(m_tabla1->statusPozicije(currentPozicja) != PROMASEN &&
                   m_tabla1->statusPozicije(currentPozicja) != POGODJEN &&
                   m_tabla1->statusPozicije(currentPozicja) != POGODJENA_MINA)
                    break;
                else{
                    pomerac++;
                    pomerac %= 5;
                    setPokret(pomerac);
                }
            }
        }


        if(m_tabla1->statusPozicije(currentPozicja) == NEUTRALNO){
            Partija::pustiMuziku(":/sounds/resources/sound/splash.wav", 0.8);
            m_tabla1->setStatusPozicije(currentPozicja, PROMASEN);
            ui->tableWidget->item(currentPozicja.first, currentPozicja.second)->setData(Qt::DecorationRole, QPixmap(":/resources/resources/img/res.png"));
            ui->label_2->setPixmap(QPixmap(":/resources/resources/img/water.png"));
            ui->label_2->setScaledContents(true);
            ui->label_2->setGeometry(currentPozicja.second*40 + 10, currentPozicja.first*40+60,60,60);
            if(m_aktivnaPartija->m_sled != START){
                pomerac++;
                pomerac %= 5;
                setPokret(pomerac);
            }
            ui->label->setText("Tvoj potez!");
            m_zakljucanaTabla = false;
            return false;
        }
        else if(m_tabla1->statusPozicije(currentPozicja) == MINA){
            m_tabla1->setStatusPozicije(currentPozicja, POGODJENA_MINA);
            ui->tableWidget->item(currentPozicja.first, currentPozicja.second)->setBackground(QPixmap(":/resources/resources/img/fire.jpg"));
            if(m_aktivnaPartija->m_sled != START){
                pomerac++;
                pomerac %= 5;
                setPokret(pomerac);
            }
            m_aktivnaPartija->m_sudija->kazniIgraca(2);
            m_blokiran_bot = true;
            m_zakljucanaTabla = false;
            ui->label->setText("Tvoj potez!");
            return false;
        }
        else{
            m_tabla1->setStatusPozicije(currentPozicja, POGODJEN);
            Partija::pustiMuziku(":/sounds/resources/sound/exs_sound.wav", 0.8);
            QLabel *label = new QLabel("", this);
            label->setPixmap(QPixmap(":/resources/resources/img/flames.png"));
            label->setGeometry(currentPozicja.second*40+31, currentPozicja.first*40+81, 40, 40);
            label->setAlignment(Qt::AlignCenter);
            label->setScaledContents(true);

            ui->label_2->setPixmap(QPixmap(":/resources/resources/img/explosion.png"));
            ui->label_2->setScaledContents(true);
            ui->label_2->setGeometry(currentPozicja.second*40 + 10, currentPozicja.first*40+60,60,60);
            QTimer::singleShot(1000, label, &QLabel::show);



            m_aktivnaPartija->m_Prethodna_Pozicija = currentPozicja;
            if(m_aktivnaPartija->m_sled == START){
                pomerac++;
                setPokret(pomerac);
            }

            int brodIdx = odrediKomBroduPripadaPolje(currentPozicja, 1);
            m_pogodjeniDeloviBrodova1[brodIdx] += 1;
            if(m_pogodjeniDeloviBrodova1[brodIdx] == duzinaBroda(brodIdx, 1)){
                pomerac = 0;
                setPokret(pomerac);
            }
            return true;
        }
    }
    return false;
}

void Singleplayer::potezBota()
{

    ui->labelTajmer->setText("CPU");

    bool uspesan=false;
    if(!Singleplayer::m_aktivnaPartija->getTezina()){
        uspesan=Singleplayer::m_aktivnaPartija->odigrajEasyPotezBota();
        proveriStatusIgre();
        if(uspesan){
            emitLater(this,SIGNAL(botNaPotezu()),1000);
        }
        else {
            if(Singleplayer::m_aktivnaPartija->getBlokiranIgrac()){
                Singleplayer::m_aktivnaPartija->setBlokiranIgrac(false);
                ui->label->setText("Protivnik na potezu!");
                emitLater(this,SIGNAL(botNaPotezu()),1000);
            }
        }
    }
    if(Singleplayer::m_aktivnaPartija->getTezina()){
        uspesan=Singleplayer::m_aktivnaPartija->odigrajHardPotezBota();
        proveriStatusIgre();
        if(uspesan){
            emitLater(this,SIGNAL(botNaPotezu()),1000);
        }
        else {
            if(Singleplayer::m_aktivnaPartija->getBlokiranIgrac()){
                Singleplayer::m_aktivnaPartija->setBlokiranIgrac(false);
                ui->label->setText("Protivnik na potezu!");
                emitLater(this,SIGNAL(botNaPotezu()),1000);
            }
        }
    }

    if(m_je_singleplayer){
        m_tajmer->resetujSek();
    }

}

void Singleplayer::on_pushButtonZapocni_clicked(){
    QPair<int,int> res = m_tabla1->proveriKolizije(mine);
    if(res == QPair<int,int>(11,11)){
        if(ui->radioButtonTajmer->isChecked() == true){
            m_je_singleplayer = true;
            ui->labelTajmer->setVisible(true);
        }

        ui->stackedWidget->setCurrentIndex(1);
        iscrtajSvojeBrodove();
        m_tabla1->inicijalizujTablu();
        for(auto brod: m_tabla1->getBrodovi())
            m_tabla1->oznaciPostavljenBrod(brod->getPocetak(), brod->getKraj());
        Singleplayer::m_aktivnaPartija->m_tabla2->postaviRandomBrodove(mine);

        if(m_je_singleplayer){
            m_tajmer->start();
        }

    }else if(res == QPair<int,int>(-1,-1)){
        ui->labelKorektnaPostavka->setText("Svi brodovi moraju biti postavljeni!");
        ui->labelKorektnaPostavka->setVisible(true);
        return;
    }else{       
        int i, j;
        if(m_randPokrenut == 0 || m_randPokrenut > 1){
            i = (res.first == 0) ? 2 : res.first + 1;
            j = res.second + 1;
        }else{
            i = ((res.first == 0) ? 5 : 5 - res.first) == 1 ? 2 : (res.first == 0) ? 5 : 5 - res.first;
            j = (5 - res.second) == 1 ? 2 : 5 - res.second;
        }

        QString output = "Kolizija brodova velicine " + QString::number(i) + " i " + QString::number(j);

        if((i == 0 && j == -1) || (i == 6 && j == 7)){
            output = "Kolizija mina";
        }else if(j == 0 || j == -1 || j == 6 || j == 7){
            output = "Kolizija broda velicine " + QString::number(i) + " i mine";
        }

        ui->labelKorektnaPostavka->setText(output);
        ui->labelKorektnaPostavka->setVisible(true);
    return;
    }
}

void Singleplayer::on_pushButtonMine_clicked(){
    mine = true;

    m_tabla1->dodajBrod(new Brod(5,QPair<int,int>(0,0),QPair<int,int>(0,0)));


    m_scenaFabrika->addItem(m_tabla1->getBrod(5));

    connect(m_tabla1->getBrod(5), SIGNAL(Clicked(int)), this, SLOT(OnClick(int)));

    m_tabla1->dodajBrod(new Brod(6,QPair<int,int>(0,0),QPair<int,int>(0,0)));


    m_scenaFabrika->addItem(m_tabla1->getBrod(6));

    connect(m_tabla1->getBrod(6), SIGNAL(Clicked(int)), this, SLOT(OnClick(int)));

    ui->pushButtonMine->setDisabled(true);
    ui->pushButtonMine->setVisible(false);
    ui->pushButtonMine->setStyleSheet("color : darkRed;");
}



void Singleplayer::proveriStatusIgre(){

    QVector<int> pogodjeni1 = Partija::m_pogodjeniDeloviBrodova1;
    QVector<int> pogodjeni2 = Partija::m_pogodjeniDeloviBrodova2;

    int suma1 = std::accumulate(pogodjeni1.begin(), pogodjeni1.end(), 0);
    int suma2 = std::accumulate(pogodjeni2.begin(), pogodjeni2.end(), 0);

    QVector<Brod*> brodovi1 = m_tabla1->getBrodovi();
    int suma_duzina1 = 0;
    for(int i = 0; i < 5; i++){
        suma_duzina1 += duzinaBroda(i, 1);
    }

    QVector<Brod*> brodovi2 = m_tabla2->getBrodovi();
    int suma_duzina2 = 0;
    for(int i = 0; i < 5; i++){
        suma_duzina2 += duzinaBroda(i, 2);
    }

    if(suma1 == suma_duzina1){
        ui->labelPobednik->setText("IZGUBIO SI :(");
        ui->labelPobednik->setStyleSheet("font-size: 72pt; color: white");
        ui->labelTajmer->setText("KRAJ");
        ui->label->hide();
        m_tajmer->prekiniBrojanje();
        emit krajPartije();

    }

    if(suma2 == suma_duzina2){
        ui->labelPobednik->setText("POBEDIO SI!");
        ui->labelPobednik->setStyleSheet("font-size: 72pt; color: white");
        ui->labelTajmer->setText("KRAJ");
        ui->label->hide();
        m_tajmer->prekiniBrojanje();
        emit krajPartije();

    }

}

void Singleplayer::ugasiTajmer() {
    m_tajmer->prekiniBrojanje();
}
