#include "include/Multiplayer.h"
#include "ui_partija.h"

Multiplayer* Multiplayer::aktivnaPartija = nullptr;
bool Multiplayer::obaPovezana = false;

Multiplayer::Multiplayer(QWidget* parent, QString adresa)
    : m_klijent(new Klijent()),
      m_parent(parent)
{
    m_klijent->povezi(adresa);
    Multiplayer::aktivnaPartija = this;
    connect(this, &Multiplayer::posaljiPozicijuKlijentu, m_klijent, &Klijent::procitajPoziciju);
    connect(m_klijent, &Klijent::posaljiPoziciju, this, &Multiplayer::procitajPozicijuOdKlijenta);

    connect(this, &Multiplayer::posaljiBrodoveKlijentu, m_klijent, &Klijent::procitajBrodove);
    connect(m_klijent, &Klijent::posaljiBrodove, this, &Multiplayer::procitajBrodoveOdKlijenta);

    connect(this, &Multiplayer::posaljiPorukuKlijentu, m_klijent, &Klijent::procitajPoruku);
    connect(m_klijent, &Klijent::posaljiPoruku, this, &Multiplayer::procitajPorukuOdKlijenta);

    ui->labelTajmer->setHidden(true);
    ui->pushButtonMine->setVisible(false);
    ui->radioButtonTajmer->setDisabled(true);
    ui->radioButtonTajmer->setVisible(false);
}

Multiplayer::~Multiplayer() {
    delete m_klijent;
}

QWidget* Multiplayer::getParent() {
    return m_parent;
}

bool Multiplayer::getProtivnikOdustao() {
    return m_protivnikOdustao;
}

void Multiplayer::postaviProtivnikOdustao(bool indikator) {
    m_protivnikOdustao = indikator;
}

bool Multiplayer::getIzasaoKlijent() {
    return m_izasaoKlijent;
}

void Multiplayer::postaviIzasaoKlijent(bool indikator) {
    m_izasaoKlijent = indikator;
}

void Multiplayer::postaviIndikator(bool indikator) {
    m_klijent1_ind = indikator;
}

