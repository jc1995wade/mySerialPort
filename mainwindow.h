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

    QString print_Hex(const QByteArray str);

private slots:
    void recv(QByteArray);   // 接收串口信号 （槽函数实现）

    void on_btnOpen_clicked();
    void on_btnClose_clicked();
    void on_btnSend_clicked();

    void on_cb_COM_currentIndexChanged(const QString &arg1);
    void on_cb_baudRate_2_currentIndexChanged(const QString &arg1);
    void on_cb_dataBits_currentIndexChanged(const QString &arg1);

    void on_cb_stopBit_currentIndexChanged(const QString &arg1);

    void on_cb_chickBit_currentIndexChanged(int index);

    void on_cb_controlFlow_currentIndexChanged(int index);

    void on_btnClear_clicked();

    void on_checkBox_2_clicked();

private:
    QPushButton     *btnOpen;
    QPushButton     *btnClose;
    QPushButton     *btnSendData;
    QPushButton     *button_movie;
    bool  hexFlag;
    Ui::MainWindow *ui;
    SPCcom *m_spcomm;

};


#endif // MAINWINDOW_H
