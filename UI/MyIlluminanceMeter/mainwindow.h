#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QLineSeries>
#include <cmath>

#include "arduinoconnector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLineSeries * voltageSerie;
    QLineSeries * luxSerie;
    QChart * voltageChart;
    QChart * luxChart;
    QChartView * voltageChartView;
    QChartView * luxChartView;
    ArduinoConnector arduinoConnector;
    long pointCount = 0;

    int ADC_MAX_VALUE = 1023;
    int MIN_VOLTAGE = 0;
    int MAX_VOLTAGE = 5;
    int MIN_LUX = 0;
    int MAX_LUX = 7000;

    void initVoltageChart();
    void initLuxChart();
    void convertValueReceived(double);
    void addPointToSeries(double, double);
    void updateSeries();
    void fillUSBCombobox();
    void fillBaudrateCombobox();
    void fillPrescalerCombobox();
    void fillPortCombobox();

private slots:
    void startListenning();
    void stopListenning();
    void clearChart();
    void handleSerialEvent();

};
#endif // MAINWINDOW_H
