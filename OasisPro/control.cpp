#include "control.h"

Control::Control() {
    powerOn = false;
    selectingSession = false;
    intensity = 1;
}

// getters

bool Control::isPowerOn() {
    return powerOn;
}

bool Control::isSelectingSession() {
    return selectingSession;
}

int Control::getIntensity() {
    return intensity;
}


// setters

void Control::turnOn() {
    powerOn = true;
}

void Control::startSelectingSession() {
    selectingSession = true;
}

void Control::stopSelectingSession() {
    selectingSession = false;
}

void Control::setIntensity(int level) {
    intensity = level;
}