void Multiplayer::on_pushButtonZapocni_clicked(){
    QPair<int,int> res = m_tabla1->proveriKolizije(false);
    if(res == QPair<int,int>(11,11)){
        if(Multiplayer::obaPovezana || !m_klijent1_ind) {
            std::string brodovi;
            for(auto brod: m_tabla1->getBrodovi()) {
                auto pocetnaPoz = brod->getPocetak();
                auto krajnjaPoz = brod->getKraj();

                brodovi.append(std::to_string(pocetnaPoz.first) + "," + std::to_string(pocetnaPoz.second) + ",");
                brodovi.append(std::to_string(krajnjaPoz.first) + "," + std::to_string(krajnjaPoz.second) + ";");
            }
            emit posaljiBrodoveKlijentu(brodovi);
            ui->stackedWidget->setCurrentIndex(1);
            iscrtajSvojeBrodove();
            m_tabla1->inicijalizujTablu();
            for(auto brod: m_tabla1->getBrodovi())
                m_tabla1->oznaciPostavljenBrod(brod->getPocetak(), brod->getKraj());
            if(m_klijent->tvojPotez){
                ui->label->setText("Ti si na potezu!");
            }
            else{
                ui->label->setText("Protivnik na potezu!");
            }
        }
        else {
            ui->labelKorektnaPostavka->setText("Probaj malo kasnije, protivnik se jos nije povezao!");
            ui->labelKorektnaPostavka->setVisible(true);
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

        ui->labelKorektnaPostavka->setText(output);
        ui->labelKorektnaPostavka->setVisible(true);
    return;
    }
}


void Multiplayer::procitajPozicijuOdKlijenta(int x, int y) {
    QPair<int,int> pozicija=QPair<int,int>(x,y);

    if(m_tabla1->statusPozicije(QPair<int,int>(x,y))==DEO_BRODA){
        m_tabla1->setStatusPozicije(QPair<int,int>(x,y),POGODJEN);
        Partija::pustiMuziku(":/sounds/resources/sound/exs_sound.wav", 15);
        ui->label_2->setPixmap(QPixmap(":/resources/resources/img/explosion.png"));
        ui->label_2->raise();
        ui->label_2->setScaledContents(true);
        ui->label_2->setGeometry(pozicija.second*40+20, pozicija.first*40+70,40,40);

        QLabel *label_flames = new QLabel("", this);
        label_flames->setPixmap(QPixmap(":/resources/resources/img/flames.png"));
        label_flames->setGeometry(pozicija.second*40+31, pozicija.first*40+81, 40, 40);
        label_flames->setAlignment(Qt::AlignCenter);
        label_flames->setScaledContents(true);
        label_flames->show();

        ui->tableWidget->item(x,y)->setBackground(QPixmap(":/resources/resources/img/fire.jpg"));

        int brodIdx = odrediKomBroduPripadaPolje(pozicija, 1);
        m_pogodjeniDeloviBrodova1[brodIdx] += 1;
        ui->label->setText("Protivnik na potezu!");
        m_klijent->tvojPotez=false;
        proveriStatusIgre();
    }
    else{
        m_tabla1->setStatusPozicije(QPair<int,int>(x,y),PROMASEN);
        Partija::pustiMuziku(":/sounds/resources/sound/splash.wav", 20);
        ui->tableWidget->item(x,y)->setBackground(QPixmap(":/resources/resources/img/res.png"));
        ui->label_2->setPixmap(QPixmap(":/resources/resources/img/water.png"));
        ui->label_2->setScaledContents(true);
        ui->label_2->setGeometry(pozicija.second*40+10, pozicija.first*40+60,60,60);
        ui->label->setText("Ti si na potezu!");
        m_klijent->tvojPotez=true;
    }

}

void Multiplayer::poljeKliknuto(QTableWidgetItem* polje) {
    int x = polje->row();
    int y = polje->column();
    QPair<int,int> pozicija=QPair<int,int>(x,y);
    int brodIdx = -1;
    if(m_klijent->tvojPotez && m_prviKlik[x][y]){

        if(m_tabla2->statusPozicije(pozicija) != NEUTRALNO && m_tabla2->statusPozicije(pozicija) != PROMASEN){
              m_tabla2->setStatusPozicije(pozicija, POGODJEN);
              Partija::pustiMuziku(":/resources/resources/sound/exs_sound.wav", 15);
              ui->label_2->setPixmap(QPixmap(":/resources/resources/img/explosion.png"));
              ui->label_2->raise();
              ui->label_2->setScaledContents(true);
              ui->label_2->setGeometry(pozicija.second*40+580, pozicija.first*40+70,40,40);

              ui->tableWidget_2->item(x,y)->setBackground(QPixmap(":/resources/resources/img/fire.jpg"));

              ui->label->setText("Ti si na potezu");
              m_klijent->tvojPotez=true;
              aktivnaPartija->m_sudija->DodajDobitnePoene(1);

              brodIdx = odrediKomBroduPripadaPolje(pozicija, 2);
              m_pogodjeniDeloviBrodova2[brodIdx] += 1;
              proveriStatusIgre();
        }
        else{
            m_tabla2->setStatusPozicije(pozicija, PROMASEN);
            Partija::pustiMuziku(":/sounds/resources/sound/splash.wav", 20);
            ui->tableWidget_2->item(x,y)->setBackground(Qt::transparent);
            ui->label_2->setPixmap(QPixmap(":/resources/resources/img/water.png"));
            ui->label_2->setScaledContents(true);
            ui->label_2->setGeometry(pozicija.second*40+570, pozicija.first*40+60,60,60);

            aktivnaPartija->m_sudija->resetujKombo(1);
            ui->label->setText("Protivnik na potezu!");
            m_klijent->tvojPotez=false;
        }
        m_prviKlik[x][y] = false;
        emit posaljiPozicijuKlijentu(x, y);
    }
    if(brodIdx != -1 && m_pogodjeniDeloviBrodova2[brodIdx] == duzinaBroda(brodIdx,2)){
        QLabel *label_brod = new QLabel("", this);
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
                label_brod->setGeometry(pocetak_broda_y*40+590, pocetak_broda_x*40+80, 40, duzinaBroda(brodIdx,1)*40);
            }
            else{
                label_brod->setGeometry((pocetak_broda_y)*40+590, (pocetak_broda_x)*40+80, 40, duzinaBroda(brodIdx,2)*40);
            }
        }else{
            if(m_randPokrenut > 0){
                label_brod->setGeometry(pocetak_broda_y*40+590, pocetak_broda_x*40+80, duzinaBroda(brodIdx,1)*40,40);
            }
            else{
                label_brod->setGeometry((pocetak_broda_y)*40+590, (pocetak_broda_x)*40+80, duzinaBroda(brodIdx,2)*40, 40);
            }
        }
        label_brod->setPixmap(pixmap);
        label_brod->setAlignment(Qt::AlignCenter);
        label_brod->setScaledContents(true);
        label_brod->show();
    }
}

void Multiplayer::procitajBrodoveOdKlijenta(std::string brodovi) {
    QString tmp = QString::fromStdString(brodovi);
    auto protivnikoviBrodovi = tmp.split(";");
    for(const auto &brod: protivnikoviBrodovi) {
        if(brod.length() < 7)
            break;
        auto pozicije = brod.split(",");
        int x1 = pozicije[0].toInt();
        int y1 = pozicije[1].toInt();

        int x2 = pozicije[2].toInt();
        int y2 = pozicije[3].toInt();

        m_tabla2->dodajBrod(new Brod(1, QPair<int, int>(x1, y1), QPair<int, int>(x2, y2)));
        m_tabla2->oznaciPostavljenBrod(QPair<int, int>(x1, y1), QPair<int, int>(x2, y2));
    }
}

void Multiplayer::procitajPorukuOdKlijenta(std::string poruka) {
    if(poruka != "Protivnik odustao")
        return;
    Multiplayer::aktivnaPartija->ui->label->setText("Protivnik je odustao od partije!");
    Multiplayer::aktivnaPartija->m_sudija->DodajDobitnePoene(2);
    Multiplayer::obaPovezana = false;
    emit krajPartije();
}

Tabla* Multiplayer::getProtivnikovaTabla() {
    return m_tabla2;
}

void Multiplayer::on_pushButtonMine_clicked(){

}
