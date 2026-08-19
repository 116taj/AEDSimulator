/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "aed.h"
#include "ecg.h"
#include "lcdscreen.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *healtyButton;
    QPushButton *vFibButton;
    QPushButton *vTachButton;
    QPushButton *asysotleButton;
    QPushButton *peaButton;
    QPushButton *rechargeButton;
    QPushButton *cprButton;
    QSlider *depthSlider;
    QLabel *depthLabel;
    QLabel *patientInfo;
    QLabel *ageLabel;
    QPushButton *childButton;
    QPushButton *adultButton;
    QSpinBox *ageInput;
    QLabel *depthMin;
    QLabel *depthMax;
    QComboBox *electrodes;
    QLabel *electrodeLabel;
    QLabel *failLabel;
    QComboBox *fail;
    QPushButton *breatheButton;
    Aed *aed;
    QProgressBar *batteryNumber;
    QLabel *batteryLabel;
    QPushButton *powerButton;
    QPushButton *shockButton;
    LCDScreen *lcdScreen;
    Ecg *ecgWidget;
    QLabel *selfTest;
    QLabel *led;
    QLabel *led_2;
    QLabel *led_3;
    QLabel *led_4;
    QLabel *led_5;
    QLabel *led_6;
    QLabel *audioPrompt;
    QLabel *aedGraphic;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1004, 809);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        healtyButton = new QPushButton(centralwidget);
        healtyButton->setObjectName(QString::fromUtf8("healtyButton"));
        healtyButton->setGeometry(QRect(190, 50, 111, 41));
        vFibButton = new QPushButton(centralwidget);
        vFibButton->setObjectName(QString::fromUtf8("vFibButton"));
        vFibButton->setGeometry(QRect(320, 50, 111, 41));
        vTachButton = new QPushButton(centralwidget);
        vTachButton->setObjectName(QString::fromUtf8("vTachButton"));
        vTachButton->setGeometry(QRect(450, 50, 111, 41));
        asysotleButton = new QPushButton(centralwidget);
        asysotleButton->setObjectName(QString::fromUtf8("asysotleButton"));
        asysotleButton->setGeometry(QRect(580, 50, 111, 41));
        peaButton = new QPushButton(centralwidget);
        peaButton->setObjectName(QString::fromUtf8("peaButton"));
        peaButton->setGeometry(QRect(710, 50, 111, 41));
        rechargeButton = new QPushButton(centralwidget);
        rechargeButton->setObjectName(QString::fromUtf8("rechargeButton"));
        rechargeButton->setGeometry(QRect(860, 160, 121, 25));
        cprButton = new QPushButton(centralwidget);
        cprButton->setObjectName(QString::fromUtf8("cprButton"));
        cprButton->setEnabled(false);
        cprButton->setGeometry(QRect(10, 170, 83, 25));
        depthSlider = new QSlider(centralwidget);
        depthSlider->setObjectName(QString::fromUtf8("depthSlider"));
        depthSlider->setEnabled(false);
        depthSlider->setGeometry(QRect(10, 200, 141, 16));
        depthSlider->setMaximum(24);
        depthSlider->setOrientation(Qt::Horizontal);
        depthLabel = new QLabel(centralwidget);
        depthLabel->setObjectName(QString::fromUtf8("depthLabel"));
        depthLabel->setGeometry(QRect(100, 170, 71, 20));
        depthLabel->setAlignment(Qt::AlignCenter);
        patientInfo = new QLabel(centralwidget);
        patientInfo->setObjectName(QString::fromUtf8("patientInfo"));
        patientInfo->setGeometry(QRect(0, 324, 151, 21));
        patientInfo->setAlignment(Qt::AlignCenter);
        ageLabel = new QLabel(centralwidget);
        ageLabel->setObjectName(QString::fromUtf8("ageLabel"));
        ageLabel->setGeometry(QRect(20, 354, 41, 21));
        ageLabel->setAlignment(Qt::AlignCenter);
        childButton = new QPushButton(centralwidget);
        childButton->setObjectName(QString::fromUtf8("childButton"));
        childButton->setEnabled(false);
        childButton->setGeometry(QRect(20, 404, 121, 25));
        childButton->setCheckable(false);
        adultButton = new QPushButton(centralwidget);
        adultButton->setObjectName(QString::fromUtf8("adultButton"));
        adultButton->setEnabled(false);
        adultButton->setGeometry(QRect(20, 434, 121, 25));
        ageInput = new QSpinBox(centralwidget);
        ageInput->setObjectName(QString::fromUtf8("ageInput"));
        ageInput->setGeometry(QRect(70, 354, 45, 26));
        depthMin = new QLabel(centralwidget);
        depthMin->setObjectName(QString::fromUtf8("depthMin"));
        depthMin->setGeometry(QRect(10, 210, 16, 17));
        depthMax = new QLabel(centralwidget);
        depthMax->setObjectName(QString::fromUtf8("depthMax"));
        depthMax->setGeometry(QRect(140, 210, 21, 17));
        electrodes = new QComboBox(centralwidget);
        electrodes->addItem(QString());
        electrodes->addItem(QString());
        electrodes->setObjectName(QString::fromUtf8("electrodes"));
        electrodes->setGeometry(QRect(100, 284, 61, 25));
        electrodeLabel = new QLabel(centralwidget);
        electrodeLabel->setObjectName(QString::fromUtf8("electrodeLabel"));
        electrodeLabel->setGeometry(QRect(20, 280, 71, 31));
        electrodeLabel->setWordWrap(true);
        failLabel = new QLabel(centralwidget);
        failLabel->setObjectName(QString::fromUtf8("failLabel"));
        failLabel->setGeometry(QRect(10, 550, 71, 31));
        failLabel->setWordWrap(true);
        fail = new QComboBox(centralwidget);
        fail->addItem(QString());
        fail->addItem(QString());
        fail->setObjectName(QString::fromUtf8("fail"));
        fail->setGeometry(QRect(90, 550, 61, 25));
        breatheButton = new QPushButton(centralwidget);
        breatheButton->setObjectName(QString::fromUtf8("breatheButton"));
        breatheButton->setEnabled(false);
        breatheButton->setGeometry(QRect(20, 240, 141, 25));
        aed = new Aed(centralwidget);
        aed->setObjectName(QString::fromUtf8("aed"));
        aed->setGeometry(QRect(170, 100, 671, 661));
        batteryNumber = new QProgressBar(aed);
        batteryNumber->setObjectName(QString::fromUtf8("batteryNumber"));
        batteryNumber->setGeometry(QRect(500, 50, 131, 31));
        batteryNumber->setValue(2);
        batteryNumber->setTextVisible(true);
        batteryLabel = new QLabel(aed);
        batteryLabel->setObjectName(QString::fromUtf8("batteryLabel"));
        batteryLabel->setGeometry(QRect(520, 10, 121, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans"));
        font.setPointSize(14);
        batteryLabel->setFont(font);
        powerButton = new QPushButton(aed);
        powerButton->setObjectName(QString::fromUtf8("powerButton"));
        powerButton->setGeometry(QRect(40, 30, 80, 80));
        powerButton->setAutoFillBackground(false);
        powerButton->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.1, cy:0.1, radius:0.1, fx:0.1, fy:0.1, stop:0 rgba(0, 0, 0, 0));"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("off-button-power-button.svg"), QSize(), QIcon::Normal, QIcon::Off);
        powerButton->setIcon(icon);
        powerButton->setIconSize(QSize(80, 80));
        shockButton = new QPushButton(aed);
        shockButton->setObjectName(QString::fromUtf8("shockButton"));
        shockButton->setGeometry(QRect(290, 190, 91, 91));
        shockButton->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.1, cy:0.1, radius:0.1, fx:0.1, fy:0.1, stop:0 rgba(0, 0, 0, 0));"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("heart shock.png"), QSize(), QIcon::Normal, QIcon::Off);
        shockButton->setIcon(icon1);
        shockButton->setIconSize(QSize(90, 90));
        lcdScreen = new LCDScreen(aed);
        lcdScreen->setObjectName(QString::fromUtf8("lcdScreen"));
        lcdScreen->setGeometry(QRect(390, 190, 260, 160));
        ecgWidget = new Ecg(aed);
        ecgWidget->setObjectName(QString::fromUtf8("ecgWidget"));
        ecgWidget->setGeometry(QRect(20, 190, 261, 161));
        selfTest = new QLabel(aed);
        selfTest->setObjectName(QString::fromUtf8("selfTest"));
        selfTest->setGeometry(QRect(30, 380, 71, 41));
        selfTest->setPixmap(QPixmap(QString::fromUtf8("selfTestDefault.png")));
        led = new QLabel(aed);
        led->setObjectName(QString::fromUtf8("led"));
        led->setGeometry(QRect(92, 510, 16, 17));
        led->setPixmap(QPixmap(QString::fromUtf8("red.png")));
        led->setAlignment(Qt::AlignCenter);
        led_2 = new QLabel(aed);
        led_2->setObjectName(QString::fromUtf8("led_2"));
        led_2->setGeometry(QRect(133, 508, 16, 17));
        led_2->setPixmap(QPixmap(QString::fromUtf8("red.png")));
        led_2->setAlignment(Qt::AlignCenter);
        led_3 = new QLabel(aed);
        led_3->setObjectName(QString::fromUtf8("led_3"));
        led_3->setEnabled(true);
        led_3->setGeometry(QRect(230, 510, 16, 17));
        led_3->setPixmap(QPixmap(QString::fromUtf8("red.png")));
        led_3->setAlignment(Qt::AlignCenter);
        led_4 = new QLabel(aed);
        led_4->setObjectName(QString::fromUtf8("led_4"));
        led_4->setGeometry(QRect(395, 442, 16, 17));
        led_4->setPixmap(QPixmap(QString::fromUtf8("red.png")));
        led_4->setAlignment(Qt::AlignCenter);
        led_5 = new QLabel(aed);
        led_5->setObjectName(QString::fromUtf8("led_5"));
        led_5->setGeometry(QRect(450, 438, 16, 17));
        led_5->setPixmap(QPixmap(QString::fromUtf8("red.png")));
        led_5->setAlignment(Qt::AlignCenter);
        led_6 = new QLabel(aed);
        led_6->setObjectName(QString::fromUtf8("led_6"));
        led_6->setGeometry(QRect(643, 510, 16, 17));
        led_6->setPixmap(QPixmap(QString::fromUtf8("red.png")));
        led_6->setAlignment(Qt::AlignCenter);
        audioPrompt = new QLabel(aed);
        audioPrompt->setObjectName(QString::fromUtf8("audioPrompt"));
        audioPrompt->setGeometry(QRect(20, 610, 641, 41));
        audioPrompt->setStyleSheet(QString::fromUtf8("font: 14pt \"DejaVu Sans\";\n"
"background-color: rgb(255, 255, 255);"));
        audioPrompt->setAlignment(Qt::AlignCenter);
        aedGraphic = new QLabel(aed);
        aedGraphic->setObjectName(QString::fromUtf8("aedGraphic"));
        aedGraphic->setGeometry(QRect(0, 0, 671, 601));
        aedGraphic->setPixmap(QPixmap(QString::fromUtf8("AED picture.png")));
        aedGraphic->setScaledContents(true);
        aedGraphic->raise();
        batteryNumber->raise();
        batteryLabel->raise();
        powerButton->raise();
        shockButton->raise();
        lcdScreen->raise();
        ecgWidget->raise();
        selfTest->raise();
        led->raise();
        led_2->raise();
        led_3->raise();
        led_4->raise();
        led_5->raise();
        led_6->raise();
        audioPrompt->raise();
        MainWindow->setCentralWidget(centralwidget);
        aed->raise();
        healtyButton->raise();
        vFibButton->raise();
        vTachButton->raise();
        asysotleButton->raise();
        peaButton->raise();
        rechargeButton->raise();
        cprButton->raise();
        depthSlider->raise();
        depthLabel->raise();
        patientInfo->raise();
        ageLabel->raise();
        childButton->raise();
        adultButton->raise();
        ageInput->raise();
        depthMin->raise();
        depthMax->raise();
        electrodes->raise();
        electrodeLabel->raise();
        failLabel->raise();
        fail->raise();
        breatheButton->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1004, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        healtyButton->setText(QCoreApplication::translate("MainWindow", "Healthy", nullptr));
        vFibButton->setText(QCoreApplication::translate("MainWindow", "vFib", nullptr));
        vTachButton->setText(QCoreApplication::translate("MainWindow", "vTach", nullptr));
        asysotleButton->setText(QCoreApplication::translate("MainWindow", "Asysotle", nullptr));
        peaButton->setText(QCoreApplication::translate("MainWindow", "PEA", nullptr));
        rechargeButton->setText(QCoreApplication::translate("MainWindow", "Replace Battery", nullptr));
        cprButton->setText(QCoreApplication::translate("MainWindow", "Begin CPR", nullptr));
        depthLabel->setText(QCoreApplication::translate("MainWindow", "Depth: 0", nullptr));
        patientInfo->setText(QCoreApplication::translate("MainWindow", "Patient Information", nullptr));
        ageLabel->setText(QCoreApplication::translate("MainWindow", "Age:", nullptr));
        childButton->setText(QCoreApplication::translate("MainWindow", "Place Child Pads", nullptr));
