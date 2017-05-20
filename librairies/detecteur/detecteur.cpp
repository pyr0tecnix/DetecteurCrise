/*detecteur.cpp
Dernière modification : 16/01/17
© Patrice Vieyra - contact@magicofthingMoTSerial::fr

Librairie ayant pour but de gérer le détecteur.

Structure d'une ligne -> JJMMAAHHMM AXAYAZGXGYGZ
*/

#include "detecteur.h"
int16_t Detecteur::_ax = 0;
int16_t Detecteur::_ay = 0;
int16_t Detecteur::_az = 0;
int16_t Detecteur::_gx = 0;
int16_t Detecteur::_gy = 0;
int16_t Detecteur::_gz = 0;

char Detecteur::_buffer[BUFFERSIZE];
unsigned int Detecteur::_cpt = 0;
unsigned int debug = 0;
char _convertedValue[4];
Detecteur::Detecteur() {}


void Detecteur::init() {
  /*Initialisation de la liaison série*/
  MoTSerial::begin(115200);
  MoTSerial::setVerboseLevel(DEBUG);
  MoTSerial::print("Initialisation de l'application..", INFO, false);

  /*Initialisation de la mémoire*/
  MoTStorage::init();

  /*Initialisation de l'accéléromètre / gyroscope*/
  MoTMPU6050::init();

  /*Initialisation de la RTC*/
  MoTRTC::init();

  /*Initialisation du WiFI*/
  MoTWIFI::init("MoTDetecteur", "", AP);

  /*Initialisation du Webserver*/
  DetecteurWebserver::init();

  MoTSerial::print("ok", INFO, true);
  /*Boucle de maintien du WiFi*/
  while(millis() < 100000) {
    DetecteurWebserver::run();
    yield();
  }
  MoTWIFI::off();
  MoTSerial::print("Désactivation du WiFI.\nLancement de l'application", INFO, true);

}

void Detecteur::run() {
  for(_cpt = 0; _cpt < NBSAMPLE; _cpt++) {
    MoTMPU6050::getData(&_ax, &_ay, &_az, &_gx, &_gy, &_gz);
    yield();
    strcat(_buffer, MoTRTC::getDateTime());
    strcat(_buffer, " ");
    strcat(_buffer, intToCharArray(_ax));
    strcat(_buffer, " ");
    strcat(_buffer, intToCharArray(_ay));
    strcat(_buffer, " ");
    strcat(_buffer, intToCharArray(_az));
    strcat(_buffer, " ");
    strcat(_buffer, intToCharArray(_gx));
    strcat(_buffer, " ");
    strcat(_buffer, intToCharArray(_gy));
    strcat(_buffer, " ");
    strcat(_buffer, intToCharArray(_gz));
    strcat(_buffer, "\r\n");
    }
  Serial.println(debug);
  MoTStorage::append("/data.txt", _buffer);
  Serial.println(_buffer);
  yield();
  /*On vide le buffer*/
  _buffer[0] = (char)0;
  debug++;
}

char* Detecteur::intToCharArray(int value) {
  _convertedValue[0] = (char)0;
  sprintf(_convertedValue, "%d", value);
  return _convertedValue;
}
