#include "cbdd.h"
#include "QSqlDatabase"
#include <QDebug>
#include <QSqlError>
#include <QString>
#include <iostream>
#include <string>
#include <QSqlQuery>
#include <QSettings>
#include <QStringListModel>
#include <QStringList>
#include <QAbstractItemView>

CBdd::CBdd(QObject *parent) : QObject(parent)
{
    QSettings settings("SmartCity.ini", QSettings::IniFormat);
    //prend valeur 1, si non trouver prend valeur 2
    QString ip = settings.value("BDD/BDD_HOST_NAME", "SmartCity").toString();
    QString id = settings.value("BDD/BDD_USER_NAME", "SmartCity").toString();
    QString mdp = settings.value("BDD/BDD_PASSWORD", "SmartCity").toString();
    QString NomBDD = settings.value("BDD/BDD_DATABASE_NAME", "SmartCity").toString();

    // Instanciation de la variable membre dbMeteo
    dbSC = QSqlDatabase::addDatabase("QMYSQL");

    // Définition des paramètres de connexion à la base de données
    dbSC.setHostName(ip); // @ip serveur MySQL
    dbSC.setDatabaseName(NomBDD); // Nom de la base
    dbSC.setUserName(id); // Nom utilisateur
    dbSC.setPassword(mdp); // Mot de passe
}

bool CBdd::verifierParamsConnexion()
{
    if(dbSC.open()) {
        connexionFaite = true;
    } else {
        qDebug() << "Echec d'ouverture de la base de donnée";
        qDebug() << dbSC.lastError();
        connexionFaite = false;
    }
    return connexionFaite;
}


QString CBdd::set_i2cAfficheur(QString addrI2C, QString message)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "INSERT INTO afficheur (adrI2C, message) VALUES ('" + addrI2C + "', '" + message + "');";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}

QString CBdd::set_i2cEclairage(QString addrI2C, QString etatLampadaire, QString capteurPres1, QString capteurPres2, QString lampadaireOK)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "INSERT INTO eclairage (adrI2C, etatLampadaire, capteurPres1, capteurPres2, lampadaireOK) VALUES ('" + addrI2C + "', '" + etatLampadaire + "', '" + capteurPres1 + "', '" + capteurPres2 + "', '" + lampadaireOK + "');";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}

QString CBdd::set_i2cIntersection(QString addrI2C, QString etatMode, QString boutonPieton1, QString boutonPieton2, QString etatVoie1, QString etatVoie2)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "INSERT INTO intersection (adrI2C, etatMode, boutonPieton1, boutonPieton2, etatVoie1, etatVoie2) VALUES ('" + addrI2C + "', '" + etatMode + "', '" + boutonPieton1 + "', '" + boutonPieton2 + "', '" + etatVoie1 + "', '" + etatVoie2 + "');";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}

QString CBdd::set_i2cParking(QString addrI2C, QString etats)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "INSERT INTO parking (adrI2C, etats) VALUES ('" + addrI2C + "', '" + etats + "');";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}







QString CBdd::mod_i2cAfficheur(QString addrI2C, QString message)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "UPDATE afficheur SET message = '" + message + "' WHERE afficheur.adrI2C = '" + addrI2C + "';";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}

QString CBdd::mod_i2cEclairage(QString addrI2C, QString etatLampadaire, QString capteurPres1, QString capteurPres2, QString lampadaireOK)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;
    QString req = "UPDATE eclairage SET etatLampadaire = '" + etatLampadaire + "', capteurPres1 = '" + capteurPres1 + "', capteurPres2 = '" + capteurPres2 + "', lampadaireOK = '" + lampadaireOK + "' WHERE eclairage.adrI2C = '" + addrI2C + "';";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}

QString CBdd::mod_i2cIntersection(QString addrI2C, QString etatMode, QString boutonPieton1, QString boutonPieton2, QString etatVoie1, QString etatVoie2)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "UPDATE intersection SET etatMode = '" + etatMode + "', boutonPieton1 = '" + boutonPieton1 + "', boutonPieton2 = '" + boutonPieton2 + "', etatVoie1 = '" + etatVoie1 + "', etatVoie2 = '" + etatVoie2 + "', WHERE intersection.adrI2C = '" + addrI2C + "';";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}

QString CBdd::mod_i2cParking(QString addrI2C, QString etats)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "UPDATE parking SET etats = '" + etats + "' WHERE parking.adrI2C = '" + addrI2C + "';";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}







QString CBdd::del_i2cAfficheur(QString addrI2C)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "DELETE FROM afficheur WHERE afficheur.adrI2C = '" + addrI2C + "';";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}

QString CBdd::del_i2cEclairage(QString addrI2C)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;
    QString req = "DELETE FROM eclairage WHERE eclairage.adrI2C = '" + addrI2C + "';";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}

QString CBdd::del_i2cIntersection(QString addrI2C)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "DELETE FROM intersection WHERE intersection.adrI2C = '" + addrI2C + "';";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}

QString CBdd::del_i2cParking(QString addrI2C)
{
    verifierParamsConnexion();
    //bool connexionFaite = verifierParamsConnexion();

    // Exécution d'une requête
    QSqlQuery requete;

    QString req = "DELETE FROM parking WHERE parking.adrI2C = '" + addrI2C + "';";
    if(!requete.exec(req)){
        adrI2C = "erreur";
    } else { adrI2C = "";}
    dbSC.close(); // Fermeture de la base de données
    qDebug() << adrI2C;
    return adrI2C;
}
