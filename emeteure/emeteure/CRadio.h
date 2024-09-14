#pragma once
#ifndef CRADIO_H
#define CRADIO_H

#include <string>

class CRadio {
public:
    CRadio(std::string deviceName, int baud);
    ~CRadio();

    void Close(); // Ferme le port série
    bool Open(std::string deviceName, int baud); // Ouvre le port série avec le nom du périphérique et la vitesse en bauds
    bool IsOpen(); // Vérifie si le port série est ouvert
    bool Send(unsigned char* data, int len); // Envoie un tableau d'octets sur le port série
    bool Send(unsigned char value); // Envoie un octet sur le port série
    bool Send(std::string value); // Envoie une chaîne de caractères sur le port série
    int Receive(unsigned char* data, int len); // Reçoit un nombre spécifié d'octets depuis le port série
    bool NumberByteRcv(int& bytelen); // Récupère le nombre d'octets disponibles pour la lecture
    char readChar(); // Lit un caractère unique depuis le port série

private:
    int handle; // Identifiant du fichier du port série
    std::string deviceName; // Nom du périphérique du port série
    int baud; // Vitesse en bauds
};

#endif  // CRADIO_H




