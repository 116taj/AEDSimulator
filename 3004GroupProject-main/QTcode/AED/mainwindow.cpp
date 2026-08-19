#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aed = ui->aed;
    aed->setECG(ui->ecgWidget);
    aed->setLCD(ui->lcdScreen);
    this->setWindowTitle("AED");
    //hide battery elements since aed is off my default
    ui->batteryNumber->setVisible(false);
    ui->batteryLabel->setVisible(false);
    //hide LEDs
    resetLEDs();
    prevAudio = "";
    shockTriggerCount = 0;
    //connect timers
    audioTimer = new QTimer(this);
    connect(audioTimer,SIGNAL(timeout()),this,SLOT(resetAudio()));
    cprCheckTimer = new QTimer(this);
    connect(cprCheckTimer,SIGNAL(timeout()),this,SLOT(checkCPR()));
    cprTimer = new QTimer(this);
    connect(cprTimer,SIGNAL(timeout()),this,SLOT(endCPR()));
    shockTimer = new QTimer(this);
    connect(shockTimer,SIGNAL(timeout()),this,SLOT(doShock()));
    //connect buttons
    connect(aed->getUpdateTimer(), SIGNAL(timeout()), this, SLOT(update())); //Updates the ecg graph according to internal timer
    connect(ui->healtyButton, SIGNAL(released()), this, SLOT(healthyButton())); //Test 1 button
    connect(ui->vFibButton, SIGNAL(released()), this, SLOT(vFibButton())); //Test 2 button
    connect(ui->vTachButton, SIGNAL(released()), this, SLOT(vTachButton())); //Test 3 button
    connect(ui->asysotleButton, SIGNAL(released()), this, SLOT(asysotleButton())); //Test 4 button
    connect(ui->peaButton, SIGNAL(released()), this, SLOT(peaButton())); //Test 5 button
    connect(ui->adultButton,SIGNAL(released()),this,SLOT(attachPads()));
    connect(ui->childButton,SIGNAL(released()),this,SLOT(attachPads()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(powerButton())); //On / Off button
    connect(ui->shockButton, SIGNAL(released()), this, SLOT(shockButton())); //Shock button
    connect(ui->rechargeButton, SIGNAL(released()), this, SLOT(rechargeButton())); //Recharge Battery
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::powerButton(){
    //powerr is pressed, reset timers and speaker
    resetAudio(true);
    resetLEDs();
    cprTimer->stop();
    cprCheckTimer->stop();
    aed->powerToggle();
    //disable cpr in case it was running
    ui->depthSlider->setEnabled(false);
    ui->cprButton->setEnabled(false);
    ui->breatheButton->setEnabled(false);
    //power on, self test forced to fail
    if (aed->testPower() && ui->fail->currentText() == "Yes"){
        QPixmap testFailed(QCoreApplication::applicationDirPath()+"/selfTestFail.png");
        ui->selfTest->setPixmap(testFailed);
        ui->batteryNumber->setVisible(true);
        ui->batteryLabel->setVisible(true);
        aed->selfTest(true);
    //power on
    } else if (aed->testPower()){
        QPixmap testPassed(QCoreApplication::applicationDirPath()+"/selfTestPassed.png");
        ui->selfTest->setPixmap(testPassed);
        ui->batteryNumber->setVisible(true);
        ui->batteryLabel->setVisible(true);
        aed->selfTest();
    //power off
    } else {
        QPixmap testDef(QCoreApplication::applicationDirPath()+"/selfTestDefault.png");
        ui->selfTest->setPixmap(testDef);
        ui->batteryNumber->setVisible(false);
        ui->batteryLabel->setVisible(false);
    }
}

//shock button pressed
void MainWindow::shockButton(){
    //do nothing if it is not time for a shock
    if(!aed->testPower() || !aed->getSelfTestResult() || ui->lcdScreen->getPrompt() != "SHOCK ADVISED.") return;
    //or if batterry too low
    if(aed->getBatteryPercent() <= 10){
        return;
    }
    //clear queue since shock more important
    ui->lcdScreen->clearPromptQueue();
    ui->lcdScreen->setPrompt("STAND CLEAR. DO NOT TOUCH PATIENT.");
    //change speaker timer because this is precisely timed
    //this calls below function in a second
    shockTimer->start(1000);
    audioTimer->start(1000);
}

void MainWindow::doShock(){
    //it takes 4 calls of this function to administer the shock
    //this way  we can display the 3,2,1 without needing another timer
    shockTriggerCount++;
    if (shockTriggerCount % 4 == 1) {
        ui->lcdScreen->setPrompt("SHOCK WILL BE DELIVERED IN THREE SECONDS.");
    } else if (shockTriggerCount % 4 == 2) {
        ui->lcdScreen->setPrompt("TWO SECONDS.");
    } else if (shockTriggerCount % 4 == 3) {
        ui->lcdScreen->setPrompt("ONE SECOND.");
    } else if (shockTriggerCount % 4 == 0) {
        //do shock and reset timers to  pre-shock state
        ui->lcdScreen->setPrompt("BEEP!");
        aed->shock();
        shockTimer->stop();
        audioTimer->start(1500);

        //do cpr if necessary
        if (ui->ecgWidget->getState() != 0) ui->lcdScreen->enqueuePrompt("START CPR.");
        else ui->lcdScreen->enqueuePrompt("DON'T TOUCH PATIENT, ANALYZING.");
    }
}

//heart cond buttons
void MainWindow::healthyButton(){
    if(!aed->testPower()) return;
    aed->healthy();
}

void MainWindow::vFibButton(){
    if(!aed->testPower()) return;
    aed->vFib();
}

void MainWindow::vTachButton(){
    if(!aed->testPower()) return;
    aed->vTach();
}

void MainWindow::asysotleButton(){
    if(!aed->testPower()) return;
    aed->asysotle();
}

void MainWindow::peaButton(){
    if(!aed->testPower()) return;
    aed->pea();
}

//replace battery if off
void MainWindow::rechargeButton(){
    if(aed->testPower()){
        return;
    }
    aed->recharge();
}


void MainWindow::update(){
    //update battery indicator
    ui->batteryNumber->setValue(aed->getBatteryPercent());
    //get aed to update
    aed->update();
    //if prompt has changed
    if (ui->lcdScreen->getPrompt() != prevAudio && aed->testPower()){
        //update audioPrompt
        ui->audioPrompt->setText(ui->lcdScreen->getPrompt());
        //update prevAudio
        prevAudio = ui->lcdScreen->getPrompt();
        //display for 1.5 s
        audioTimer->start(1500);
        //check if LEDs need updating and if state has been changed
        checkLED();
    //redraw depth indicator if requirements met
    } if (cprTimer->isActive() && aed->testPower()){
        ui->lcdScreen->updateDepth((double)ui->depthSlider->value()/10);
    }
    //cable was unplugged while on
    if (!aed->getElectrodeStatus() && ui->lcdScreen->getPrompt() != nullptr && ui->lcdScreen->getPrompt() != "PLUG IN CABLE." && ui->lcdScreen->getPrompt() != "CHANGE BATTERIES." && ui->lcdScreen->getPrompt() != "UNIT FAILED."){
        //reset everything aand set back to  beginning
        QTextStream(stdout)<<"DEBUG";
        //everything must be reset because we do not know when the cable is unplugged
        ui->lcdScreen->clearPromptQueue();
        ui->lcdScreen->setPrompt("PLUG IN CABLE.");
        cprTimer->stop();
        cprCheckTimer->stop();
        shockTimer->stop();
        ui->lcdScreen->updateDepth(0);
        ui->depthSlider->setEnabled(false);
        ui->cprButton->setEnabled(false);
        ui->breatheButton->setEnabled(false);
        audioTimer->start(1500);
        shockTriggerCount = 0;
    }
}

//check if LEDs need to be updated
void MainWindow::checkLED(){
    //initialiing leds
    if (prevAudio == "CHECK RESPOSIVENESS."){
        ui->led->setVisible(true);
    } else if (prevAudio == "CALL FOR HELP."){
        ui->led->setVisible(false);
        ui->led_2->setVisible(true);
    } else if (prevAudio == "ATTACH DEFIB PADS TO PATIENT'S BARE CHEST."){
        ui->led_2->setVisible(false);
        ui->led_3->setVisible(true);
    } else if (prevAudio == "DON'T TOUCH PATIENT, ANALYZING."){
        //analysis mode detected, do analysis
        resetLEDs();
        ui->led_4->setVisible(true);
        aed->analyze();
    } else if (prevAudio == "START CPR."){
        ui->led_4->setVisible(false);
        ui->led_5->setVisible(true);
        ui->led_6->setVisible(true);
        ui->cprButton->setEnabled(true);
        ui->breatheButton->setEnabled(true);
    }
}

//update depth labe with formatting
void MainWindow::on_depthSlider_sliderMoved(int position)
{
    QString depth = QString::number((double) position/10);
    if (depth == "0" || depth == "1" || depth == "2")
        depth+=".0";
    ui->depthLabel->setText("Depth: "+depth);
}

//disabl/enable buttons depending on age
void MainWindow::on_ageInput_valueChanged(int val)
{
    if (val > 17){
        ui->adultButton->setEnabled(true);
        ui->childButton->setEnabled(false);
    } else if (val > 7){
        ui->childButton->setEnabled(true);
        ui->adultButton->setEnabled(false);
    } else {
        ui->childButton->setEnabled(false);
        ui->adultButton->setEnabled(false);
    }
}

//check if battery is dead or low, update gui accordingly
void MainWindow::on_batteryNumber_valueChanged(int value)
{
    QPalette p = ui->batteryNumber->palette();
    if (value == 0){
        QPixmap testDef(QCoreApplication::applicationDirPath()+"/selfTestDefault.png");
        ui->selfTest->setPixmap(testDef);
    } else if (value <= 20)
      p.setColor(QPalette::Highlight,QColor(246, 97, 81));
    else
      p.setColor(QPalette::Highlight,QColor(53,132,228));
    ui->batteryNumber->setPalette(p);

}

//set electrode status, call selfTest to update AED  after
void MainWindow::on_electrodes_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "No")
        aed->setElectrodeStatus(false);
    else
        aed->setElectrodeStatus(true);
    aed->selfTest();
}

