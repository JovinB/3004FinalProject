#ifndef CONTROL_H
#define CONTROL_H
#include <QList>
#include "user.h"
#include "session.h"


class Control {
public:
    Control();

    // getters
    bool isPowerOn();
    bool isSelectingSession();
    int getIntensity();
    int getNumUsers();
    User* getUser(QString);
    Record* fetchRecord(QString);
    QString getCurrentUser();
    Session* getCurrentSession();
    QString getConnectionLevel();


    // setters
    void turnOn();
    //turnOff
    void startSelectingSession();
    void stopSelectingSession();
    void setIntensity(int);
    void setCurrentUser(QString);
    void setCurrentSession(QString,QString);
    void setConnectionLevel(QString);

    bool addUser(QString);
    void reset();
    void saveRecord(int);


private:
    bool powerOn;
    bool selectingSession;
    int intensity; // from 1-8
    int userId;
    QVector<User*> users;
    int numUsers;
    QString currentUser;
    Session* currentSession;
    QString connectionLevel;


};

#endif // CONTROL_H
