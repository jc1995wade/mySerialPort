#ifndef SPCCOM_H
#define SPCCOM_H

#include <QObject>
#include "QtSerialPort/QSerialPort"  // 串口头文件
#include <QSerialPortInfo>
#include <signal.h>
#include <qstringlist.h>
#include <qt_windows.h>
#include <QSettings>

class SPCcom:public QObject
{
    Q_OBJECT
public:
    explicit SPCcom(QObject *parent = 0);
    ~SPCcom();
    QSerialPort *m_serialPort;
   QStringList m_listcomboName;
   QString m_portName;
   int m_baudRate;
   int m_parity;
   int m_dataBits;
   int m_stopBits;
   int m_flowControl;


    //声明串口功能
    bool isOpen() const;

    void setPortName(const QString &name);
    QString portName() const;

    void setBaudRate(int baudRate);
    int baudRate() const;

    virtual bool open();
    virtual void close();
    virtual bool clear();

    int readData(char *buffer, int count, int timeout=1000);
    int writeData(char *data, int size);
    int write(char ch);

    void connect_read();

    // 读取键名
    QString getcomm(int index, QString keyorvalue);
protected:


private:

    HKEY hKey;
    LPCWSTR subkey;
    wchar_t keyname[256];  // 键名数组
    char keyvalue[256];   // 键值数组
    DWORD keysize, type, valuesize;
    int indexnum;

signals:
    void send(QByteArray);

public slots:
    void onReadyRead();
};

#endif // SPCCOM_H
