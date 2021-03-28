#ifndef ARDUINOCONNECTOR_H
#define ARDUINOCONNECTOR_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class ArduinoConnector : public QObject {

    Q_OBJECT

public:
    explicit ArduinoConnector(QObject * parent = nullptr);
    QString connectArduino();
    void disconnectArduino();
    void setSerialParameters(QString portName, QString baudRate);
    void sendData(char data);
    QByteArray readData();
    void getAvailablePorts();
    qint64 bytesAvailable();
    bool receivedNewData();

    QList<QSerialPortInfo> availablePorts;
    QSerialPort * serial;
    bool isConnected;
    bool validStream;

    const uint8_t STOP_READ = 0x7F;
    const uint8_t START_READ = 0x80;

    struct SerialParameters {
        QString name;
        qint32 baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
    };

private:
    SerialParameters serialParameters;
    QByteArray dataReceived;
};


#endif // ARDUINOCONNECTOR_H
