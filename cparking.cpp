#include "cparking.h"

CParking::CParking(QObject *parent, CZdc *zdc) : QObject(parent)
{
    _zdc = zdc;
    _i2c = CI2c::getInstance(nullptr, 1);
    //Init
    _zdc->setOrdreBarrieres(0);//0 = BED et BSD / 1 = BEM et BSD
    //2 = BED ET BSM / 3 = BEM ET BSM
    _zdc->setEtatsBarrieres(0);
    _zdc->setCpt(8);//8 places par défaut
    //Fin Init
}

CParking::~CParking()
{
    CI2c::freeInstance();
    //_bdd->del_i2cParking(QString(_zdc->getAddrPark()));
}

void CParking::on_parking()
{
    unsigned char addr = static_cast<unsigned char>(_zdc->getAddrPark());
    //_bdd->set_i2cParking(QString(addr), "0");

    unsigned char parking[11];
    QByteArray RFIDe;
    QByteArray RFIDs;

    _i2c->lire(addr, parking, 11); // Lecture
    T_PARK_STATE *parkState;
    parkState = reinterpret_cast<T_PARK_STATE *>(&parking[0]);
    qDebug() << "Etats parking : " << QString::number(parking[0], 16);

    //_bdd->mod_i2cParking(QString(addr), QString(parkState->bitsStates));
    _zdc->setEtatsBarrieres(parkState->bitsStates);

    RFIDe = QByteArray(reinterpret_cast<char *>(parking+1), 5); //Conversion de unsigned char * vers QByteArray
    qDebug() << RFIDe;
    _zdc->setRfidE(RFIDe);

    RFIDs = QByteArray(reinterpret_cast<char *>(parking+6), 5);
    qDebug() << RFIDs;
    _zdc->setRfidS(RFIDs);

    QThread::msleep(300);

    //emit sigEcran(static_cast<QString>(_zdc->getCpt()));

    uint8_t order = _zdc->getOrdreBarrieres();
    if(order >= 128){
        order = order - 128;
        switch(order){
        case BAR_SORTIE_DES:
            _i2c->ecrire(static_cast<unsigned char>(_zdc->getAddrPark()), &order, 1);
            _zdc->setOrdreBarrieres(order);
            _zdc->setCptPlus();
            break;

        case BAR_ENTREE_DES:
            _i2c->ecrire(static_cast<unsigned char>(_zdc->getAddrPark()), &order, 1);
            _zdc->setOrdreBarrieres(order);
            _zdc->setCptMoins();
            break;

        default:
            _i2c->ecrire(static_cast<unsigned char>(_zdc->getAddrPark()), &order, 1);
            _zdc->setOrdreBarrieres(order);
            break;
        }//SW
    }//IF
    sleep(1);
    emit sig_places();
}//onPark()
