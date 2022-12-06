#ifndef USER_H
#define USER_H
#include "record.h"
#include <QList>

class User {
public:
    User(int,QString);
    void addRecord(Record*);

    //getters
    QString getName();
    QVector<Record*> getRecords();
    int getNumRecords();

private:
    int id;
    QString name;
    QVector<Record*> records;
    int numRecords= 0;


};

#endif // USER_H
