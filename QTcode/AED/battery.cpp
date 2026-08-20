#include "battery.h"

Battery:: Battery(){
    batteryPercent = 100;
}

//Recharge the battery to 100%
void Battery:: recharge(){
    batteryPercent = 100;
}

//Decrease the battery by a set amount
void Battery:: decreaseBattery(int amount){
    //can't make a battery go into negatives
    if (amount > batteryPercent)
        batteryPercent = 0;
    batteryPercent -= amount;
}

