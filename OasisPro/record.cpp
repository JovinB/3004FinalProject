#include "record.h"
#include <QDebug>

Record::Record(int recordId, QString sessionName, QString sessionGroup, int duration, int intensityLevel) {
    this->recordId = recordId;
    this->sessionName = sessionName;
    this->sessionGroup = sessionGroup;
    this->duration = duration;
    this->intensityLevel = intensityLevel;
    qDebug() << "RecordId: " << recordId <<"Session Name: " << sessionName <<"Session Group: " << sessionGroup << "Duration: " << duration << "Intensity: " << intensityLevel;
}


// getters
int Record::getRecordId() { return recordId; }
QString Record::getSessionName() { return sessionName; }
QString Record::getSessionGroup() { return sessionGroup; }
int Record::getDuration() { return duration; }
int Record::getIntensityLevel() { return intensityLevel; }

// setters
// void Record::setIntensityLevel(int newIntensity) { intensityLevel = newIntensity; }
