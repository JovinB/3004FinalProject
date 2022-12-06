#include "session.h"

Session::Session(QString name, QString groupName) {
    this->name = name;
    this->groupName = groupName;
}

QString Session::getName() { return name; }

QString Session::getGroupName() { return groupName; }
