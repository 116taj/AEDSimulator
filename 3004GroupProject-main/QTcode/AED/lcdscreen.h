#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QTimer>

//LCDScreen QWidget that displays prompts, time, shock count, and cpr compression depth
class LCDScreen : public QWidget
{
    Q_OBJECT

public:
    LCDScreen(QWidget *parent = nullptr);
    ~LCDScreen();

    //setters
    void setShocks(int);
    void setTimer(int);
    void setPrompt(QString);
    void enqueuePrompt(QString);

    //getters
    QString getPrompt();
    int getShocks();
    int getTimeElasped();
    bool getPowerState();
    double getDepth();

    //other
    void powerOn();
    void powerOff();
    QString timeToString();
    void updateDepth(double);
    void incrementShock();
    void updateShockCounter();
    void clearPromptQueue();

private slots:
    //timer based
    void incrementTimer();
    void reset();
    void promptCheck();

private:
    //widgets
    QFrame* frame;
    QLabel* shockCounter;
    QLabel* timer;
    QLabel* prompt;
    QGraphicsView* depthIndicator;
    QFrame* depth0_0;
    QFrame* depth2_0;
    QFrame* depth2_4;

    //other variables
    int shockCount;
    int timeElasped;
    double depth;
    QString promptText;
    QTimer* elaspedTimer;
    QTimer* powerOffTimer;
    QTimer* promptTimer;
    //list of future prompts, done so the screen doesn't blast through a bunch of prompts at once
    QList<QString> promptQueue;
    bool poweredOn;


};
#endif  //LCDSCREEN_H
