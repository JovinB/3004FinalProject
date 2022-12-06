#ifndef SESSION_H
#define SESSION_H
#include <QDateTime>


class Session {
public:
    Session(QString,QString);

     QString getName();
     QString getGroupName();

private:
    QString name;
    QString groupName;

};

#endif // SESSION_H
