#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "include/partija.h"
#include "include/Tajmer.h"

enum Pokret {
    START = 0,
    LEVO = 1,
    DESNO = 2,
    GORE = 3,
    DOLE = 4
};

class Singleplayer : public Partija
{
    Q_OBJECT
public:
    Singleplayer(QWidget* parent = nullptr, bool tezinaBota = false);
    ~Singleplayer() = default;
    bool odigrajPotezIgraca(QPair<int, int>);
    bool odigrajEasyPotezBota();
    bool odigrajHardPotezBota();
    static Singleplayer* m_aktivnaPartija;
    bool getTezina();
    QWidget* getParent();
    bool getMine();
    bool getBlokiranIgrac();
    void setBlokiranIgrac(bool);
    void proveriStatusIgre() override;

public slots:
    void poljeKliknuto(QTableWidgetItem*) override;
    void potezBota();
    void on_pushButtonZapocni_clicked() override;
    void on_pushButtonMine_clicked() override;
    void ugasiTajmer();

signals:
    void botNaPotezu();
    void odustao();

private:
    QWidget* m_parent;
    bool m_tezinaBota;
    bool m_mine;
    QPair<int, int> odrediPotez();
    void setPokret(int);
    Pokret m_sled = START;
    QPair<int, int> m_Prethodna_Pozicija = QPair<int, int>(-1,-1);

    Tajmer *m_tajmer;
    bool m_je_singleplayer = false;

    bool m_blokiran_bot = false;
    bool m_blokiran_igrac = false;
};


#endif // SINGLEPLAYER_H
