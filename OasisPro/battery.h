#ifndef BATTERY_H
#define BATTERY_H

class Battery
{
public:
    Battery();
    Battery(int);
    void chargeBattery();
    void depleteBattery();
    void myfunction();

private:
    int batteryLevel;



};

#endif // BATTERY_H
