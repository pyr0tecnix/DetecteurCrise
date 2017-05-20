/*detecteur_webserver.h
Dernière modification : 20/05/2017
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
    - void handleReadScript() : Permet de récupérer le script depuis le navigateur pour l'enregistrer sur la balle
    - void handleSendScript() : Permet de récupérer le script et de l'envoyer vers le navigateur
*/

#ifndef detecteurWebserver
#define detecteurWebserver


#include <moTWebserver.h>

class DetecteurWebserver : protected MoTWebserver {

  public:
    /*Constructeur*/
    DetecteurWebserver();
    static void init();
    static void run();

  private:
    static String getContentType(String filename);
    static bool handleFileRead(String path);
    static void handleFileUpload();
    static bool handleSendData();
    static bool handleDeleteData();

};


#endif
