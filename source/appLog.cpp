#include "appLog.h"
/*
 * Сведение числа к обратному
 * В программе используются только числа от 1 до 5
 * При остальных выдавать -1(символизирует об ошибке ввода)
 */
double ReverseFraction(double frac)
{
    if(frac < 1 || frac > 5)
        return -1;//Проерка на корректность ввода

    return 1/frac;
}


void MakeRavers (std::string parEl, double frac,QWidget *parent)
{
    char row = parEl[5];
    char col = parEl[6];

    QString rewEl="Crit_"+col+row;
    QLineEdit *rewEdit = parent->findChild<QLineEdit*>(rewEl);

    //rewEdit->setText(ReverseFraction(frac));
}
