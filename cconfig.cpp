#include "cconfig.h"


CConfig::CConfig()
{
    //creer objet avec paramètre chemin d'access du fichier et format de lecture
    QSettings settings("SmartCity.ini", QSettings::IniFormat);

    //prend valeur ici, si non trouvée prend valeur du .ini
    _port = settings.value("Serveur/PORT", "2222").toString();
    _addrPark = settings.value("Parking/ADDR_I2C_PARK", "0x35").toString();
    _addrPlaces = settings.value("Places/ADDR_I2C_PLACES", "0x32").toString();
    _addrEclair = settings.value("Eclairage/ADDR_I2C_ECLAIR", "0x14").toString();
    _nbEclair = settings.value("Eclairage/NOMBRE_CARTES", "1").toString();
    _addrInter = settings.value("Intersection/ADDR_I2C_INTER", "0x42").toString();
}
