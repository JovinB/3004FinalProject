#include "user.h"

User::User(int id, QString name) {
    this->id = id;
    this->name = name;
}

void User::addRecord(Record* record) {
    records.push_back(record);
    numRecords++;
}

// getters
QString User::getName() { return name; }
QVector<Record*> User::getRecords() { return records; }
int User::getNumRecords() { return numRecords; }

