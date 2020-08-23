#include "suggerimento.h"

Suggerimento::Suggerimento(QString testo_, QWidget* parent): QPushButton(parent), testo(testo_)
{
    setIcon(QIcon(":/resources/Suggestion.png"));
    setIconSize(QSize(16,16));
    //setFixedSize(20,20);

    connect(this, SIGNAL(clicked()), this, SLOT(show()));

}


void Suggerimento::show() const{
    auto msg= QMessageBox(QMessageBox::Information, "Suggerimento", testo, QMessageBox::Ok);
    msg.exec();
}