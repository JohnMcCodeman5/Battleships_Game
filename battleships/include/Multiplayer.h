#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "include/Klijent.h"
#include "include/partija.h"

class Multiplayer : public Partija {
    Q_OBJECT
public:
    Multiplayer(QWidget* parent = nullptr, QString adresa = "");
    ~Multiplayer();
    static Multiplayer* aktivnaPartija;
    QWidget* getParent();
    Tabla* getProtivnikovaTabla();
    static bool obaPovezana;
    void postaviIndikator(bool);
    void postaviProtivnikOdustao(bool);
    bool getProtivnikOdustao();
    void postaviIzasaoKlijent(bool);
    bool getIzasaoKlijent();
    bool zavrsenaPartija = false;

signals:
    void posaljiPozicijuKlijentu(int x, int y);
    void posaljiBrodoveKlijentu(std::string brodovi);
    void posaljiPorukuKlijentu(std::string poruka);

public slots:
    void procitajPozicijuOdKlijenta(int x, int y);
    void poljeKliknuto(QTableWidgetItem*) override;
    void on_pushButtonZapocni_clicked() override;
    void procitajBrodoveOdKlijenta(std::string brodovi);
    void procitajPorukuOdKlijenta(std::string poruka);
    void on_pushButtonMine_clicked() override;

private:
    bool m_klijent1_ind = false;
    Klijent* m_klijent;
    QWidget* m_parent;
    bool m_protivnikOdustao = false;
    bool m_izasaoKlijent = false;
};

#endif // MULTIPLAYER_H
