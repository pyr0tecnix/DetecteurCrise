/*detecteurWebserver.cpp
Dernière modification : 15/10/16
© Patrice Vieyra - contact@magicofthings.fr

Librairie ayant pour but de gérer le serveur web.

Méthodes
  Publiques

    - Constructeur : Instanciation de l'objet. Pas utilisé dans notre cas, la classe
      est statique
    - void init() : Initialise le serveur web et les différentes routes
    - void run() : Permet de recevoir les requêtes des navigateurs web. La méthode doit être appelée dans la méthode loop de l'ESP
	  - String getContentType(string filename) : Renvoie le type du fichier, text/html, image/png...
    - bool handleFileRead(String path) : Lit le fichier situé à l'adresse path
    - void handleFileUpload() : Permet d'uploader des fichiers sur la balle
*/

#include "detecteur_webserver.h"

DetecteurWebserver::DetecteurWebserver() {}

void DetecteurWebserver::init() {
  MoTWebserver::initBegin();
  _server.on("/getdata", HTTP_POST, handleSendData);
  _server.on("/delete", HTTP_POST, handleDeleteData);
  MoTWebserver::initEnd();
}

bool DetecteurWebserver::handleSendData() {
  MoTSerial::print("Envoie des données..", INFO, true);
  String contentType = getContentType("/data.txt");
  if(SPIFFS.exists("/data.txt")){
    File _file = SPIFFS.open("/data.txt", "r");
    size_t sent = _server.streamFile(_file, contentType);
    _file.close();
    MoTSerial::print("Ok", INFO, true);
    return true;
  }
  return false;
}

bool DetecteurWebserver::handleDeleteData() {
  MoTSerial::print("Suppression des données..", INFO, true);
  MoTSerial::print("Ok", INFO, true);
  return SPIFFS.remove("/data.txt");
}

void DetecteurWebserver::run() {
  MoTWebserver::run();
}

String DetecteurWebserver::getContentType(String filename){
  MoTSerial::print(filename, INFO, true);
  return MoTWebserver::getContentType(filename);
}

bool DetecteurWebserver::handleFileRead(String path){
  MoTSerial::print(path, INFO, true);
  return MoTWebserver::handleFileRead(path);
}

void DetecteurWebserver::handleFileUpload(){
  return MoTWebserver::handleFileUpload();
}
