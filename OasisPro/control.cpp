#include "control.h"

Control::Control() {
    powerOn = false;
    selectingSession = false;
    intensity = 1;
    userId = 1000;
    numUsers = 0;
    currentUser = "";
}

// getters

bool Control::isPowerOn() { return powerOn; }

bool Control::isSelectingSession() { return selectingSession; }

int Control::getIntensity() { return intensity; }

int Control::getNumUsers() { return numUsers; }

QString Control::getCurrentUser() { return currentUser; }

Session* Control::getCurrentSession() { return currentSession; }


// setters

void Control::turnOn() { powerOn = true; }

void Control::startSelectingSession() { selectingSession = true; }

void Control::stopSelectingSession() { selectingSession = false; }

void Control::setIntensity(int level) { intensity = level; }

void Control::setCurrentUser(QString name) {
    currentUser = name;
}

void Control::setCurrentSession(QString sessionName, QString groupName) {
    currentSession = new Session(sessionName, groupName);
}


bool Control::addUser(QString name) { //Parameters
    User* user = new User(userId++, name);
    users.push_back(user);
    numUsers++;
    return true;
}


User* Control::getUser(QString name) {
    for(int i = 0; i < numUsers; i++){
        if (users[i]->getName() == name){
            return users[i];
        }
    }
    return NULL;
}
