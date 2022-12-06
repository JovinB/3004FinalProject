#ifndef RECORD_H
#define RECORD_H
#include <string>
#include <QDateTime>
#include <QTimer>

using namespace std;

class Record {
public:
    Record(int,const QString&,int,int); // const QDateTime&

    // getters
    int getRecordId();
    QString getSessionType();
    int getDuration();
    int getIntensityLevel();
    QDateTime getStartTime();

    // setters
    // void setIntensityLevel(int newIntensity);

private:
    int recordId;
    QString sessionType;
    int duration;
    int intensityLevel;
    QDateTime startTime;

};

#endif // RECORD_H
