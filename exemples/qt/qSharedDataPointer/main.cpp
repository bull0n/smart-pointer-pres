#include <QCoreApplication>
#include <QDebug>

#include "simpsonmember.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpsonMember homer(10, "Homer Simpson");
    SimpsonMember barth = homer;
    barth.setName("Barth Simspon");
    homer.setAge(50);

    qDebug() << "Nom : " << homer.name() << "\t age : " << homer.age();
    qDebug() << "Nom : " << barth.name() << "\t age : " << barth.age();
    return a.exec();
}
