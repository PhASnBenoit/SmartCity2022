#ifndef CECLAIRAGE_H
#define CECLAIRAGE_H

#include <QObject>

#include "czdc.h"
#include "ci2c.h"
#include "cbdd.h"

#define ORDRE_RECU 128

typedef struct{     //LSB vers MSB
    uint8_t
        bitJN : 1, bitPresence : 1, bitLamps : 6;
}T_LAMP;

typedef union{
    T_LAMP partie;
    unsigned char octet;
}U_LAMP;

class CEclairage : public QObject
{
    Q_OBJECT
public:
    explicit CEclairage(QObject *parent = nullptr, CZdc *zdc = nullptr);
    ~CEclairage();

private:
    CI2c *_i2c;
    CZdc *_zdc;
    //CBdd *_bdd;

signals:
    void sig_eclairages(int addr, int nb, int addr_base);
    void sig_parking();

public slots:
    void on_eclairage();
    void on_eclairages(int addr, int nb, int addr_base);
};

#endif // CECLAIRAGE_H
