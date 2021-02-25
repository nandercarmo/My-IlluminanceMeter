/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *chartWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *comboBoxUSB;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QComboBox *comboBoxBaudrate;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QComboBox *comboBoxPrescaler;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QComboBox *comboBoxPort;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonClear;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 640);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"* {\n"
"	background-color: #e0e0e5;\n"
"	font-weight: bold;\n"
"}\n"
"\n"
"#MainWindow {\n"
"}\n"
"\n"
"QPushButton {\n"
"	color: #404042;	\n"
"	background-color: #fff;\n"
"	font-weight: bold;\n"
"	border-radius: 7px;	\n"
"	border: 2px solid #bbb;\n"
"	padding-top: 7px;\n"
"	padding-bottom: 7px;\n"
"	padding-left: 14px;\n"
"	padding-right: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {	\n"
"	background-color: #eeeeef;\n"
"}\n"
"\n"
"QCheckBox:indicator {\n"
"	width: 14px;\n"
"	height:14px;\n"
"}\n"
"\n"
"QLabel {\n"
"	color: #404042;\n"
"}\n"
"\n"
"QComboBox {\n"
"	background-color: #fefefe;	\n"
"	color: #6f707a;\n"
"	font-weight: bold;\n"
"	border-radius: 7px;	\n"
"	border: 2px solid #bbb;\n"
"	padding-top: 7px;\n"
"	padding-bottom: 7px;\n"
"	padding-left: 14px;\n"
"	padding-right: 14px;\n"
"}\n"
"\n"
"QComboBox:editable {\n"
"	background-color: #fefefe;	\n"
"	margin: 5px;\n"
"	border: 2px solid #bbb;\n"
"	border-radius: 7px;	\n"
"}\n"
"\n"
"QComboBox:item {\n"
"	background-color: #fefefe;\n"
"}\n"
"\n"
"QComb"
                        "oBox:item:selected {\n"
"    padding-left: 5px;\n"
"	background-color: #e0e0e5;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"	background-color: #fefefe;	\n"
"	subcontrol-origin: padding;\n"
"	subcontrol-position: top right;\n"
"	width: 12px;\n"
"	\n"
"	border-left: 0px solid #bbb;\n"
"	border-radius: 7px;	\n"
"	border-top-right-radius: 7px;\n"
"	border-bottom-right-radius: 7px;\n"
"	padding-right: 7px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	image: url(:/images/drop_dow_arrow_16px.png);\n"
"}\n"
"\n"
"QComboBox::down-arrow:on {\n"
"	top: 1px;\n"
"	left: 1px;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 1001, 641));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        horizontalLayout->setContentsMargins(10, 10, 10, 10);
        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        chartWidget = new QWidget(horizontalLayoutWidget);
        chartWidget->setObjectName(QString::fromUtf8("chartWidget"));

        horizontalLayout->addWidget(chartWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(7);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_2->setContentsMargins(10, 20, 10, 20);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(275, 16777215));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	margin-left: 5px;\n"
"}"));
        label->setMargin(0);

        verticalLayout->addWidget(label);

        comboBoxUSB = new QComboBox(horizontalLayoutWidget);
        comboBoxUSB->setObjectName(QString::fromUtf8("comboBoxUSB"));
        comboBoxUSB->setMinimumSize(QSize(0, 50));
        comboBoxUSB->setMaximumSize(QSize(275, 16777215));
        comboBoxUSB->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(comboBoxUSB);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(275, 16777215));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	margin-top:  10px;\n"
"	margin-left: 5px;\n"
"}"));
        label_2->setMargin(2);

        verticalLayout_4->addWidget(label_2);

        comboBoxBaudrate = new QComboBox(horizontalLayoutWidget);
        comboBoxBaudrate->setObjectName(QString::fromUtf8("comboBoxBaudrate"));
        comboBoxBaudrate->setMinimumSize(QSize(50, 50));
        comboBoxBaudrate->setMaximumSize(QSize(275, 16777215));

        verticalLayout_4->addWidget(comboBoxBaudrate);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(275, 16777215));
        label_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	margin-top:  10px;\n"
"	margin-left: 5px;\n"
"}"));
        label_3->setMargin(2);

        verticalLayout_5->addWidget(label_3);

        comboBoxPrescaler = new QComboBox(horizontalLayoutWidget);
        comboBoxPrescaler->setObjectName(QString::fromUtf8("comboBoxPrescaler"));
        comboBoxPrescaler->setMinimumSize(QSize(0, 50));
        comboBoxPrescaler->setMaximumSize(QSize(275, 16777215));

        verticalLayout_5->addWidget(comboBoxPrescaler);


        verticalLayout_4->addLayout(verticalLayout_5);


        verticalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(275, 16777215));
        label_4->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	margin-top:  10px;\n"
"	margin-left: 5px;\n"
"}r"));
        label_4->setMargin(2);

        verticalLayout_6->addWidget(label_4);

        comboBoxPort = new QComboBox(horizontalLayoutWidget);
        comboBoxPort->setObjectName(QString::fromUtf8("comboBoxPort"));
        comboBoxPort->setMinimumSize(QSize(275, 50));
        comboBoxPort->setMaximumSize(QSize(275, 16777215));

        verticalLayout_6->addWidget(comboBoxPort);


        verticalLayout_2->addLayout(verticalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        pushButtonStart = new QPushButton(horizontalLayoutWidget);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        pushButtonStart->setEnabled(true);
        pushButtonStart->setMinimumSize(QSize(275, 50));
        pushButtonStart->setMaximumSize(QSize(275, 16777215));
        pushButtonStart->setStyleSheet(QString::fromUtf8("/*\n"
"QPushButton:hover {	\n"
"	background-color: #c9ffd4;\n"
"}\n"
"*/"));

        verticalLayout_2->addWidget(pushButtonStart);

        pushButtonStop = new QPushButton(horizontalLayoutWidget);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setMinimumSize(QSize(275, 50));
        pushButtonStop->setMaximumSize(QSize(275, 16777215));
        pushButtonStop->setStyleSheet(QString::fromUtf8("/*\n"
"QPushButton:hover {	\n"
"	background-color: #ffc9d4;\n"
"}\n"
"*/"));

        verticalLayout_2->addWidget(pushButtonStop);

        pushButtonClear = new QPushButton(horizontalLayoutWidget);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));
        pushButtonClear->setMinimumSize(QSize(275, 50));
        pushButtonClear->setMaximumSize(QSize(275, 16777215));

        verticalLayout_2->addWidget(pushButtonClear);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "My Illuminance Meter UI", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Porta USB:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Baudrate:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Prescaler do Clock:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Porta Anal\303\263gica", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("MainWindow", "Come\303\247ar Leitura", nullptr));
        pushButtonStop->setText(QCoreApplication::translate("MainWindow", "Parar a Leitura", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("MainWindow", "Apagar Gr\303\241fico", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
