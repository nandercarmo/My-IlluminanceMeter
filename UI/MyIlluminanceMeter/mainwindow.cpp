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

    this->initVoltageChart();
    this->initLuxChart();

    QLayoutItem * previousWidget = ui->horizontalLayout->replaceWidget(ui->chartVoltageWidget, this->voltageChartView);
    delete previousWidget;

    previousWidget = ui->horizontalLayout->replaceWidget(ui->chartLuxWidget, this->luxChartView);
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

            this->startListenning();

        } else {

            qDebug() << "Erro tentando abrir conexão: " << error;
            this->arduinoConnector.isConnected = false;
        }

    } else {

        clearChart();

        QChar prescaler = ui->comboBoxPrescaler->currentData().toChar();
        QChar port = ui->comboBoxPort->currentData().toChar();

        this->arduinoConnector.sendData(char(this->arduinoConnector.START_READ));
        this->arduinoConnector.sendData(prescaler.toLatin1());
        this->arduinoConnector.sendData(port.toLatin1());

        connect(this->arduinoConnector.serial, &QSerialPort::readyRead, this, &MainWindow::handleSerialEvent);
    }
}

void MainWindow::stopListenning() {

    qDebug() << "Stop";

    disconnect(this->arduinoConnector.serial, &QSerialPort::readyRead, this, &MainWindow::handleSerialEvent);

    this->arduinoConnector.sendData(char(this->arduinoConnector.STOP_READ));
}

void MainWindow::handleSerialEvent() {

    this->voltageChart->removeSeries(this->voltageSerie);
    this->luxChart->removeSeries(this->luxSerie);

    while(this->arduinoConnector.bytesAvailable()) {

        if(this->arduinoConnector.receivedNewData()) {

            QByteArray data = this->arduinoConnector.readData();

            if(!data.isEmpty()) this->convertValueReceived(1.0 * data.toInt());
            else qDebug() << "Erro recebendo dados da USB";
        }
    }

    this->updateSeries();
}

void MainWindow::initVoltageChart() {

    this->voltageSerie = new QLineSeries();

    this->voltageChart = new QChart();
    this->voltageChart->addSeries(this->voltageSerie);
    this->voltageChart->setTitle("Variação da Tensão  [ V ]");
    this->voltageChart->legend()->hide();
    this->voltageChart->createDefaultAxes();
    this->voltageChart->axes(Qt::Vertical, this->voltageSerie).back()->setRange(this->MIN_VOLTAGE, this->MAX_VOLTAGE);
    this->voltageChart->axes(Qt::Horizontal, this->voltageSerie).back()->setTitleText("Amostras");
    this->voltageChart->setTheme(QChart::ChartThemeDark);

    QFont font;
    font.setBold(true);
    font.setPixelSize(16);
    this->voltageChart->setTitleFont(font);

    this->voltageChartView = new QChartView(this->voltageChart);
    this->voltageChartView->setRenderHint(QPainter::Antialiasing);
    this->voltageChartView->setStyleSheet("background-color: #e0e0e5;");
}

void MainWindow::initLuxChart() {

    this->luxSerie = new QLineSeries();

    this->luxChart = new QChart();
    this->luxChart->addSeries(this->luxSerie);
    this->luxChart->setTitle("Variação da Iluminância  [ lx ]");
    this->luxChart->legend()->hide();
    this->luxChart->createDefaultAxes();
    this->luxChart->axes(Qt::Vertical, this->luxSerie).back()->setRange(this->MIN_LUX, this->MAX_LUX);
    this->luxChart->axes(Qt::Horizontal, this->luxSerie).back()->setTitleText("Amostras");
    this->luxChart->setTheme(QChart::ChartThemeDark);

    QFont font;
    font.setBold(true);
    font.setPixelSize(16);
    this->luxChart->setTitleFont(font);

    this->luxChartView = new QChartView(this->luxChart);
    this->luxChartView->setRenderHint(QPainter::Antialiasing);
    this->luxChartView->setStyleSheet("background-color: #e0e0e5;");
}

void MainWindow::clearChart() {

    qDebug() << "Clear";

    this->pointCount = 0;

    this->voltageChart->removeSeries(this->voltageSerie);
    this->voltageSerie->clear();
    this->voltageChart->addSeries(this->voltageSerie);

    this->luxChart->removeSeries(this->luxSerie);
    this->luxSerie->clear();
    this->luxChart->addSeries(this->luxSerie);
}

void MainWindow::convertValueReceived(double newValue) {

    double voltageValue;
    voltageValue = newValue / this->ADC_MAX_VALUE;
    voltageValue *= this->MAX_VOLTAGE;

    double luxValue = 0.0;
    luxValue -= 9.2017399997558357E1 * pow(voltageValue * 1000.0, 0.0);
    luxValue += 5.6925744486746090E0 * pow(voltageValue * 1000.0, 1.0);
    luxValue -= 7.3489975622013995E-3 * pow(voltageValue * 1000.0, 2.0);
    luxValue += 6.1085988832089932E-6 * pow(voltageValue * 1000.0, 3.0);
    luxValue -= 2.3966391086544928E-9 * pow(voltageValue * 1000.0, 4.0);
    luxValue += 3.7174706249698862E-13 * pow(voltageValue * 1000.0, 5.0);

    qDebug() << "Bits:" << newValue;
    qDebug() << "Voltage:" << voltageValue;
    qDebug() << "Lux:" << luxValue;

    this->addPointToSeries(voltageValue, luxValue);

    this->pointCount++;
}

void MainWindow::addPointToSeries(double newVoltageValue, double newLuxValue) {

    this->voltageSerie->append(this->pointCount + 1, newVoltageValue);
    if(this->voltageSerie->count() > 1000) this->voltageSerie->remove(0);

    this->luxSerie->append(this->pointCount + 1, newLuxValue);
    if(this->luxSerie->count() > 1000) this->luxSerie->remove(0);
}

void MainWindow::updateSeries() {

    this->voltageChart->addSeries(this->voltageSerie);
    this->voltageChart->createDefaultAxes();
    this->voltageChart->axes(Qt::Vertical, this->voltageSerie).back()->setRange(this->MIN_VOLTAGE, this->MAX_VOLTAGE);
    this->voltageChart->axes(Qt::Horizontal, this->voltageSerie).back()->setTitleText("Amostras");

    this->luxChart->addSeries(this->luxSerie);
    this->luxChart->createDefaultAxes();
    this->luxChart->axes(Qt::Vertical, this->luxSerie).back()->setRange(this->MIN_LUX, this->MAX_LUX);
    this->luxChart->axes(Qt::Horizontal, this->luxSerie).back()->setTitleText("Amostras");
}

void MainWindow::fillUSBCombobox() {

    ui->comboBoxUSB->clear();
    for(const auto &info : this->arduinoConnector.availablePorts) {

        QString portname = info.portName();
        QString description = (!info.description().isEmpty() ? info.description() : "N/A");
        QString item = portname + " (" + description + ")";

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

