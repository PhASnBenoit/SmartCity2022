#include "cgererserveur.h"

CGererServeur::CGererServeur(quint16 noPort, QObject *parent) : QObject(parent)
{
    _noPort = noPort;
    _addr = QHostAddress::AnyIPv4;
    _serv = new CMonServeurTcp();
    connect(_serv, &CMonServeurTcp::sig_sdClient, this, &CGererServeur::on_newConnection);
    _serv->listen(_addr, _noPort);

}

CGererServeur::~CGererServeur()
{// effacement des threads
    for (int i=0 ; i<_listeThread.size() ; i++) {
        _listeThread.at(i)->quit();  // demande au thread de se terminer
        _listeThread.at(i)->wait();  // attends la fin de la boucle événements
    } // for
    _listeThread.clear();
    _listeClient.clear();
    delete _serv;
}

void CGererServeur::on_newConnection(qintptr sd)
{
    // Nouvelle connexion d'un client
    // La méthode héritée QTcpServer::incomingConnection() a été redéfinie.

    QThread *gthc = new QThread();  // création du thread
    gthc->setObjectName("servGcl_"+QString::number(sd));    //changer son nom pour le reconnaitre dans pstree
    CGererClient *client = new CGererClient(sd,nullptr);  // le client créera la socket de comm grace au descripteur (sd)

    client->moveToThread(gthc);// déplacement vers le thread

    //init signaux affichages
    connect(client, &CGererClient::sig_info, this, &CGererServeur::on_info);
    connect(client, &CGererClient::sig_erreur, this, &CGererServeur::on_erreur);

    connect(client, &CGererClient::sig_disconnected, this, &CGererServeur::on_disconnected); // provoque la destruction du client et du thread
    connect(this, &CGererServeur::sig_goGestionClient, client, &CGererClient::on_goGestionClient); // provoque création socket client
    connect(gthc, &QThread::finished, client, &QObject::deleteLater); // L'objet qui gere le client se fais détruire si son thread se fini

    gthc->start(); // départ boucle des événements du thread.
    emit sig_goGestionClient(); // Départ de la gestion du client

    // Mémorisation des objets créés dans des listes
    _listeClient.append(client);
    _listeThread.append(gthc);
}

void CGererServeur::on_disconnected()
{
    CGererClient *client = static_cast<CGererClient *>(sender());
    // le signal disconnected est parfois envoyé 2 fois !!! la 2ème fois, client = 0 !
    // Alors on filtre.
    if (client != nullptr) {
        QThread *gthc = client->thread(); // on récupère le thread qui a envoyé le signal
        int pos = _listeThread.indexOf(gthc); // on cherche la position
        if (pos > -1) {  // s'il existe
            _listeThread.at(pos)->quit();  // demande au thread de se terminer
            _listeThread.at(pos)->wait();  // attends la fin de la boucle événements
            // effacement de la liste des objets dépendant du client
            // client s'effacera automatiquement avec le thread.
            _listeThread.removeAt(pos);
            _listeClient.removeAt(pos);//on enleve l'addresse des objects des listes qui les stockait
        } // if pos
        emit sig_info("CGererServeur::on_disconnected : Nb client restant : "+QString::number(_listeClient.size()));
    } // if 0
}

void CGererServeur::on_erreur(QString mess)
{
    emit sig_erreur(mess);
}

void CGererServeur::on_info(QString mess)
{
    emit sig_info(mess);
}

