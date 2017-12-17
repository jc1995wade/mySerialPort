#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qDebug"
#include <QComboBox>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_spcomm = new SPCcom();
    hexFlag  = false;
     // 将获取到的端口号设置到端口选择界面
     ui->cb_COM->addItem(m_spcomm->m_listcomboName.join(","));

     // 绑定串口接收函数和文本显示函数
    connect(m_spcomm, SIGNAL(send(QByteArray)), this, SLOT(recv(QByteArray)));

    QIcon btnImgClose(":/icons/close.png");
    QIcon btnImgOpen(":/icons/open.png");

    ui->btnClose->setIcon(btnImgClose);
    ui->btnClose->setIconSize(QSize(65, 45));
    ui->btnClose->setFlat(true);

    ui->btnOpen->setIcon(btnImgOpen);
    ui->btnOpen->setIconSize(QSize(65, 45));
    ui->btnOpen->setFlat(true);

    ui->photo_label->setText("串口关闭");
    ui->textRData->setReadOnly(true);  // 设置只读

    ui->textRData->append("hello world");
    ui->textRData->append("hello world");
    ui->textRData->append("hello world");
    ui->textRData->append("hello world");
 #if 0
/* 16进制接收文本*/
    QString str1 = "h";
    QByteArray str2 = QByteArray::fromHex(str1.toLatin1().data());
    qDebug()<<str2;
/*16进制发送文本*/
   QByteArray str4 = "12345";
   QString strDis;
   QString str3 = str4.toHex().data();
   str3 = str3.toUpper();
   for(int i=0; i<str3.length(); i+= 2)
   {
       QString st = str3.mid(i,2);
       strDis += st;
       strDis += " ";
   }
    ui->textRData->append(strDis);
 #endif
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_spcomm;
}

// 显示串口数据
void MainWindow::recv(QByteArray n)
{
    if(hexFlag == false)
    {
         ui->textRData->append(n);
    }
    else{
        ui->textRData->append(print_Hex(n));
    }
}

// 将QByreArray转为16进制文本
 QString MainWindow::print_Hex(const QByteArray str)
 {
     QString strDis;
     QString str3 = str.toHex().data();
     str3 = str3.toUpper();
     for(int i=0; i<str3.length(); i+= 2)
     {
         QString st = str3.mid(i,2);
         strDis += st;
         strDis += " ";
     }
     return strDis;
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
        ui->photo_label->setText("已经打开");
       qDebug() << "打开串口成功";
    }
    else
        ui->photo_label->setText("打开失败");
        qDebug() << "串口打开失败";
}

void MainWindow::on_btnClose_clicked()
{
    if(m_spcomm->isOpen())
    {
        m_spcomm->close();
        ui->photo_label->setText("串口关闭");
        qDebug() << "关闭串口成功";
    }
    else
    {
        ui->photo_label->setText("串口关闭");
        qDebug()<<"串口已经关闭";
    }

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

// 串口选择
void MainWindow::on_cb_COM_currentIndexChanged(const QString &arg1)
{
    if(arg1 != NULL)
    {
        m_spcomm->m_portName = arg1;
        qDebug()<<arg1;
    }
    else
    {
        qDebug()<<"未读到串口";
    }

}

// 波特率选择
void MainWindow::on_cb_baudRate_2_currentIndexChanged(const QString &arg1)
{
    m_spcomm->m_baudRate = arg1.toInt();
    qDebug()<<arg1;
}

// 数据位选择
void MainWindow::on_cb_dataBits_currentIndexChanged(const QString &arg1)
{
    m_spcomm->m_dataBits = arg1.toInt();
    qDebug()<<arg1.toInt();
}
// 停止位选择
void MainWindow::on_cb_stopBit_currentIndexChanged(const QString &arg1)
{
    int tmp = arg1.toInt();
    if(arg1.toFloat() == 1.5)
    {
        tmp = 3;
    }
    m_spcomm->m_stopBits = tmp;
    qDebug()<<tmp;
}

// 校验位选择
void MainWindow::on_cb_chickBit_currentIndexChanged(int index)
{
    if(index >0)
    {
      index++;
    }
    m_spcomm->m_parity = index;
    qDebug()<<index;
}

// 流控制选择
void MainWindow::on_cb_controlFlow_currentIndexChanged(int index)
{
    m_spcomm->m_flowControl = index;
    qDebug()<<index;
}

// 窗口清除
void MainWindow::on_btnClear_clicked()
{
    ui->textRData->clear();
    ui->editSendData->clear();
}

// Hex显示
void MainWindow::on_checkBox_2_clicked()
{
//    QString arr = ui->textRData->text();
 //   qDebug()<<arr;
    hexFlag  = !hexFlag;
    qDebug()<<hexFlag;
}
