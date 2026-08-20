#include "ecg.h"

Ecg::Ecg(QWidget* parent)
    : QWidget(parent)
    //ecgGraph(0)
{
    srand(time(NULL)); // Iniatilze randomness for value "wobble"
    frame = new QFrame(this);
    frame->setFrameShape(QFrame::Box);
    frame->setStyleSheet("background-color: white");
    frame->setGeometry(QRect(0,0,260,160));
    // Initialize Graph Plot
    ecgGraph = new QCustomPlot(this);
    ecgGraph->setGeometry(QRect(0,0,260,160));
    ecgGraph->addGraph();
    ecgGraph->xAxis->setLabel("");
    ecgGraph->xAxis->setRange(0,100);
    ecgGraph->xAxis->setVisible(false);
    ecgGraph->yAxis->setLabel("ECG(mV)");
    ecgGraph->yAxis->setRange(-0.5,1);

    // Initialize graph data
    x = QVector<double>(101);
    y = QVector<double>(101);
    for(int i=0;i<x.size();i++){
        x[i]=i;
        y[i]=0;
    }

    // Set up rythmn patterns
    healthy = QVector<double>(25);
    healthy[4] = 0.1;
    healthy[5] = 0.2;
    healthy[6] = 0.1;
    healthy[11] = -0.1;
    healthy[12] = 0.9;
    healthy[13] = -0.1;
    healthy[18] = 0.2;
    healthy[19] = 0.4;
    healthy[20] = 0.2;

    vFib = QVector<double>(20);
    vFib[1]=0.2;
    vFib[3]=-0.2;
    vFib[4]=0.1;
    vFib[5]=-0.1;
    vFib[6]=0.2;
    vFib[7]=0.2;
    vFib[8]=-0.1;
    vFib[9]=-0.2;
    vFib[10]=-0.2;
    vFib[11]=0.2;
    vFib[12]=0.1;
    vFib[13]=-0.1;
    vFib[14]=0.2;
    vFib[15]=0.1;
    vFib[16]=0.2;
    vFib[18]=-0.1;
    vFib[19]=-0.2;

    vTach = QVector<double>(11);
    vTach[0]=0.8;
    vTach[1]=0.7;
    vTach[2]=0.6;
    vTach[3]=0.5;
    vTach[4]=0.4;
    vTach[5]=0.3;
    vTach[6]=0.2;
    vTach[7]=0.1;
    vTach[8]=0;
    vTach[9]=-0.1;
    vTach[10]=-0.2;

    asystole = QVector<double>(2);

    pea = QVector<double>(33);
    pea[1]=0.8;
    pea[2]=0.6;
    pea[2]=0.4;
    pea[2]=0.2;
    pea[3]=0;
    pea[4]=-0.2;
    pea[5]=-0.4;
    pea[6]=-0.2;

    // Remaining Variables
    power = false;
    current  = 0;
    state = 0;
}
Ecg::~Ecg(){
    delete ecgGraph;
}

int Ecg::getState(){
    return state;
}

QCustomPlot* Ecg::getGraph(){
    return ecgGraph;
}

void Ecg::setState(int s){
    state = s;
}

void Ecg::setPower(bool p){
    ecgGraph->graph(0)->setVisible(p);
    power=p;
    if(!p) clear();
}

bool Ecg::isShockable(){
    if (state==1 || state == 2) return true;
    return false;
}

void Ecg::clear(){
    for(int i=0; i<x.size(); i++){
        y[i]=0;
    }
    current = 0;
    ecgGraph->replot();
}

void Ecg::shock(){
    int outcome = rand()%100;
    if(outcome>30) return;
    if(outcome>10){
        state = 0;
        return;
    }
    state = 3;
}

void Ecg::cpr(){
    int outcome = rand()%100;
    if(outcome>40) return;
    if(outcome>10){
        state = 0;
        return;
    }
    state = 3;
}

void Ecg::ecgTimerSlot(){
    if(!power) return;
    double wobble = 1+0.1*(rand()%3-1); //Each non-zero value is multiplied by 0.9~1.1 randomly
    switch(state){
        case 0: y[current%y.size()] = healthy[current%healthy.size()]*wobble;
                break; //Healthy
        case 1: y[current%y.size()] = vFib[current%vFib.size()]*wobble; //vFib
                break;
        case 2: y[current%y.size()] = vTach[current%vTach.size()]*wobble; //vTach
                break;
        case 3: y[current%y.size()] = asystole[current%asystole.size()]+0.05*(wobble-1); //asostyle
                break;
        case 4: y[current%y.size()] = pea[current%pea.size()]*wobble; //PEA
    }

    current++;
    ecgGraph->graph(0)->setData(x,y);
    ecgGraph->replot();
}
