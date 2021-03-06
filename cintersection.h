#ifndef CINTERSECTION_H
#define CINTERSECTION_H

#define AUCUN_ORDRE 4
#define ORDRE_RECU 128
#define ACK 128
#define MODE_MANUEL 2

#include <QObject>

#include "czdc.h"
#include "ci2c.h"
#include "cbdd.h"

//READ//

typedef struct{
    uint8_t
        bitMode : 2,
        bitCouleurs : 2,
        bitBoutons : 3;
} T_READ;

typedef union{
    T_READ partie;
    unsigned char octet;
} U_READ;

//WRITE//

typedef struct{
    uint8_t
        bitMode : 2,
        bitCouleurs1 : 2,
        bitCouleurs2 : 2;
} T_WRITE;

typedef union{
    T_WRITE partie;
    unsigned char octet;
} U_WRITE;

class CIntersection : public QObject
{
    Q_OBJECT
public:
    explicit CIntersection(QObject *parent, CZdc *zdc);
    ~CIntersection();

private:
    CI2c *_i2c;
    CZdc *_zdc;
    //CBdd *_bdd;
    U_WRITE uw;
    unsigned char ancienOctet;

signals:
    void sig_restart();
    void sig_eclairage();

public slots:
    void on_inter();
};

#endif // CINTERSECTION_H
