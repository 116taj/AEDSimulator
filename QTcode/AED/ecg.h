#ifndef ECG_H
#define ECG_H

#include <QWidget>
#include "qcustomplot.h"

// This class simulates an ecg and its display by creating a heartbeat based on a rythmn given to the ecg
//
// Can be used by passing a QCustomPlot widget on creation of ecg and connecting its timer with getTimer()
// to the slot ecgTimerSlot or by tying it to another slot and calling ecgTimerSlot seperately.
//
// The heart Rythmns States which can be set are: 0 = healthy, 1 = vFib, 2 = vTach, 3 = asostyle, 4 = PEA
// Setting the state to off or from off will toggle the visibility of the display

class Ecg : public QWidget
{
    Q_OBJECT

public:
    Ecg(QWidget *parent = nullptr);
    ~Ecg();

    //setters
    void setState(int);
    void setPower(bool);

    //getters
    int getState();
    QCustomPlot* getGraph();
    //Checks if current state is shockable
    bool  isShockable();

    //Apply Shock with a %chance of success or change in state
    void shock();

    //Apply CPR with a %chance of success or change in state
    void cpr();

public slots:
    void ecgTimerSlot(); // Update Graph when called

private:
    QCustomPlot *ecgGraph;
    QVector<double> x,y,healthy,vFib,vTach,asystole,pea;
    QFrame* frame;
    bool power;
    int current; // current place along the graph/rythmn
    int state; //0 == healthy, 1 = vFib, 2 = vTach, 3 = asostyle, 4 = PEA

    void clear(); // Clear data from graph
};


#endif // ECG_H
