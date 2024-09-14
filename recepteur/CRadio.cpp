#include "CRadio.h"
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

CRadio::CRadio(std::string deviceName, int baud) : handle(-1) {
    // Constructeur de la classe CRadio, initialise handle à -1
    // et ouvre la communication série avec le périphérique spécifié
    Open(deviceName, baud);
}

CRadio::~CRadio() {
    // Destructeur de la classe CRadio, ferme la communication série si elle est ouverte
    if (handle >= 0) {
        Close();
    }
}

void CRadio::Close() {
    // Fonction pour fermer la communication série
    if (handle >= 0) {
        close(handle);
    }
    handle = -1;
}

bool CRadio::Open(std::string deviceName, int baud) {
    // Fonction pour ouvrir la communication série avec le périphérique spécifié
    struct termios tio;
    struct termios2 tio2;
    this->deviceName = deviceName;
    this->baud = baud;
    handle = open(this->deviceName.c_str(), O_RDWR | O_NOCTTY);

    if (handle < 0) {
        return false;
    }

    // Configuration des paramètres de la communication série
    tio.c_cflag = CS8 | CLOCAL | CREAD;
    tio.c_oflag = 0;
    tio.c_lflag = 0;       // ICANON;
    tio.c_cc[VMIN] = 0;
    tio.c_cc[VTIME] = 1;    // time out every .1 sec
    ioctl(handle, TCSETS, &tio);

    ioctl(handle, TCGETS2, &tio2);
    tio2.c_cflag &= ~CBAUD;
    tio2.c_cflag |= BOTHER;
    tio2.c_ispeed = baud;
    tio2.c_ospeed = baud;
    ioctl(handle, TCSETS2, &tio2);

    // Vidange du tampon
    ioctl(handle, TCFLSH, TCIOFLUSH);

    return true;
}

bool CRadio::IsOpen() {
    // Fonction pour vérifier si la communication série est ouverte
    return (handle >= 0);
}

bool CRadio::Send(unsigned char* data, int len) {
    // Fonction pour envoyer un tableau d'octets sur la communication série
    if (!IsOpen()) {
        return false;
    }
    int rlen = write(handle, data, len);
    return (rlen == len);
}

bool CRadio::Send(unsigned char value) {
    // Fonction pour envoyer un octet sur la communication série
    if (!IsOpen()) {
        return false;
    }
    int rlen = write(handle, &value, 1);
    return (rlen == 1);
}

bool CRadio::Send(std::string value) {
    // Fonction pour envoyer une chaîne de caractères sur la communication série
    if (!IsOpen()) {
        return false;
    }
    int rlen = write(handle, value.c_str(), value.size());
    return (rlen == value.size());
}

int CRadio::Receive(unsigned char* data, int len) {
    // Fonction pour recevoir un nombre spécifié d'octets sur la communication série
    if (!IsOpen()) {
        return -1;
    }

    // Réception bloquante
    int lenRCV = 0;
    while (lenRCV < len) {
        int rlen = read(handle, &data[lenRCV], len - lenRCV);
        lenRCV += rlen;
    }
    return lenRCV;
}

bool CRadio::NumberByteRcv(int& bytelen) {
    // Fonction pour obtenir le nombre d'octets en attente de lecture dans le tampon
    if (!IsOpen()) {
        return false;
    }
    ioctl(handle, FIONREAD, &bytelen);
    return true;
}

char CRadio::readChar() {
    // Fonction pour lire un caractère de la communication série
    if (!IsOpen()) {
        std::cerr << "Le port série n'a pas été initialisé." << std::endl;
        return '\0';
    }

    // Lecture d'un caractère
    char data;
    int bytesRead = read(handle, &data, 1);

    if (bytesRead == 1) {
        return data;
    }
    else {
        return '\0'; // Retourner un caractère nul en cas d'erreur de lecture
    }
}
