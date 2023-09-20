#ifndef BROD_H
#define BROD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPair>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

class Brod : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Brod(int broj,QPair<int,int> poc,QPair<int,int> kraj);
    Brod(const Brod&);
    Brod& operator=(const Brod&);
    ~Brod();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void setBrojBroda(int);
    void setVelicinaBroda(int);

    int getId();
    void setId(int id);
    QPair<int,int> getPocetak();
    void setPocetak(QPair<int,int> pocetak);
    QPair<int,int> getKraj();
    void setKraj(QPair<int,int> kraj);
    bool getNaTabli();
    void setNaTabli(bool b);
    void setRotiran(int);
    bool getRotiran();
    int getVelicinaBroda();
    void rotiraj();

    bool pritisnuto;
    QMap<int, int> x_pos;
    QMap<int, int> y_pos;

private:
    int m_id;
    QPair<int,int> m_pozPocetak;
    QPair<int,int> m_pozKraj;
    QPainter *painter();
    bool m_naTabli;
    bool m_rotiran;
    int m_brojBroda;
    int m_velicinaBroda;
    bool m_postavljen;

signals:
    void Clicked(int shipsize);
    void promenaStanja();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BROD_H
