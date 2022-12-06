#ifndef RECORD_H
#define RECORD_H
#include <string>
#include <QDateTime>
#include <QTimer>

using namespace std;

class Record {
public:
    Record(QString,QString,QString,int,int); // const QDateTime&

    // getters
    QString getRecordName();
    QString getSessionName();
    QString getSessionGroup();
    int getDuration();
    int getIntensityLevel();

    // setters
    // void setIntensityLevel(int newIntensity);

private:
    QString recordName;
    QString sessionName;
    QString sessionGroup;
    int duration;
    int intensityLevel;

};

#endif // RECORD_H
