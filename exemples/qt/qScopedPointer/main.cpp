#include <QCoreApplication>
#include <QScopedPointer>

#include "fauteuil.h"
#include "canape.h"
#include "telecommande.h"


void useTelecommande(QScopedPointer<Telecommande>& telecommande){
    //Quelque chose qui pourrais lancer une exception !
}

void useCanape(bool homer, int chaine)
{
    // assuming that MyClass has a virtual destructor
    QScopedPointer<Canape> p(homer ? new Fauteuil() : new Canape(5));
    QScopedPointer<Telecommande> telecommande(Telecommande::createTelecommande());

    if (chaine < 1)
        return;

    useTelecommande(telecommande);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int chaine = 12;
    useCanape(true, chaine);

    return a.exec();
}
