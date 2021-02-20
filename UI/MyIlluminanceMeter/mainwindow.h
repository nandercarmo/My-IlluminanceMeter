#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
 #include <QXYSeries>
#include <QLineSeries>
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
    QLineSeries * series;
    QChart * chart;
    QChartView * chartView;
    ArduinoConnector arduinoConnector;
    long pointCount = 0;

    void initChart();
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
