#include "ceclairage.h"

CEclairage::CEclairage(QObject *parent, CZdc *zdc) : QObject(parent)
{
    _zdc = zdc;
    _i2c = CI2c::getInstance(this, '1');
    connect(this, &CEclairage::sig_eclairages, this, &CEclairage::on_eclairages);
    //Initialisation des variables concernant l'éclairage
    int nb = _zdc->getNbEclairage();
    for(uint8_t i = 0; i < nb; i++){
        _zdc->setPresence(i,false);
        _zdc->setCellule(i,false);
        _zdc->setLampFonct(i,63);//6 lampadaires fonctionnants
        _zdc->setConsigneEclair(i,128+4); //Éteint par défaut et lance un test lampadaire
    }//for
}

CEclairage::~CEclairage()
{
    CI2c::freeInstance();
//    for(int i = 0; i < _zdc->getNbEclairage(); i++){
//        _bdd->del_i2cEclairage(QString(_zdc->getAddrEclair()+i));
    //    }
}

void CEclairage::on_eclairage()
{
    int addr = _zdc->getAddrEclair();
    int nb = _zdc->getNbEclairage();
    emit sig_eclairages(addr, nb, addr);
}

void CEclairage::on_eclairages(int addr, int nb, int addr_base)
{
    if (addr > (addr_base+nb-1)){
        //emit sigRestart();
        emit sig_parking();
        return;
    }//if addr

    //_bdd->set_i2cEclairage(QString(addr), "0", "0", "0", "6");

    U_LAMP octet;
    _i2c->lire(static_cast<unsigned char>(addr), &octet.octet, 1); // Lecture

    uint8_t indice = static_cast<uint8_t>(addr-addr_base);

    _zdc->setCellule(indice, octet.partie.bitJN);
    _zdc->setPresence(indice, octet.partie.bitPresence);
    _zdc->setLampFonct(indice, octet.partie.bitLamps);


    unsigned char ordre = _zdc->getConsigneEclair(indice);
    //ordre |= ORDRE_RECU;

    if(ordre >= ORDRE_RECU){
        ordre -= ORDRE_RECU;
        _i2c->ecrire(static_cast<unsigned char>(addr), &ordre, 1);
        qDebug() << "-------> ORDRE ECLAIRAGE : " << QString::number(ordre);
        _zdc->setConsigneEclair(indice, ordre);  // acquittement de l'ordre
    }

    //_bdd->mod_i2cEclairage(QString(addr), QString(ordre), QString(octet.partie.bitPresence), QString(octet.partie.bitPresence), QString(octet.partie.bitLamps));

    addr = addr + 1;
    sleep(1);
    emit sig_eclairages(addr, nb, addr_base);
}
