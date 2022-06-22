#ifndef CPLACES_H
#define CPLACES_H

#include <QObject>

#include "czdc.h"
#include "ci2c.h"
#include "cbdd.h"

class CPlaces : public QObject
{
    Q_OBJECT
public:
    explicit CPlaces(QObject *parent = nullptr, CZdc *zdc = nullptr);
    ~CPlaces();

private:
    CI2c *_i2c;
    CZdc *_zdc;

signals:
    void sig_ecran(QString nb);
    void sig_restart();

public slots:
    void on_places();
};

#endif // CPLACES_H
