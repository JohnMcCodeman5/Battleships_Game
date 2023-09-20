#include "include/popup.h"
#include "ui_popup.h"

PopUp::PopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUp)
{
    ui->setupUi(this);
}

PopUp::~PopUp()
{
    delete ui;
}

void PopUp::setBrojPoena(int brPoena)
{
    m_brojPoena=brPoena;
}

void PopUp::on_pushButtonSacuvaj_clicked()
{
    QString ime;
    ime=ui->lineEditIme->text();
    QString ime_fajla="../battleships/resources/rezultati.csv";
    QFile fajl(ime_fajla);

    QString podaci;
    QStringList redovi;
    QStringList red;
    podaci.clear();
    redovi.clear();
    red.clear();

    if(fajl.open(QFile::ReadWrite))
    {
        podaci=fajl.readAll();
        redovi=podaci.split("\n");
    }

    int poz=0;
    for(int i=0;i<redovi.size()-1;i++)
    {
        red=redovi.at(i).split(",");

        int brPoena=red.at(1).toInt();
        if(m_brojPoena<brPoena){
            poz=poz+1;
        }
    }
    QTextStream stream(&fajl);
    stream.seek(0);
    for(int i=0;i<poz;i++){
        stream<<redovi.at(i)<<"\n";
    }
    stream<<ime<<","<<m_brojPoena<<"\n";
    for(int i=poz;i<redovi.size()-1;i++){
        stream<<redovi.at(i)<<"\n";
    }
    fajl.close();
    this->hide();
}

void PopUp::incijalizujLabelu() {
    QString labelText = QStringLiteral("POENI: %1").arg(m_brojPoena);
    ui->labelPoeni->setText(labelText);
}


