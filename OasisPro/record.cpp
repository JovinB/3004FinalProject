#include "record.h"

Record::Record(int recordId, const QString& sessionType, int duration, int intensityLevel){
    if (startTime.isValid()) {
        this->recordId = recordId;
        this->sessionType = sessionType;
        this->duration = duration;
        this->intensityLevel = intensityLevel;
        // this->startTime = startTime;
    }
}


// getters
int Record::getRecordId() { return recordId; }
QString Record::getSessionType() { return sessionType; }
int Record::getDuration() { return duration; }
int Record::getIntensityLevel() { return intensityLevel; }
QDateTime Record::getStartTime() { return startTime; }

// setters
// void Record::setIntensityLevel(int newIntensity) { intensityLevel = newIntensity; }
