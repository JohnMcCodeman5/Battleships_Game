#ifndef PARTIJA_H
#define PARTIJA_H

#include "include/Sudija.h"
#include "include/Tabla.h"
#include "include/popup.h"

#include "qtablewidget.h"
#include <QWidget>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QSoundEffect>
#define SIR 12
#define DUZ 12
#define POLJE 30
#define KVADRAT 44

namespace Ui {
class Partija;
}

class Partija : public QWidget
{
    Q_OBJECT

public:
    explicit Partija(QWidget *parent = nullptr);
    ~Partija();
    int odrediKomBroduPripadaPolje(QPair<int, int>, int id);
    int duzinaBroda(int brodIdx, int id);
    virtual void proveriStatusIgre();
    void iscrtajSvojeBrodove();
    void emitLater(const QObject*,const char*,int);
    bool mine = false;
    void pustiMuziku(QSoundEffect *,QString, double);
    void pustiMuziku(QString, double);


public slots:
    virtual void poljeKliknuto(QTableWidgetItem*) = 0;
    virtual void on_pushButtonZapocni_clicked() = 0;
    void closeEvent(QCloseEvent *) override;
    virtual void on_pushButtonMine_clicked() = 0;



private slots:
    void on_pushButtonRandom_clicked();
    void on_pushButtonOdustani_clicked();

    void prikazi();
    void OnClick(int shipnum);
    void onHKeyPressed();

signals:
    void krajPartije();
    void hKeyPressed();

protected:
    QVector<int> m_pogodjeniDeloviBrodova1;
    QVector<int> m_pogodjeniDeloviBrodova2;
    Sudija* m_sudija;
    Ui::Partija *ui;
    Tabla* m_tabla1;
    Tabla* m_tabla2;
    PopUp *m_popUp1=nullptr;
    QVector< QVector<bool> > m_prviKlik;
    bool m_zakljucanaTabla = false;
    QGraphicsScene *m_scena;
    QGraphicsScene *m_scenaFabrika;
    int m_randPokrenut;

    void NacrtajTablu();
    void iscrtajRandomPostavku();

private:
    void keyPressEvent(QKeyEvent *event) override;
};


#endif // PARTIJA_H
