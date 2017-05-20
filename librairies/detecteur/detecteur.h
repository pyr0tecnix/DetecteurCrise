/*detecteur.h
Dernière modification : 16/01/17
© Patrice Vieyra - contact@magicofthings.fr

Librairie ayant pour but de gérer le détecteur.
*/

#ifndef detecteur
#define detecteur

#include <SPI.h>
#include <ArduinoJson.h>
#include <moTSerial.h>
#include <moTStorage.h>
#include <moTRTC.h>
#include <moTMPU6050.h>
#include <moTWIFI.h>
#include <detecteur_webserver.h>


#define BUFFERSIZE 6000
#define NBSAMPLE 50 //50Hz

class Detecteur {

  public:

    /*Constructeur*/
    Detecteur();
    static void init();
    static void run();
    static char* intToCharArray(int value);

  private:
    static int16_t _ax, _ay, _az;
    static int16_t _gx, _gy, _gz;
    static char _buffer[];
    static unsigned int _cpt;
};
#endif
