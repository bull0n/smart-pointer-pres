#pragma once

#include <QSharedDataPointer>

class SimpsonMemberData : public QSharedData
{
public:
    SimpsonMemberData() : age(-1) { }
    SimpsonMemberData(const SimpsonMemberData &other) : QSharedData(other), age(other.age), name(other.name) { }
    ~SimpsonMemberData() {}

    int age;
    QString name;
};

