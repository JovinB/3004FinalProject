#include "record.h"

Record::Record(QString recordName, QString sessionName, QString sessionGroup, int duration, int intensityLevel) {
    this->recordName = recordName;
    this->sessionName = sessionName;
    this->sessionGroup = sessionGroup;
    this->duration = duration;
    this->intensityLevel = intensityLevel;
}


// getters
QString Record::getRecordName() { return recordName; }
QString Record::getSessionName() { return sessionName; }
QString Record::getSessionGroup() { return sessionGroup; }
int Record::getDuration() { return duration; }
int Record::getIntensityLevel() { return intensityLevel; }

// setters
// void Record::setIntensityLevel(int newIntensity) { intensityLevel = newIntensity; }
