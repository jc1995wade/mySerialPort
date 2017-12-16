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
    void recv(QByteArray);   // 接收串口信号 （槽函数实现）

    void on_btnOpen_clicked();

    void on_btnClose_clicked();

    void on_btnSend_clicked();

private:
    QPushButton     *btnOpen;
    QPushButton     *btnClose;
    QPushButton     *btnSendData;

    Ui::MainWindow *ui;
    SPCcom *m_spcomm;
};


#endif // MAINWINDOW_H
