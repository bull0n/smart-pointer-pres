#pragma once

#include "simpsonmemberdata.h"

class SimpsonMember
{
public:
    SimpsonMember() { _data = new SimpsonMemberData; }
    SimpsonMember(int age, const QString &name) {
        _data = new SimpsonMemberData();
        setAge(age);
        setName(name);
    }
    SimpsonMember(const SimpsonMember &other)
          : _data (other._data)
    {
    }
    void setAge(int age) { _data->age = age; }
    void setName(const QString &name) { _data->name = name; }

    int age() const { return _data->age; }
    QString name() const { return _data->name; }

  private:
    QSharedDataPointer<SimpsonMemberData> _data;
};
