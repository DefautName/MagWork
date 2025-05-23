#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenPushBut_clicked();

    void on_SaveAs_clicked();

    void on_Save_clicked();

    void on_CompHelp_clicked();

    void on_KritHelp_clicked();

    void on_Crit_12_editingFinished();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
