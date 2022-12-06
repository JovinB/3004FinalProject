#ifndef RECORD_H
#define RECORD_H
#include <string>
#include <QDateTime>
#include <QTimer>

using namespace std;

class Record {
public:
    Record(int,QString,QString,int,int); // const QDateTime&

    // getters
    int getRecordId();
    QString getSessionName();
    QString getSessionGroup();
    int getDuration();
    int getIntensityLevel();

    // setters
    // void setIntensityLevel(int newIntensity);

private:
    int recordId;
    QString sessionName;
    QString sessionGroup;
    int duration;
    int intensityLevel;

};

#endif // RECORD_H
