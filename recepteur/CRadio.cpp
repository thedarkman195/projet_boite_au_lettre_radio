#include "CRadio.h"
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

CRadio::CRadio(std::string deviceName, int baud) : handle(-1) {
    // Constructeur de la classe CRadio, initialise handle � -1
    // et ouvre la communication s�rie avec le p�riph�rique sp�cifi�
    Open(deviceName, baud);
}

CRadio::~CRadio() {
    // Destructeur de la classe CRadio, ferme la communication s�rie si elle est ouverte
    if (handle >= 0) {
        Close();
    }
}

void CRadio::Close() {
    // Fonction pour fermer la communication s�rie
    if (handle >= 0) {
        close(handle);
    }
    handle = -1;
}

bool CRadio::Open(std::string deviceName, int baud) {
    // Fonction pour ouvrir la communication s�rie avec le p�riph�rique sp�cifi�
    struct termios tio;
    struct termios2 tio2;
    this->deviceName = deviceName;
    this->baud = baud;
    handle = open(this->deviceName.c_str(), O_RDWR | O_NOCTTY);

    if (handle < 0) {
        return false;
    }

    // Configuration des param�tres de la communication s�rie
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
    // Fonction pour v�rifier si la communication s�rie est ouverte
    return (handle >= 0);
}

bool CRadio::Send(unsigned char* data, int len) {
    // Fonction pour envoyer un tableau d'octets sur la communication s�rie
    if (!IsOpen()) {
        return false;
    }
    int rlen = write(handle, data, len);
    return (rlen == len);
}

bool CRadio::Send(unsigned char value) {
    // Fonction pour envoyer un octet sur la communication s�rie
    if (!IsOpen()) {
        return false;
    }
    int rlen = write(handle, &value, 1);
    return (rlen == 1);
}

bool CRadio::Send(std::string value) {
    // Fonction pour envoyer une cha�ne de caract�res sur la communication s�rie
    if (!IsOpen()) {
        return false;
    }
    int rlen = write(handle, value.c_str(), value.size());
    return (rlen == value.size());
}

int CRadio::Receive(unsigned char* data, int len) {
    // Fonction pour recevoir un nombre sp�cifi� d'octets sur la communication s�rie
    if (!IsOpen()) {
        return -1;
    }

    // R�ception bloquante
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
    // Fonction pour lire un caract�re de la communication s�rie
    if (!IsOpen()) {
        std::cerr << "Le port s�rie n'a pas �t� initialis�." << std::endl;
        return '\0';
    }

    // Lecture d'un caract�re
    char data;
    int bytesRead = read(handle, &data, 1);

    if (bytesRead == 1) {
        return data;
    }
    else {
        return '\0'; // Retourner un caract�re nul en cas d'erreur de lecture
    }
}
