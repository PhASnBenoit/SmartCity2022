#ifndef CGESTIONMAQUETTE_H
#define CGESTIONMAQUETTE_H

#include <QObject>
#include <QThread>
#include <QString>

#include "czdc.h"
#include "ceclairage.h"
#include "cintersection.h"
#include "cecran.h"
#include "cparking.h"
#include "cplaces.h"
#include "cconfig.h"

class CGestionMaquette : public QObject
{
    Q_OBJECT

public:
    CGestionMaquette();
    ~CGestionMaquette();

    void on_go();

private:
    CEclairage *_eclair;
    CIntersection *_inter;
    CEcran *_ecran;
    CParking *_park;
    CPlaces *_places;
    CZdc *_zdc;

signals:
    void sig_eclair(int addr, int nb, int addr_base);
    void sig_inter();
    void sig_park();
    void sig_places();
    void sig_ecran(QString nb);
};

#endif // CGESTIONMAQUETTE_H
