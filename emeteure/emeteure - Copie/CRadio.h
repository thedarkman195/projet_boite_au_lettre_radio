#pragma once
#ifndef CRADIO_H
#define CRADIO_H

#include <string>

class CRadio {
public:
    CRadio(std::string deviceName, int baud);
    ~CRadio();

    void Close(); // Ferme le port s�rie
    bool Open(std::string deviceName, int baud); // Ouvre le port s�rie avec le nom du p�riph�rique et la vitesse en bauds
    bool IsOpen(); // V�rifie si le port s�rie est ouvert
    bool Send(unsigned char* data, int len); // Envoie un tableau d'octets sur le port s�rie
    bool Send(unsigned char value); // Envoie un octet sur le port s�rie
    bool Send(std::string value); // Envoie une cha�ne de caract�res sur le port s�rie
    int Receive(unsigned char* data, int len); // Re�oit un nombre sp�cifi� d'octets depuis le port s�rie
    bool NumberByteRcv(int& bytelen); // R�cup�re le nombre d'octets disponibles pour la lecture
    char readChar(); // Lit un caract�re unique depuis le port s�rie

private:
    int handle; // Identifiant du fichier du port s�rie
    std::string deviceName; // Nom du p�riph�rique du port s�rie
    int baud; // Vitesse en bauds
};

#endif  // CRADIO_H




