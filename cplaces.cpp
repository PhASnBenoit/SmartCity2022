#include "cplaces.h"


CPlaces::CPlaces(QObject *parent, CZdc *zdc) : QObject(parent)
{
    _zdc = zdc;
    _i2c = CI2c::getInstance(nullptr, 1);
}

CPlaces::~CPlaces()
{
    CI2c::freeInstance();
}

void CPlaces::on_places()
{
    unsigned char addr = static_cast<unsigned char>(_zdc->getAddrPlaces());

    //READ
    quint8 octet;
    int nb = _i2c->lire(addr, &octet, 1); // Lecture
    if (nb != 1) {
        emit sig_ecran("PROBLEME LECTURE PLACES PARKING I2C !!!");
    } // erreur i2c
    _zdc->setPlaces(octet);
    qDebug() << "Voitures présentes : " << octet;
    emit sig_ecran("AFFICHAGE");
    //emit sig_restart();
    sleep(1);
}
