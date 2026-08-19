#ifndef AED_H
#define AED_H

#include "lcdscreen.h"
#include "battery.h"
#include "ecg.h"
#include <QWidget>

//AED class that contains all AED information
//QObject to support QTimer, QWidget to be able to find children (not implemented due to findChild() taking too much time to initialize widgets)
class Aed : public QWidget{
    Q_OBJECT
    public:
        Aed(QWidget *parent = nullptr);

        //Getters
        QTimer* getUpdateTimer();
        int getBatteryPercent();
        bool getElectrodeStatus();
        bool getSelfTestResult();
        bool testPower();
        //setters
        void setElectrodeStatus(bool);
        void setECG(Ecg*);
        void setLCD(LCDScreen*);
        // Handles updating elements on timer
        void update();

        //Other
        void shock();
        void cprApplied();
        void powerToggle();
        void powerOff();
        void recharge();
        void padsAttached(int);
        void analyze();
        void selfTest(bool=false);

        // Testing Functions
        void healthy();
        void vFib();
        void vTach();
        void asysotle();
        void pea();
    private:
        LCDScreen* display;
        Battery* batteryUnit;
        Ecg* ecg;
        QTimer* updateTimer;

        //stores time for battery drain
        int currTime;
        //whether unit is on; true if yes
        bool power;
        //whether electrodes are connected to patient; true if yes
        bool electrodesConnected;
        //true if selfTest was successful
        bool selfTestSuccessful;

};

#endif // AED_H
