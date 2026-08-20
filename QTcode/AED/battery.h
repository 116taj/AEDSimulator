#ifndef BATTERY_H
#define BATTERY_H

//basic battery storage class
class Battery {
    public:

    Battery();

    //getters
    int getPercent(){return batteryPercent;}

    void recharge();
    void decreaseBattery(int amount);



    private:
        int batteryPercent;
};

#endif // BATTERY_H
