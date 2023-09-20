#include "include/partija.h"
#include "include/Singleplayer.h"
#include "ui_partija.h"
#include<QGraphicsScene>
#include<iostream>
#include "include/Multiplayer.h"
#include <QtMultimedia/QSoundEffect>
#include <QtMultimedia>
#include <QKeyEvent>
#include <QMenu>

class Singleplayer;

Partija::Partija(QWidget *parent) :
    QWidget(parent),
    m_sudija(new Sudija()),
    ui(new Ui::Partija),
    m_tabla1(new Tabla()),
    m_tabla2(new Tabla()),
    m_popUp1(new PopUp())
{

    int n = m_tabla2->getDimenzijaTable();
    m_prviKlik = QVector< QVector<bool> >(n);
    for(int i = 0; i < n; i++)
        m_prviKlik[i] = QVector<bool>(n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            m_prviKlik[i][j] = true;

    m_pogodjeniDeloviBrodova1 = QVector<int>(5);
    for(int i = 0; i < 5; i++)
        m_pogodjeniDeloviBrodova1[i] = 0;

    m_pogodjeniDeloviBrodova2 = QVector<int>(5);
    for(int i = 0; i < 5; i++)
        m_pogodjeniDeloviBrodova2[i] = 0;

    ui->setupUi(this);
    this->setWindowTitle("Battleships");

    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(40);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_2->horizontalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_2->verticalHeader()->setDefaultSectionSize(40);
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++){
            ui->tableWidget->setItem(i,j, new QTableWidgetItem);
            ui->tableWidget->item(i,j)->setBackground(Qt::transparent);
            ui->tableWidget->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable);
            ui->tableWidget_2->setItem(i,j, new QTableWidgetItem);
            ui->tableWidget_2->item(i,j)->setBackground(QColor(21,96,217));
            ui->tableWidget_2->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable);
        }

    ui->label->setWindowFlag(Qt::FramelessWindowHint);
    ui->label->setAttribute(Qt::WA_NoSystemBackground);

    ui->labelPobednik->setWindowFlag(Qt::FramelessWindowHint);
    ui->labelPobednik->setAttribute(Qt::WA_NoSystemBackground);


    ui->stackedWidget->setCurrentIndex(0);


    connect(ui->tableWidget_2, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(poljeKliknuto(QTableWidgetItem*)));
    connect(this,SIGNAL(krajPartije()),this,SLOT(prikazi()));

    m_randPokrenut = 0;

    connect(this,SIGNAL(hKeyPressed()), this, SLOT(onHKeyPressed()));


    ui->labelKorektnaPostavka->setVisible(false);

    m_scena = new QGraphicsScene(this);
    ui->graphicsViewPostavka->setScene(m_scena);

    m_scena->setSceneRect(0,0,442,442);

    NacrtajTablu();

    m_scenaFabrika = new QGraphicsScene(this);
    ui->graphicsViewFabrika->setScene(m_scenaFabrika);


    for(int k = 0; k < 5; k++){

        m_tabla1->dodajBrod(new Brod(k,QPair<int,int>(0,0),QPair<int,int>(0,0)));


        m_scenaFabrika->addItem(m_tabla1->getBrod(k));

        connect(m_tabla1->getBrod(k), SIGNAL(Clicked(int)), this, SLOT(OnClick(int)));
    }
    ui->page->setFocus();
    ui->page->setAttribute(Qt::WA_KeyboardFocusChange);

    QMenu *menu = new QMenu(this);
    menu->move(440,530);
    QSoundEffect *player = new QSoundEffect();
    QAction *action1 = menu->addAction("The Art of War");
    QAction *action2 = menu->addAction("First Transmission");
    QAction *action3 = menu->addAction("Iskljuci muziku");

    connect(action1, &QAction::triggered, [this, player] {
        pustiMuziku(player,":/sounds/resources/sound/theartofwar.wav",0.5);
    });
    connect(action2, &QAction::triggered, [this, player] {
        pustiMuziku(player,":/sounds/resources/sound/firstT.wav",1);
    });
    connect(action3, &QAction::triggered, [player] {
        player->stop();
    });

    connect(ui->pushButton, &QPushButton::clicked, [menu]{
        menu->show();
    });

    ui->labelTajmer->setVisible(false);
}

