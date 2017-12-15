#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "spccom.h"    // 串口操作类


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void btnOpen_clicked();

    void btnClose_clicked();

    void btnSendData_clicked();

    void recv(QByteArray);   // 接收串口信号 （槽函数实现）

   // void on_testReceveData_destroyed();

private:
    QPushButton     *btnOpen;
    QPushButton     *btnClose;
    QPushButton     *btnSendData;

    Ui::MainWindow *ui;
    SPCcom *m_spcomm;
};


#endif // MAINWINDOW_H
