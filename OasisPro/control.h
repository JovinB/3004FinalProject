#ifndef CONTROL_H
#define CONTROL_H


class Control {
public:
    Control();

    // getters
    bool isPowerOn();
    bool isSelectingSession();
    int getIntensity();

    // setters
    void turnOn();
    //turnOff
    void startSelectingSession();
    void stopSelectingSession();
    void setIntensity(int);

private:
    bool powerOn;
    bool selectingSession;
    int intensity; // from 1-8

};

#endif // CONTROL_H
