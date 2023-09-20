#include "../include/Brod.h"
#define KVADRAT 44
//Brod::Brod(){}

Brod::Brod(int broj, QPair<int, int> poc,QPair<int,int> kraj)
    : m_id(broj),m_pozPocetak(poc),m_pozKraj(kraj),m_naTabli(false)
{
    m_brojBroda = broj;

    pritisnuto = false;

    m_rotiran = false;

    m_velicinaBroda = (m_brojBroda == 0 ? 2 : m_brojBroda + 1);

    if(m_brojBroda >= 5){
        m_velicinaBroda = 1;
    }
}

Brod::Brod(const Brod& brod)
    : QObject(), QGraphicsItem()
{
    m_id = brod.m_id;
    m_pozPocetak = brod.m_pozPocetak;
    m_pozKraj = brod.m_pozKraj;
}


Brod& Brod::operator=(const Brod& brod){
    m_id = brod.m_id;
    m_pozPocetak = brod.m_pozPocetak;
    m_pozKraj = brod.m_pozKraj;
    return *this;
}


bool Brod::getRotiran(){
    return m_rotiran;
}

Brod::~Brod() = default;

int Brod::getId(){
    return m_id;
}

void Brod::setId(int id)
{
    this->m_id=id;
}

QPair<int, int> Brod::getPocetak()
{
    return m_pozPocetak;
}

void Brod::setPocetak(QPair<int,int> pocetak)
{
    this->m_pozPocetak=pocetak;
}

QPair<int, int> Brod::getKraj()
{
    return m_pozKraj;
}

void Brod::setKraj(QPair<int,int> kraj)
{
    this->m_pozKraj=kraj;
}

bool Brod::getNaTabli()
{
    return m_naTabli;
}

void Brod::setNaTabli(bool b)
{
    this->m_naTabli=b;
}

void Brod::setBrojBroda(int i){
    this->m_brojBroda = i;
}

void Brod::setVelicinaBroda(int i){
    this->m_velicinaBroda = (i == 0 ? 2 : i + 1);
}

void Brod::setRotiran(int r){
    m_rotiran = r;
}

int Brod::getVelicinaBroda(){
    return m_velicinaBroda;
}


QRectF Brod::boundingRect() const
{

    switch(m_brojBroda)
        {
        case 0:
            return QRectF(0,0,KVADRAT*2,KVADRAT);
            break;
        case 1:
            return QRectF(0,m_naTabli ? 0 : KVADRAT,KVADRAT*2,KVADRAT);
            break;
        case 2:
            return QRectF(0,m_naTabli ? 0 : KVADRAT*2,KVADRAT*3,KVADRAT);
            break;
        case 3:
            return QRectF(0,m_naTabli ? 0 : KVADRAT*3,KVADRAT*4,KVADRAT);
            break;
        case 4:
            return QRectF(0,m_naTabli ? 0 : KVADRAT*4,KVADRAT*5,KVADRAT);
            break;
        case 5:
            return QRectF(0,m_naTabli ? 0: KVADRAT*6, KVADRAT, KVADRAT);
            break;
        case 6:
            return QRectF(0,m_naTabli ? 0: KVADRAT*7, KVADRAT, KVADRAT);
            break;
        }
        return QRectF(0,0,0,0);

}


void Brod::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF rec = boundingRect();

    QRectF rec1;
    if (m_naTabli == 0){
        m_naTabli = 1;
        rec1 = boundingRect();
        m_naTabli = 0;
    }
    QBrush brush(QColorConstants::DarkCyan);

    if (pritisnuto){
        brush.setColor(QColorConstants::Svg::pink);
    }
    else {
        brush.setColor(QColorConstants::DarkCyan);
        if(m_velicinaBroda == 1){
            brush.setColor(QColorConstants::DarkMagenta);
        }
    }
    QPixmap pixmap;
    switch(m_velicinaBroda){
        case 1:
            pixmap.load(":/resources/resources/img/mine_scaled.png");
            break;
        case 2:
            pixmap.load(":/resources/resources/img/brod1");
            break;
        case 3:
            pixmap.load(":/resources/resources/img/brod2");
            break;
        case 4:
            pixmap.load(":/resources/resources/img/brod3");
            break;
        case 5:
            pixmap.load(":/resources/resources/img/brod4");
        break;
        default:
            pixmap.load(":/resources/resources/img/mine.png");
        break;
    }
    if(m_naTabli == 0){
        painter->drawPixmap(rec, pixmap, rec1);
    }
    else{
        painter->drawPixmap(rec, pixmap, rec);
    }
}


void Brod::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    setFlags(ItemIsMovable);
    prepareGeometryChange();
    m_naTabli = true;
    emit Clicked(m_brojBroda);
}

void Brod::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton && m_naTabli == true && m_rotiran == false)
    {
        setRotation(90);

        m_rotiran = true;
    }
    else if(event->button() == Qt::RightButton && m_naTabli == true && m_rotiran)
    {

        setRotation(0);

        m_rotiran = false;
    }
    else if(m_naTabli == true)
    {
        pritisnuto = true;
        update();
        QGraphicsItem::mousePressEvent(event);
    }



}

void Brod::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pritisnuto = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);

    QPointF xandy;
    int currentX;
    int currentY;
    pos();
    xandy = pos();

    currentX = xandy.x();
    currentY = xandy.y();
    currentX = KVADRAT * (currentX/KVADRAT);
    currentY = KVADRAT * (currentY/KVADRAT);
    if(!m_rotiran){
        //ako nije rotiran
        if (currentY < 0)
        {
            currentY = 0;
        }
        if (currentX < 0)
        {
            currentX = 0;
        }
        if (currentY+KVADRAT >= 10*KVADRAT)
        {
            currentY = 9 * KVADRAT;
        }
        if (currentX + m_velicinaBroda * KVADRAT > 10*KVADRAT+2)
        {
            currentX = 10 * KVADRAT - KVADRAT*m_velicinaBroda;
        }
        setX(currentX);
        setY(currentY);
    }

    else{
        //ako jeste rotiran

        if (currentY < 0)
        {
            currentY = 0;
        }
        if (currentX < KVADRAT)
        {
            currentX = KVADRAT;
        }
        if (currentY+KVADRAT*m_velicinaBroda > 10*KVADRAT)
        {
            currentY = 10*KVADRAT - KVADRAT*m_velicinaBroda;
        }
        if (currentX > 10*KVADRAT+4)
        {
            currentX = 10 * KVADRAT;
        }
        setX(currentX);
        setY(currentY);
    }


    x_pos[m_brojBroda] = this->pos().x();
    y_pos[m_brojBroda] = this->pos().y();



    setX(currentX);
    setY(currentY);

    currentX = currentX / KVADRAT;
    currentY = currentY / KVADRAT;
    if(m_rotiran){
        Brod::setPocetak(QPair<int,int>(currentY,currentX-1));
        Brod::setKraj(QPair<int,int>(currentY+m_velicinaBroda-1,currentX));
    }
    else{
        Brod::setPocetak(QPair<int,int>(currentY,currentX));
        Brod::setKraj(QPair<int,int>(currentY,currentX+m_velicinaBroda-1));
    }
    update();
}


void Brod::rotiraj(){
    setRotation(90);
    m_rotiran = true;
}
