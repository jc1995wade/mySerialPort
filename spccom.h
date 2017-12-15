#ifndef SPCCOM_H
#define SPCCOM_H

#include <QObject>
#include "QtSerialPort/QSerialPort"  // 串口头文件
#include <QSerialPortInfo>
#include <signal.h>
class SPCcom:public QObject
{
    Q_OBJECT
public:

    explicit SPCcom(QObject *parent = 0);
  //  explicit SPCcom(void (MainWindow::*f)(const QString));
    ~SPCcom();
    QSerialPort *m_serialPort;

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
protected:
    QString m_portName;
    int m_baudRate;


signals:
    void send(QByteArray);

public slots:
    void onReadyRead();
};

#endif // SPCCOM_H
