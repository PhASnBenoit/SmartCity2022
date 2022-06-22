#include "cgestionmaquette.h"

CGestionMaquette::CGestionMaquette()
{
    _zdc = new CZdc();
    _ecran = new CEcran(nullptr, _zdc);
    _eclair = new CEclairage(nullptr, _zdc);
    _park = new CParking(nullptr, _zdc);
    _places = new CPlaces(nullptr, _zdc);
    _inter = new CIntersection(nullptr, _zdc);


    connect(this, &CGestionMaquette::sig_inter, _inter, &CIntersection::on_inter);
    connect(_inter, &CIntersection::sig_eclairage, _eclair, &CEclairage::on_eclairage);
    connect(_eclair, &CEclairage::sig_parking, _park, &CParking::on_parking);
    connect(_park, &CParking::sig_places, _places, &CPlaces::on_places);
    connect(_places, &CPlaces::sig_ecran, _ecran, &CEcran::on_ecran);
    connect(_ecran, &CEcran::sig_restart, this, &CGestionMaquette::on_go);
}

CGestionMaquette::~CGestionMaquette()
{
    delete _inter;
    delete _places;
    delete _park;
    delete _eclair;
    delete _ecran;
    delete _zdc;
}

void CGestionMaquette::on_go()
{
        emit sig_inter();  // départ cycle I2C
}
