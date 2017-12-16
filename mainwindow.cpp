#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qDebug"
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_spcomm = new SPCcom();

     // 将获取到的端口号设置到端口选择界面
     ui->cb_COM->addItem(m_spcomm->m_listcomboName.join(","));

     // 绑定串口接收函数和文本显示函数
    connect(m_spcomm, SIGNAL(send(QByteArray)), this, SLOT(recv(QByteArray)));
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_spcomm;
}

// 显示串口数据
void MainWindow::recv(QByteArray n)
{
     ui->textRData->append(n);
}


// 打开串口按钮
void MainWindow::on_btnOpen_clicked()
{
    if(m_spcomm->isOpen())
    {
         qDebug() << "串口已经打开";
        return;
    }
    m_spcomm->setBaudRate(115200);
    m_spcomm->setPortName("com8");
    if(m_spcomm->open())
    {
       qDebug() << "打开串口成功";
    }
    else
        qDebug() << "串口打开失败";
}

void MainWindow::on_btnClose_clicked()
{
    if(m_spcomm->isOpen())
    {
        m_spcomm->close();
        qDebug() << "关闭串口成功";
    }
    else
        qDebug()<<"串口已经关闭";
}

// 串口发送函数
void MainWindow::on_btnSend_clicked()
{
   QString send =  ui->editSendData->text();     // 获取发送文本
    const char *psend = send.toStdString().data();  // QString 转为 const char * 类型

    if(m_spcomm->isOpen())             // 发送文本
    {
        m_spcomm->writeData((char *)psend, qstrlen(psend));
        qDebug()<<psend;
    }
    else
    {
        qDebug()<<"串口未打开";
    }

}
