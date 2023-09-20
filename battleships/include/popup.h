#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class PopUp;
}

class PopUp : public QDialog
{
    Q_OBJECT

public:
    explicit PopUp(QWidget *parent = nullptr);
    ~PopUp();
    void setBrojPoena(int);
    void incijalizujLabelu();

private slots:
    void on_pushButtonSacuvaj_clicked();

private:
    Ui::PopUp *ui;
    int m_brojPoena=0;
};

#endif // POPUP_H
