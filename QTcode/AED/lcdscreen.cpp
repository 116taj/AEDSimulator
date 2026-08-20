#include "lcdscreen.h"

//constructor
LCDScreen::LCDScreen(QWidget *parent)
    : QWidget(parent){

    //create frame and resize
    frame = new QFrame(this);
    frame->setFrameShape(QFrame::Box);
    frame->setStyleSheet("background-color: white");
    frame->setGeometry(QRect(0,0,260,160));
    //shock counter label creation
    shockCounter = new QLabel(this);
    shockCounter->setObjectName(QString::fromUtf8("shockCounter"));
    shockCounter->setGeometry(QRect(10, 10, 111, 21));
    shockCounter->setMinimumSize(QSize(91, 0));
    shockCounter->setStyleSheet(QString::fromUtf8("font: 12pt \"DejaVu Sans\";"));
    shockCounter->setVisible(false);

    //timer label creation
    timer = new QLabel(this);
    timer->setObjectName(QString::fromUtf8("timer"));
    timer->setGeometry(QRect(205, 10, 100, 21));
    timer->setMinimumSize(QSize(91, 0));
    timer->setStyleSheet(QString::fromUtf8("font: 12pt \"DejaVu Sans\";"));
    timer->setVisible(false);

    //prompt label creation
    prompt = new QLabel(this);
    prompt->setObjectName(QString::fromUtf8("label"));
    prompt->setGeometry(QRect(30, 40, 190, 90));
    prompt->setStyleSheet(QString::fromUtf8("font: 14pt \"DejaVu Sans\";"));
    prompt->setAlignment(Qt::AlignCenter);
    prompt->setWordWrap(true);
    prompt->setVisible(false);

    //depth meter creation
    depthIndicator = new QGraphicsView(this);
    depthIndicator->setObjectName(QString::fromUtf8("depthIndicator"));
    depthIndicator->setGeometry(QRect(225, 40, 30, 0));
    depthIndicator->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
    depthIndicator->setVisible(false);

    //depth lines creation
    depth0_0 = new QFrame(this);
    depth0_0->setObjectName(QString::fromUtf8("depth2_0"));
    depth0_0->setGeometry(QRect(225, 40, 30, 2));
    depth0_0->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"""));
    depth0_0->setFrameShape(QFrame::HLine);
    depth0_0->setFrameShadow(QFrame::Sunken);
    depth0_0->setVisible(false);

    depth2_0 = new QFrame(this);
    depth2_0->setObjectName(QString::fromUtf8("depth2_0"));
    depth2_0->setGeometry(QRect(225, 95, 30, 2));
    depth2_0->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"""));
    depth2_0->setFrameShape(QFrame::HLine);
    depth2_0->setFrameShadow(QFrame::Sunken);
    depth2_0->setVisible(false);

    depth2_4 = new QFrame(this);
    depth2_4->setObjectName(QString::fromUtf8("depth2_4"));
    depth2_4->setGeometry(QRect(225, 110, 30, 2));
    depth2_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"""));
    depth2_4->setFrameShape(QFrame::HLine);
    depth2_4->setFrameShadow(QFrame::Sunken);
    depth2_4->setVisible(false);

    //initialize integers
    shockCount = 0;
    timeElasped = 0;
    poweredOn = false;
    depth = 0;

    //initialize timers
    elaspedTimer = new QTimer(this);
    connect(elaspedTimer,SIGNAL(timeout()),this,SLOT(incrementTimer()));

    powerOffTimer = new QTimer(this);
    connect(powerOffTimer,SIGNAL(timeout()),this,SLOT(reset()));

    //calls promptCheck to check for new prompts
    promptTimer = new QTimer(this);
    connect(promptTimer,SIGNAL(timeout()),this,SLOT(promptCheck()));

}

//destructor
LCDScreen::~LCDScreen()
{
    delete frame;
    delete shockCounter;
    delete timer;
    delete prompt;
    delete depthIndicator;
    delete depth0_0;
    delete depth2_0;
    delete depth2_4;
    delete elaspedTimer;
    delete powerOffTimer;
}

//setters
void LCDScreen::setPrompt(QString p){
    prompt->setText(p);
}

//adds to queue
void LCDScreen::enqueuePrompt(QString p){
    promptQueue.append(p);
}
void LCDScreen::setShocks(int s){
    shockCount = s;
}

void LCDScreen::setTimer(int t){
    timeElasped = t;
}

//getters
QString LCDScreen::getPrompt(){
    return prompt->text();
}

int LCDScreen::getShocks(){
    return shockCount;
}

int LCDScreen::getTimeElasped(){
    return timeElasped;
}

bool LCDScreen::getPowerState(){
    return poweredOn;
}

double LCDScreen::getDepth(){
    return depth;
}
//AED is turned on
void LCDScreen::powerOn(){
    poweredOn = true;
    //stop powerOffTimer if on
    powerOffTimer->stop();
    //set everything to visible and update the results
    shockCounter->setVisible(true);
    shockCounter->setText("SHOCKS: "+QString::number(shockCount));
    timer->setVisible(true);
    timer->setText(timeToString());
    elaspedTimer->start(1000);
    promptTimer->start(2750);
    prompt->setVisible(true);
    depthIndicator->setVisible(true);
    depth0_0->setVisible(true);
    depth2_0->setVisible(true);
    depth2_4->setVisible(true);
}

//AED is off, hide everything and start reset timer
void LCDScreen::powerOff(){
    clearPromptQueue();
    promptTimer->stop();
    poweredOn = false;
    shockCounter->setVisible(false);
    timer->setVisible(false);
    prompt->setVisible(false);
    prompt->setText(nullptr);
    updateDepth(0);
    depthIndicator->setVisible(false);
    depth0_0->setVisible(false);
    depth2_0->setVisible(false);
    depth2_4->setVisible(false);

    powerOffTimer->start(5000);


}

//converts the timeElasped integer to proper format
QString LCDScreen::timeToString(){
    int minutes = timeElasped/60;
    int seconds = timeElasped%60;
    if (seconds < 10 && minutes < 10)
        return "0"+QString::number(minutes)+":0"+QString::number(seconds);
    else if (minutes < 10)
        return "0"+QString::number(minutes)+":"+QString::number(seconds);
    else if (seconds < 10)
        return QString::number(minutes)+":0"+QString::number(seconds);
    return QString::number(minutes)+":"+QString::number(seconds);
}

//called every second, increments timer and updates
void LCDScreen::incrementTimer(){
    timeElasped++;
    if (timeElasped > 5999)
        timeElasped = 0;
    timer->setText(timeToString());
}

//update indicator based on the depth of compression
void LCDScreen::updateDepth(double d){
    if (d > 2.4)
        d = 2.4;
    depth = d;
    depthIndicator->setGeometry(QRect(225, 40, 30, depth/2.4 * 70));
}

//increment shock number and&& prevAudio != "PUSH HARDER." update
void LCDScreen::incrementShock(){
    shockCount++;
    updateShockCounter();
}

//update shock label
void LCDScreen::updateShockCounter(){
    shockCounter->setText("SHOCKS: "+QString::number(shockCount));
}

//reset integers and stop timers
void LCDScreen::reset(){
    shockCount = 0;
    timeElasped = 0;
    elaspedTimer->stop();
    powerOffTimer->stop();
}

//check if prompt needs to be updated, if so set new prompt and then pop queue
void LCDScreen::promptCheck(){
    if (promptQueue.size() > 0){
        QString p = promptQueue[0];
        setPrompt(p);
        promptQueue.pop_front();
    }
}

void LCDScreen::clearPromptQueue(){
    promptQueue.clear();
}
