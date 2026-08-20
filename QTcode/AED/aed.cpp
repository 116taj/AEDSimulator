#include "aed.h"

Aed::Aed(QWidget *parent)
    : QWidget(parent){
    //create Battery
    batteryUnit = new Battery();
    //initialize other variables
    power = false;
    currTime = 0;
    electrodesConnected = false;
    selfTestSuccessful = false;
    //begin timer
    updateTimer = new QTimer(this);
    updateTimer->start(15);
}


// Aed Updates are managed by an internal QTimer
// Function passes this function for updating UI elements
QTimer* Aed::getUpdateTimer(){
    return updateTimer;
}

//we have setters for these so we can have a QWidget* parent constructor
//these two basically act as secondary constructors
void Aed::setLCD(LCDScreen* l){
    display = l;
}

void Aed::setECG(Ecg* e){
    ecg = e;
}

// Updates relevant functions such as the ecg display and battery drain
//called every 0.015 seconds
void Aed::update(){
    ecg->ecgTimerSlot();

    //Battery will drop by 1 every 5 seconds
    if(currTime != display->getTimeElasped()){
        currTime = display->getTimeElasped();
        if(display->getTimeElasped() % 5 == 0 && testPower()) batteryUnit->decreaseBattery(1);
    }
    //when the battery is out (warning will be shown before)
    //force shutdown
    if (batteryUnit->getPercent() == 0){
        powerOff();
    }
}

bool Aed::getElectrodeStatus(){
    return electrodesConnected;
}
// Unit applies a shock, so long as the rythmn is shockable and charge is built up.
// After a shock the unit cannot shock again until charge has been built up, during which time
// CPR needs to be applied
void Aed::shock(){
    ecg->shock();
    display->incrementShock();
    batteryUnit->decreaseBattery(10);
}

// After user has given sufficient CPR check if it has changed the patient's condition
void Aed::cprApplied(){
    ecg->cpr();
}

// Power is toggled so long as there is charge in the battery
void Aed::powerToggle(){
    power = !power;
    ecg->setPower(power);
    if (display->getPowerState())
        display->powerOff();
    else
        display->powerOn();
}

//force shutdown. used when battery dies
void Aed::powerOff(){
    power = false;
    ecg->setPower(power);
    display->powerOff();
}

bool Aed::testPower(){
    return power;
}


// Replace the battery in the unit, resetting power
void Aed::recharge(){
    batteryUnit->recharge();
}


// Test cases where different conditions are set and handled

// Healthy Rythmn, not shockable
// Nothing should be done besides calling for help
void Aed::healthy(){
    ecg->setState(0);
}

// Shockable Rythmns vFib and vTach
// Shock should be administered followed by CPR, repeated until condition leaves a shockable state or help arrives
void Aed::vFib(){
    ecg->setState(1);
}
void Aed::vTach(){
    ecg->setState(2);
}

// Non-Shockable Rythmns asysotle and pulseless electrical activity
// Only CPR should be administered until condition enters a shockable state or help arrives
void Aed::asysotle(){
    ecg->setState(3);
}
void Aed::pea(){
    ecg->setState(4);
}

int Aed::getBatteryPercent(){
    return batteryUnit->getPercent();
}

//self test
//only fails if forced (an option in the GUI)
//if successful, there might still be battery/cable issues which are also handled here
void Aed::selfTest(bool forceFail){

    selfTestSuccessful = !forceFail;
    if (forceFail)
        display->setPrompt("UNIT FAILED.");
    else if (batteryUnit->getPercent() <= 20)
        display->setPrompt("CHANGE BATTERIES.");
    else if (!electrodesConnected)
        display->setPrompt("PLUG IN CABLE.");
    else if (display->getPrompt() == nullptr || display->getPrompt() == "PLUG IN CABLE." || display->getPrompt() == "CHANGE BATTERIES." || display->getPrompt() == "UNIT FAILED."){
        display->setPrompt("UNIT OK.");
        display->enqueuePrompt("STAY CALM.");
        display->enqueuePrompt("CHECK RESPOSIVENESS.");
        display->enqueuePrompt("CALL FOR HELP.");
        display->enqueuePrompt("ATTACH DEFIB PADS TO PATIENT'S BARE CHEST.");
    }

}

bool Aed::getSelfTestResult(){
    return selfTestSuccessful;
}

void Aed::setElectrodeStatus(bool e){
    electrodesConnected = e;
}

//pads are attached
void Aed::padsAttached(int a){
    //if trying to attach in a state that shouldn't allow it (AED is off or pads undetectable, fail attach
    if (display->getPrompt() == nullptr || display->getPrompt() == "PLUG IN CABLE." || display->getPrompt() == "CHANGE BATTERIES." || display->getPrompt() == "UNIT FAILED.") return;
    //clear queue to allow for skipping beginning in case of emergency
    display->clearPromptQueue();
    //set whether pads are adult or pediatric
    if (a > 17)
        display->enqueuePrompt("ADULT PADS.");
    else
        display->enqueuePrompt("PEDIATRIC PADS.");
    //get to analyzing
    display->enqueuePrompt("DON'T TOUCH PATIENT, ANALYZING.");
}

void Aed::analyze(){
    //check if rythym is shockable and adjut on that
    if (ecg->isShockable()){
       display->enqueuePrompt("SHOCK ADVISED.");

    } else {
        display->enqueuePrompt("NO SHOCK ADVISED.");
        //do cpr if neccessary
        if (ecg->getState() != 0) display->enqueuePrompt("START CPR.");
        else display->enqueuePrompt("DON'T TOUCH PATIENT, ANALYZING.");
    }
}



