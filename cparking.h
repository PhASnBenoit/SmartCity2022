#ifndef CPARKING_H
#define CPARKING_H

#include "stdio.h"
#include <QObject>
#include <QDebug>
#include <QThread>

#define BAR_SORTIE_DES 2
#define BAR_ENTREE_DES 0

#include "czdc.h"
#include "ci2c.h"
#include "cbdd.h"

typedef struct{         //LSB vers MSB
    uint8_t bitsStates : 8;// 7:ButtUrgExit 6:ButtUrgEntr 5:PersEntr 4: PersExit
                           // 3:BSM 2:BSD 1:BEM 0: BED
} T_PARK_STATE;

class CParking : public QObject
{
    Q_OBJECT
public:
    explicit CParking(QObject *parent, CZdc *zdc);
    ~CParking();

private:
    CI2c *_i2c;
    CZdc *_zdc;
    //CBdd *_bdd;

signals:
    void sigEcran(QString nb);
    void sigRestart();
    void sig_places();

public slots:
    void on_parking();

};

#endif // CPARKING_H