void Partija::proveriStatusIgre(){

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
        ui->label->hide();
        ui->labelPobednik->setText("IZGUBIO SI :(");
        ui->labelPobednik->setStyleSheet("font-size: 72pt; color: white");
        Multiplayer::aktivnaPartija->zavrsenaPartija = true;

        emit krajPartije();
    }

    if(suma2 == suma_duzina2){
        ui->label->hide();
        ui->labelPobednik->setText("POBEDIO SI!");
        ui->labelPobednik->setStyleSheet("font-size: 72pt; color: white");
        Multiplayer::aktivnaPartija->zavrsenaPartija = true;

        emit krajPartije();
    }

}

int Partija::odrediKomBroduPripadaPolje(QPair<int, int> pozicija, int id) {
    QVector<Brod*> brodovi;
    if(id == 1)
        brodovi = m_tabla1->getBrodovi();
    else
        brodovi = m_tabla2->getBrodovi();

    int brodIdx = -1;
    int i = 0;
    for(Brod* brod : brodovi) {
        int x1 = pozicija.first;
        int y1 = pozicija.second;

        int x2 = brod->getPocetak().first;
        int y2 = brod->getPocetak().second;

        int x3 = brod->getKraj().first;
        int y3 = brod->getKraj().second;

        if(x1 == x2 && y1 >= y2 && y1 <= y3) {
            brodIdx = i;
            return brodIdx;
        }
        else if(y1 == y2 && x1 >= x2 && x1 <= x3){
            brodIdx = i;
            return brodIdx;
        }
        i++;
    }
    return brodIdx;
}

void Partija::iscrtajSvojeBrodove() {

    QVector<Brod*> brodovi = m_tabla1->getBrodovi();
    bool indikator = false;
    for(int i = 0; i < brodovi.size(); i++) {
        int x1 = brodovi[i]->getPocetak().first;
        int y1 = brodovi[i]->getPocetak().second;

        int x2 = brodovi[i]->getKraj().first;
        int y2 = brodovi[i]->getKraj().second;

        int a = x1;
        int b = x2;
        if (x1==x2){
            a = y1;
            b = y2;
        }
        auto trenutni_label = ui->brod0;
        auto rotirani_label = ui->brod0_2;
        QPixmap pixmap = QPixmap(":/resources/resources/img/brod1.png");

        switch(b-a){
            case 1:
                if(indikator == false){
                    trenutni_label = ui->brod0;
                    rotirani_label = ui->brod0_2;
                    indikator = true;
                }else{
                    trenutni_label = ui->brod1;
                    rotirani_label = ui->brod1_2;
                }
                break;
            case 2:
                trenutni_label = ui->brod2;
                rotirani_label = ui->brod2_2;
                pixmap = QPixmap(":/resources/resources/img/brod2.png");
                break;
            case 3:
                trenutni_label = ui->brod3;
                rotirani_label = ui->brod3_2;
                pixmap = QPixmap(":/resources/resources/img/brod3.png");
                break;
            case 4:
                trenutni_label = ui->brod4;
                rotirani_label = ui->brod4_2;
                pixmap = QPixmap(":/resources/resources/img/brod4.png");
                break;
        }
        if(x1 == x2 && y1 == y2){
            pixmap = QPixmap(":/resources/resources/img/mine.png");
            QLabel *label = new QLabel("", this);
            label->setGeometry( y1*40+35,x1*40+83, 40, 40);
            label->setScaledContents(true);
            label->setPixmap(pixmap);
            label->show();
            m_tabla1->setStatusPozicije(QPair<int,int>(x1,y1), MINA);
        }
        else if(x1 == x2){
            trenutni_label->setPixmap(pixmap);
            trenutni_label->setScaledContents(true);
            trenutni_label->move(y1*40+20, x1*40+70);
            while(y1 <= y2) {
                y1++;

            }
        }
        else {
            rotirani_label->setScaledContents(true);
            rotirani_label->move(y1*40+20, x1*40+70);
            QTransform transform;
            transform.rotate(90);
            QPixmap rotatedPixmap = pixmap.transformed(transform);
            rotirani_label->setPixmap(rotatedPixmap);
            while(x1 <= x2) {
                x1++;
            }
        }

    }
}

