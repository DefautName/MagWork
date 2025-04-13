#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QtGui>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenPushBut_clicked()
{
     QString fileName = QFileDialog::getOpenFileName(this,
                                                    QString::fromUtf8("Открыть файл"),
                                                    QDir::currentPath(),
                                                    "All files (*.*)");
    QMessageBox msgBox;     // диалоговое окно
    msgBox.setText(fileName); // устанавливаем текст
    msgBox.exec();  // отображаем диалоговое окно
}


void MainWindow::on_SaveAs_clicked()
{
    /*
QString fileName = QFileDialog::getSaveFileName(this,
                            QString::fromUtf8("Сохранить файл"),
                            QDir::currentPath(),
                            "Images (*.png *.xpm *.jpg);;All files (*.*)");
     * */
    QMessageBox msgBox;     // диалоговое окно
    msgBox.setText("SaveAs"); // устанавливаем текст
    msgBox.exec();  // отображаем диалоговое окно
}


void MainWindow::on_Save_clicked()
{
    QMessageBox msgBox;     // диалоговое окно
    msgBox.setText("Save"); // устанавливаем текст
    msgBox.exec();  // отображаем диалоговое окно
}

