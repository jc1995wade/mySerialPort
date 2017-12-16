#include "spccom.h"
#include "qdebug.h"
#include "mainwindow.h"

//构造函数 添加初始化数据
SPCcom::SPCcom(QObject *parent):QObject(parent)
{
    m_serialPort = new QSerialPort();
    m_baudRate = 9600;
    m_portName = "com1";

    /*====获取可用串口号====*/
    QString path = "HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
    QSettings *settings = new QSettings(path, QSettings::NativeFormat);
    QStringList key = settings->allKeys();
    int num = (int)key.size();
    QString value;
    for(int i = 0; i<num; i++)
    {
        value  = getcomm(i, "value");
        qDebug()<<value;
        m_listcomboName<<value;
    }


}


// index 为索引号，keyorvalue 为选择返回值应该为key还value
QString SPCcom::getcomm(int index, QString keyorvalue)
{
    QString commresult;

   if(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),0,KEY_READ,&hKey)!=0)
   {
       QString error = "Cannot open regedit!";
       return error;
   }
   QString keymessage;  // 键名
   QString message;
   QString valuemessage; // 键值
   indexnum = index;   // 要读取键值的索引号
   keysize=sizeof(keyname);
   valuesize = sizeof(keyvalue);
   if(::RegEnumValue(hKey,indexnum,keyname,&keysize,0,&type,(BYTE*)keyvalue,&valuesize)==0)//列举键名和值
   {
       for(int i=0; i<keysize; i++)
       {
           message=keyname[i];
           keymessage.append(message);
       }
       for(int j=0; j<valuesize; j++)
       {
           if(keyvalue[j] != 0x00)
           {
               valuemessage.append(keyvalue[j]);
           }
       }
       if(keyorvalue=="key")
       {
           commresult=keymessage;
       }
       else
       {
          // qDebug()<<"nokey";
           commresult=valuemessage;
       }
       return commresult;
       ::RegCloseKey(hKey);   // 关闭注册表
   }
}



bool SPCcom::isOpen() const
{
    return m_serialPort->isOpen();
}


// 设置波特率
static QSerialPort::BaudRate getBaudRate(int baudRate)
{
    switch(baudRate)
    {
    case 1200:
        return QSerialPort::Baud1200;
    case 2400:
        return QSerialPort::Baud2400;
    case 4800:
        return QSerialPort::Baud4800;
    case 9600:
        return QSerialPort::Baud9600;
    case 19200:
        return QSerialPort::Baud19200;
    case 38400:
        return QSerialPort::Baud38400;
    case 57600:
        return QSerialPort::Baud57600;
    case 115200:
        return QSerialPort::Baud115200;
    default:
            return QSerialPort::UnknownBaud;
    }
}

// 设置串口名字
// window 下用"com1"
void SPCcom::setPortName(const QString &name)
{
    m_portName = name;
}

// 获取串口名字
QString SPCcom::portName() const
{
    return m_portName;
}

// 设置波特率 9600
void SPCcom::setBaudRate(int baudRate)
{
    m_baudRate = baudRate;
}

// 打开串口，调用前，先设置串口名字和波特率
bool SPCcom::open()
{
    if(m_serialPort->isOpen())
    {
        return true;
    }
    m_serialPort->setPortName(m_portName);
    m_serialPort->setBaudRate(getBaudRate(m_baudRate));
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort->setReadBufferSize(1024);
    bool read = m_serialPort->open(QSerialPort::ReadWrite);
    // 绑定串口中断信号和中断处理函数
    connect(m_serialPort,  SIGNAL(readyRead()),  this,  SLOT(onReadyRead()));
    return  read;
 }

 // 串口处理函数
void SPCcom::onReadyRead()
{
    QByteArray arr;
   arr = m_serialPort->readAll();   // 读取串口全部数据
   emit send(arr);    // 发送显示信号
    qDebug()<<arr;
}


void SPCcom::close()
{
    if(m_serialPort->isOpen())
    {
        m_serialPort->close();
    }
}

// 重启串口，清除数据
bool SPCcom::clear()
{
    if(m_serialPort->isOpen())
    {
        m_serialPort->clear();
        this->close();
        return this->open();
    }
    return false;
}

// 接收串口发来的数据
int SPCcom::readData(char *buffer, int count,int timeout)
{
    int len = 0;
    forever
    {
        int n = m_serialPort->read(&buffer[len],count - len);

        if(n == -1)
        {

            return -1;
        }
        else if(n == 0 && !m_serialPort->waitForReadyRead(timeout))
        {
            return -2;
        }
        else
        {
            len += n;
            if(count == len)
                break;
        }
    }
    return len;
}

// 发送数据到串口
int SPCcom::writeData(char *data, int size)
{
    int len = 0;
    forever
    {
        int n = m_serialPort->write(&data[len], size - len);
        if(n == -1)
        {
            return -1;
        }
        else
        {
            len += n;
            if(size == len)
                break;
        }
    }
    return len;
}


SPCcom::~SPCcom()
{
    delete m_serialPort;
}