int Partija::duzinaBroda(int brodIdx, int id) {
    QVector<Brod*> brodovi;
    if (id == 1)
        brodovi = m_tabla1->getBrodovi();
    else
        brodovi = m_tabla2->getBrodovi();

    QPair<int, int> pocetnaPoz = brodovi[brodIdx]->getPocetak();
    int x1 = pocetnaPoz.first;
    int y1 = pocetnaPoz.second;

    QPair<int, int> krajnjaPoz = brodovi[brodIdx]->getKraj();
    int x2 = krajnjaPoz.first;
    int y2 = krajnjaPoz.second;

    return std::max(abs(x1 - x2) + 1, abs(y1 - y2) + 1);
}


void Partija::on_pushButtonOdustani_clicked(){
    this->hide();
    if(Singleplayer::m_aktivnaPartija != nullptr) {
        emit Singleplayer::m_aktivnaPartija->odustao();
        Singleplayer::m_aktivnaPartija->getParent()->show();
        delete Singleplayer::m_aktivnaPartija;
    }
    else {
        Multiplayer::aktivnaPartija->getParent()->show();
        Multiplayer::obaPovezana = false;
        if(!Multiplayer::aktivnaPartija->zavrsenaPartija && !Multiplayer::aktivnaPartija->getProtivnikOdustao())
            emit Multiplayer::aktivnaPartija->posaljiPorukuKlijentu("Protivnik odustao");
        delete Multiplayer::aktivnaPartija;
    }

}

void Partija::emitLater(const QObject *obj, const char *signalOrSlot, int msDelay)
{
    QTimer::singleShot(msDelay, obj, signalOrSlot);
}

void Partija::prikazi(){
    m_sudija->upisiRezultat("igrac1");
    m_popUp1->setBrojPoena(m_sudija->DohvatiRezultate().value("igrac1"));
    m_popUp1->incijalizujLabelu();
    m_popUp1->show();
}
void Partija::on_pushButtonRandom_clicked(){
    srand(time(NULL));
    ui->pushButtonMine->setDisabled(true);
    ui->pushButtonMine->setVisible(false);
    iscrtajRandomPostavku();
}


void Partija::NacrtajTablu()
{
    int n;
    int m;

    ui->graphicsViewPostavka->centerOn(QPointF(SIR*POLJE/2, DUZ*POLJE/2));

    int x;
    int y;

    double pomeraj = 44;

    for (n = 0, x = 0; n < 10; ++n, x += pomeraj){
        for (m = 0, y = 0; m < 10; ++m, y += pomeraj){

            m_scena->addRect(x, y, pomeraj, pomeraj);

        }
    }
}



void Partija::OnClick(int i)
{
    ui->pushButtonRandom->setDisabled(true);
    ui->pushButtonRandom->setStyleSheet("color : darkRed;");
    m_scena->addItem(m_tabla1->getBrod(i));
    ui->pushButtonMine->setDisabled(true);
    ui->pushButtonMine->setVisible(false);
    return;
}

void Partija::onHKeyPressed()
{
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap(":/resources/resources/img/h.jpg"));
    label->move(500, 300);
    label->show();
}


