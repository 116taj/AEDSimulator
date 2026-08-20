#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "aed.h"

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
    //aed pointer to get aed
    Aed* aed;
    //timers
    QTimer* audioTimer;
    QTimer* cprCheckTimer;
    QTimer* cprTimer;
    QTimer* shockTimer;
    //prevAudio exists for program flow and for speaker functionality
    QString prevAudio;
    //this is also technically a timer
    int shockTriggerCount;

private slots:
   //aed functions
   void powerButton();
   void shockButton();
   void rechargeButton();

   //testing
   void healthyButton();
   void vFibButton();
   void vTachButton();
   void asysotleButton();
   void peaButton();

   //timer based
   void update();
   void checkLED();
   void resetLEDs();
   void resetAudio(bool=false);
   void checkCPR();
   void endCPR();
   void doShock();

   //patient gui interactions
   void on_depthSlider_sliderMoved(int position);
   void on_ageInput_valueChanged(int arg1);
   void on_batteryNumber_valueChanged(int value);
   void on_electrodes_currentIndexChanged(const QString &arg1);
   void on_cprButton_clicked();
   void attachPads();

};
#endif // MAINWINDOW_H
