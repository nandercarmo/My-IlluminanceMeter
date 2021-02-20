#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(size());

    this->fillUSBCombobox();
    this->fillBaudrateCombobox();
    this->fillPrescalerCombobox();
    this->fillPortCombobox();

    this->initChart();

    QLayoutItem * previousWidget = ui->horizontalLayout->replaceWidget(ui->chartWidget, this->chartView);
    delete previousWidget;

    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::startListenning);
    connect(ui->pushButtonStop, &QPushButton::clicked, this, &MainWindow::stopListenning);
    connect(ui->pushButtonClear, &QPushButton::clicked, this, &MainWindow::clearChart);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startListenning() {

    qDebug() << "Start";

    if(!this->arduinoConnector.isConnected) {

        QString portName = ui->comboBoxUSB->currentData().toString();
        QString baudRate = ui->comboBoxBaudrate->currentData().toString();

        this->arduinoConnector.setSerialParameters(portName, baudRate);

        QString error = this->arduinoConnector.connectArduino();

        if(error.isNull()) {

            qDebug() << "Conexão USB aberta!";
            this->arduinoConnector.isConnected = true;

        } else {

            qDebug() << "Erro tentando abrir conexão: " << error;
            this->arduinoConnector.isConnected = false;
        }
    }

    if(arduinoConnector.isConnected) {

        clearChart();

        QChar prescaler = ui->comboBoxPrescaler->currentData().toChar();
        QChar port = ui->comboBoxPort->currentData().toChar();

        this->arduinoConnector.sendData(char(this->arduinoConnector.START_READ));
        this->arduinoConnector.sendData(prescaler.toLatin1());
        this->arduinoConnector.sendData(port.toLatin1());
    }

    connect(this->arduinoConnector.serial, &QSerialPort::readyRead, this, &MainWindow::handleSerialEvent);
}

void MainWindow::stopListenning() {

    qDebug() << "Stop";

    disconnect(this->arduinoConnector.serial, &QSerialPort::readyRead, this, &MainWindow::handleSerialEvent);

    this->arduinoConnector.sendData(char(this->arduinoConnector.STOP_READ));
}

void MainWindow::handleSerialEvent() {

    QByteArray data = this->arduinoConnector.readData();

    if(!data.isEmpty()) {

        qDebug() << "Int:" << data.toInt();

        this->chart->removeSeries(this->series);
        this->series->append(this->pointCount + 1, data.toInt());
        if(this->series->count() > 200) this->series->remove(0);
        this->chart->addSeries(this->series);
        this->chart->createDefaultAxes();
        this->chart->axes(Qt::Vertical, this->series).back()->setRange(0, 500);
        this->chart->axes(Qt::Vertical, this->series).back()->setTitleText("Passo do ADC 0 ~ 1023");
        this->chart->axes(Qt::Horizontal, this->series).back()->setTitleText("Amostras");

        this->pointCount++;

    } else qDebug() << "Erro recebendo dados da USB";
}

void MainWindow::initChart() {

    this->series = new QLineSeries();

    this->chart = new QChart();
    this->chart->addSeries(series);
    this->chart->setTitle("Iluminância x Tempo");
    this->chart->legend()->hide();
    this->chart->createDefaultAxes();
    this->chart->axes(Qt::Vertical, this->series).back()->setRange(0, 500);
    this->chart->axes(Qt::Vertical, this->series).back()->setTitleText("Passo do ADC 0 ~ 1023");
    this->chart->axes(Qt::Horizontal, this->series).back()->setTitleText("Amostras");

    QFont font;
    font.setBold(true);
    font.setPixelSize(16);
    this->chart->setTitleFont(font);

    this->chartView = new QChartView(chart);
    this->chartView->setRenderHint(QPainter::Antialiasing);
    this->chartView->setStyleSheet("background-color: #e0e0e5;");
}

void MainWindow::clearChart() {

    qDebug() << "Clear";

    this->pointCount = 0;

    this->chart->removeSeries(this->series);
    this->series->clear();
    this->chart->addSeries(this->series);
}

void MainWindow::fillUSBCombobox() {

    ui->comboBoxUSB->clear();
    for(const auto &info : this->arduinoConnector.availablePorts) {

        QString portname = info.portName();
        QString description = (!info.description().isEmpty() ? info.description() : "N/A");
        QString item = portname + "(" + description + ")";

        ui->comboBoxUSB->addItem(item, portname);
    }
}

void MainWindow::fillBaudrateCombobox() {

    ui->comboBoxBaudrate->clear();
    ui->comboBoxBaudrate->addItem("19200", "19200");
    ui->comboBoxBaudrate->addItem("9600", "9600");
    ui->comboBoxBaudrate->addItem("4800", "4800");
    ui->comboBoxBaudrate->addItem("2400", "2400");
    ui->comboBoxBaudrate->addItem("1200", "1200");
}

void MainWindow::fillPrescalerCombobox() {

    uint8_t prescaler128 = 0x07;
    uint8_t prescaler64 = 0x06;
    uint8_t prescaler32 = 0x05;
    uint8_t prescaler16 = 0x04;
    uint8_t prescaler8 = 0x03;
    uint8_t prescaler4 = 0x02;
    uint8_t prescaler2 = 0x01;

    double freq128 = 16E6 / (13 * 128);
    double freq64 = 16E6 / (13 * 64);
    double freq32 = 16E6 / (13 * 32);
    double freq16 = 16E6 / (13 * 16);
    double freq8 = 16E6 / (13 * 8);
    double freq4 = 16E6 / (13 * 4);
    double freq2 = 16E6 / (13 * 2);

    ui->comboBoxPrescaler->clear();
    ui->comboBoxPrescaler->addItem("128      [  fs = " + QString::number(freq128, 'E', 3) + " Hz  ]", prescaler128);
    ui->comboBoxPrescaler->addItem("64        [  fs = " + QString::number(freq64, 'E', 3) + " Hz  ]", prescaler64);
    ui->comboBoxPrescaler->addItem("32        [  fs = " + QString::number(freq32, 'E', 3) + " Hz  ]", prescaler32);
    ui->comboBoxPrescaler->addItem("16        [  fs = " + QString::number(freq16, 'E', 3) + " Hz  ]", prescaler16);
    ui->comboBoxPrescaler->addItem("8          [  fs = " + QString::number(freq8, 'E', 3) + " Hz  ]", prescaler8);
    ui->comboBoxPrescaler->addItem("4          [  fs = " + QString::number(freq4, 'E', 3) + " Hz  ]", prescaler4);
    ui->comboBoxPrescaler->addItem("2          [  fs = " + QString::number(freq2, 'E', 3) + " Hz  ]", prescaler2);
}

void MainWindow::fillPortCombobox() {

    uint8_t portA0 = 0x00;
    uint8_t portA1 = 0x01;
    uint8_t portA2 = 0x02;
    uint8_t portA3 = 0x03;
    uint8_t portA4 = 0x04;
    uint8_t portA5 = 0x05;
    uint8_t portA6 = 0x06;
    uint8_t portA7 = 0x07;

    ui->comboBoxPort->clear();
    ui->comboBoxPort->addItem("Porta A0", portA0);
    ui->comboBoxPort->addItem("Porta A1", portA1);
    ui->comboBoxPort->addItem("Porta A2", portA2);
    ui->comboBoxPort->addItem("Porta A3", portA3);
    ui->comboBoxPort->addItem("Porta A4", portA4);
    ui->comboBoxPort->addItem("Porta A5", portA5);
    ui->comboBoxPort->addItem("Porta A6", portA6);
    ui->comboBoxPort->addItem("Porta A7", portA7);
}