void Partija::iscrtajRandomPostavku(){

    int m = mine ? 7 : 5;

    for(int i = 0; i < m; i++){
        m_scenaFabrika->removeItem(m_tabla1->getBrod(i));
    }
    m_tabla1->obrisiBrodove();

    if(Singleplayer::m_aktivnaPartija != nullptr)
        Singleplayer::m_aktivnaPartija->m_tabla1->postaviRandomBrodove(mine);
    else
        Multiplayer::aktivnaPartija->m_tabla1->postaviRandomBrodove(false);

    int xposP;
    int yposP;
    int xposK;
    int yposK;

    m = mine ? 6 : 4;

    for(int i = 4; i >= 0; i--){
        xposP = m_tabla1->getBrod(i)->getPocetak().first;
        yposP = m_tabla1->getBrod(i)->getPocetak().second;
        xposK = m_tabla1->getBrod(i)->getKraj().first;
        yposK = m_tabla1->getBrod(i)->getKraj().second;

        xposP = xposP * KVADRAT;
        yposP = yposP * KVADRAT;
        xposK = xposK * KVADRAT;
        yposK = yposK * KVADRAT;

        m_scena->addItem(m_tabla1->getBrod(i));
        m_tabla1->getBrod(i)->setNaTabli(true);

        if(xposP == xposK){
            m_tabla1->getBrod(i)->rotiraj();
            xposP = xposP + KVADRAT;
            xposK = xposK + KVADRAT;
        }
        m_tabla1->getBrod(i)->setX(xposP);
        m_tabla1->getBrod(i)->setY(yposP);

        xposP = xposP / KVADRAT;
        yposP = yposP / KVADRAT;
        if(m_tabla1->getBrod(i)->getRotiran()){
            m_tabla1->getBrod(i)->setPocetak(QPair<int,int>(yposP,xposP-1));
            m_tabla1->getBrod(i)->setKraj(QPair<int,int>(yposP+m_tabla1->getBrod(i)->getVelicinaBroda()-1,xposP-1));
        }
        else{
            m_tabla1->getBrod(i)->setPocetak(QPair<int,int>(yposP,xposP));
            m_tabla1->getBrod(i)->setKraj(QPair<int,int>(yposP,xposP+m_tabla1->getBrod(i)->getVelicinaBroda()-1));
        }
    }
    if(mine){
        for(int i = 6; i >= 5; i--){
            xposP = m_tabla1->getBrod(i)->getPocetak().first;
            yposP = m_tabla1->getBrod(i)->getPocetak().second;

            xposP = xposP * KVADRAT;
            yposP = yposP * KVADRAT;


            m_scena->addItem(m_tabla1->getBrod(i));
            m_tabla1->getBrod(i)->setNaTabli(true);

            m_tabla1->getBrod(i)->setX(xposP);
            m_tabla1->getBrod(i)->setY(yposP);

            xposP = xposP / KVADRAT;
            yposP = yposP / KVADRAT;
            m_tabla1->getBrod(i)->setPocetak(QPair<int,int>(yposP,xposP));
            m_tabla1->getBrod(i)->setKraj(QPair<int,int>(yposP,xposP));
        }
    }
    m_randPokrenut++;

    ui->pushButtonRandom->setDisabled(true);
    ui->pushButtonRandom->setText("Samo jedna random postavka dozvoljena");
    ui->pushButtonRandom->setStyleSheet("color : darkRed;");

}
void Partija::pustiMuziku(QString putanja, double jacinaZvuka){

    QSoundEffect *player = new QSoundEffect();
    player->setSource(QUrl::fromLocalFile(putanja));
    player->setVolume(jacinaZvuka);
    player->play();

    return;
}
void Partija::pustiMuziku(QSoundEffect *player,QString putanja, double jacinaZvuka){

    player->setSource(QUrl::fromLocalFile(putanja));
    player->setVolume(jacinaZvuka);
    player->play();

    return;
}

void Partija::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_H){
        emit hKeyPressed();
    }
}


void Partija::closeEvent(QCloseEvent* event) {
    if(Multiplayer::aktivnaPartija != nullptr && !Multiplayer::aktivnaPartija->zavrsenaPartija
            && !Multiplayer::aktivnaPartija->getIzasaoKlijent())
        emit Multiplayer::aktivnaPartija->posaljiPorukuKlijentu("Protivnik odustao");

    QWidget::closeEvent(event);
}

Partija::~Partija() {
    delete m_tabla1;
    delete m_tabla2;
    delete m_sudija;
    delete ui;
}