//enable cpr and timer
void MainWindow::on_cprButton_clicked()
{
    ui->depthSlider->setEnabled(true);
    cprTimer->start(15000);
    cprCheckTimer->start(3000);
}

//prompts for cpr, depends on how well compressions are
//checks every 6 compressions
void MainWindow::checkCPR(){
    if (ui->lcdScreen->getDepth() < 2)
        ui->lcdScreen->enqueuePrompt("PUSH HARDER.");
    else if (prevAudio == "PUSH HARDER.")
        ui->lcdScreen->enqueuePrompt("GOOD COMPRESSIONS.");
    else
        ui->lcdScreen->enqueuePrompt("CONTINUE CPR.");
}

//cpr timer expired stop cpr
void MainWindow::endCPR(){
    //stop timers clear queue, etc
    cprTimer->stop();
    cprCheckTimer->stop();
    ui->lcdScreen->clearPromptQueue();
    ui->lcdScreen->enqueuePrompt("STOP CPR.");
    ui->lcdScreen->updateDepth(0);

    // Check if cpr changed patient condition
    aed->cprApplied();
    
    //go back to analysis mode
    ui->lcdScreen->enqueuePrompt("DON'T TOUCH PATIENT, ANALYZING.");
    ui->depthSlider->setEnabled(false);
    ui->cprButton->setEnabled(false);
    ui->breatheButton->setEnabled(false);
}

//reset audio, this is done for realism, since audio wouldn't actually be playing the entire time the display is showing the prompt
void MainWindow::resetAudio(bool full){
    if (full)
        prevAudio = "";
    audioTimer->stop();
    ui->audioPrompt->setText("No audio is currently playing.");
}


//set all LEDs to invisible
void MainWindow::resetLEDs(){
    ui->led->setVisible(false);
    ui->led_2->setVisible(false);
    ui->led_3->setVisible(false);
    ui->led_4->setVisible(false);
    ui->led_5->setVisible(false);
    ui->led_6->setVisible(false);
}

//attach pads to aed
void MainWindow::attachPads()
{
    aed->padsAttached(ui->ageInput->value());
}


