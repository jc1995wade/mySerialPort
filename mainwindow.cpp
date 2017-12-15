#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnOpen = new QPushButton("open", this);
    btnOpen->setGeometry(50, 50, 80, 40);
    //btnOpen->setFont(f);

   btnClose = new QPushButton("close", this);
   btnClose->setGeometry(50, 150, 80, 40);
    //btnClose->setFont(f);

   btnSendData = new QPushButton("send", this);
   btnSendData->setGeometry(50, 330, 80, 40);

    m_spcomm = new SPCcom();

    // 绑定串口接收函数和文本显示函数
    connect(m_spcomm, SIGNAL(send(QByteArray)), this, SLOT(recv(QByteArray)));

    connect(btnOpen,  SIGNAL(clicked(bool)), this,  SLOT(btnOpen_clicked()));
    connect(btnClose,  SIGNAL(clicked(bool)),  this,  SLOT(btnClose_clicked()));
    connect(btnSendData,  SIGNAL(clicked(bool)),  this,  SLOT(btnSendData_clicked()));
    ui->textRData->setText("12456");

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
void MainWindow::btnOpen_clicked()
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



void MainWindow::btnClose_clicked()
{
    if(m_spcomm->isOpen())
    {
        m_spcomm->close();
        qDebug() << "关闭串口成功";
    }
    else
        qDebug()<<"串口已经关闭";

}



void MainWindow::btnSendData_clicked()
{
   unsigned char ch[] = {0xEF, 0x01,
            0xFF, 0xFF, 0xFF, 0xFF,
            0x01,
            0x00, 0x03,
            0x0f,
            0x01, 0x03};
}


