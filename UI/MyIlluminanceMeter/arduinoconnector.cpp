#include "arduinoconnector.h"

ArduinoConnector::ArduinoConnector(QObject * parent) :
    QObject(parent) {

    this->serial = new QSerialPort(this);
    this->isConnected =  false;
    this->getAvailablePorts();
}

void ArduinoConnector::getAvailablePorts() {
    this->availablePorts = QSerialPortInfo::availablePorts();
}

QString ArduinoConnector::connectArduino() {

    SerialParameters params = this->serialParameters;
    this->serial->setPortName(params.name);
    this->serial->setBaudRate(params.baudRate);
    this->serial->setDataBits(params.dataBits);
    this->serial->setParity(params.parity);
    this->serial->setStopBits(params.stopBits);
    this->serial->setFlowControl(params.flowControl);

    if (this->serial->open(QSerialPort::ReadWrite)) {

        this->isConnected = true;
        return nullptr;

    } else {

        this->isConnected = false;
        qDebug() << this->serial->errorString();
        return this->serial->errorString();
    }
}

void ArduinoConnector::disconnectArduino() {

    qDebug() << "Serial desconectada";

    if (this->serial->isOpen()) {

        this->serial->close();
        this->isConnected = false;
    }
}

void ArduinoConnector::setSerialParameters(QString portName, QString baudRate) {

    QSerialPort::BaudRate baud;

    if(baudRate == "19200") baud = QSerialPort::Baud19200;
    else if(baudRate == "9600") baud = QSerialPort::Baud9600;
    else if(baudRate == "4800") baud = QSerialPort::Baud4800;
    else if(baudRate == "2400") baud = QSerialPort::Baud2400;
    else baud = QSerialPort::Baud1200;

    this->serialParameters.name = portName;
    this->serialParameters.baudRate = baud;
    this->serialParameters.dataBits = QSerialPort::Data8;
    this->serialParameters.parity = QSerialPort::NoParity;
    this->serialParameters.stopBits = QSerialPort::OneStop;
    this->serialParameters.flowControl = QSerialPort::NoFlowControl;
}

void ArduinoConnector::sendData(char data) {

    this->serial->write(&data, sizeof (char));
}

qint64 ArduinoConnector::bytesAvailable(){
    qint64 bytesAvailable = this->serial->bytesAvailable();
    qDebug() << "Bytes:" << bytesAvailable;
    return bytesAvailable;
}

QByteArray ArduinoConnector::readData() {

    char data[20];

    this->serial->readLine(data, sizeof (data));
    //qDebug() << data.fromHex(data);
    QByteArray data2 = QByteArray(data);
    return data2;
}
