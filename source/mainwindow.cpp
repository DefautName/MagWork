#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "appLog.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QtGui>

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
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
                                                    "JSON files (*.json)");
    QMessageBox msgBox;     // диалоговое окно
    msgBox.setText(fileName); // устанавливаем текст
    msgBox.exec();  // отображаем диалоговое окно
}


void MainWindow::on_SaveAs_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                QString::fromUtf8("Сохранить файл"),
                                QDir::currentPath(),
                                "JSON files (*.json)");

    QMessageBox msgBox;     // диалоговое окно
    msgBox.setText("SaveAs " + fileName); // устанавливаем текст
    msgBox.exec();  // отображаем диалоговое окно
}


void MainWindow::on_Save_clicked()
{
    QMessageBox msgBox;     // диалоговое окно
    msgBox.setText("Save"); // устанавливаем текст
    msgBox.exec();  // отображаем диалоговое окно
}


void MainWindow::on_CompHelp_clicked()
{
    QMessageBox msgBox;     // диалоговое окно
    msgBox.setText("Объяснение как сделать сравнение вариантов по критериям"); // устанавливаем текст
    msgBox.exec();  // отображаем диалоговое окно

}


void MainWindow::on_KritHelp_clicked()
{
    QMessageBox msgBox;     // диалоговое окно
    msgBox.setText("Объяснение как сделать сравнение критериев между собой"); // устанавливаем текст
    msgBox.exec();  // отображаем диалоговое окно

}


void MainWindow::on_Crit_12_editingFinished()
{
  //  MakeRavers("Crit_12", 0.5,this);
}