#if QT_CONFIG(statustip)
        adultButton->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        adultButton->setText(QCoreApplication::translate("MainWindow", "Place Adult Pads", nullptr));
        depthMin->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        depthMax->setText(QCoreApplication::translate("MainWindow", "2.4", nullptr));
        electrodes->setItemText(0, QCoreApplication::translate("MainWindow", "No", nullptr));
        electrodes->setItemText(1, QCoreApplication::translate("MainWindow", "Yes", nullptr));

        electrodeLabel->setText(QCoreApplication::translate("MainWindow", "Electrodes Connected", nullptr));
        failLabel->setText(QCoreApplication::translate("MainWindow", "Force Self Test Fail", nullptr));
        fail->setItemText(0, QCoreApplication::translate("MainWindow", "No", nullptr));
        fail->setItemText(1, QCoreApplication::translate("MainWindow", "Yes", nullptr));

        breatheButton->setText(QCoreApplication::translate("MainWindow", "Breathe Into Patient", nullptr));
        batteryLabel->setText(QCoreApplication::translate("MainWindow", "BATTERY: ", nullptr));
        powerButton->setText(QString());
        shockButton->setText(QString());
        selfTest->setText(QString());
        led->setText(QString());
        led_2->setText(QString());
        led_3->setText(QString());
        led_4->setText(QString());
        led_5->setText(QString());
        led_6->setText(QString());
        audioPrompt->setText(QCoreApplication::translate("MainWindow", "No audio is currently playing.", nullptr));
        aedGraphic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
