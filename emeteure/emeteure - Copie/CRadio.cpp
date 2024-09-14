extern "C" {
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
}
#include <iostream>
using namespace std;

#include "CRadio.h"

CRadio::CRadio(std::string deviceName, int baud) : handle(-1) {
    Open(deviceName, baud);
}

CRadio::~CRadio() {
    if (handle >= 0) {
        Close();
    }
}

void CRadio::Close() {
    if (handle >= 0) {
        close(handle);
    }
    handle = -1;
}

bool CRadio::Open(std::string deviceName, int baud) {
    struct termios tio;
    struct termios2 tio2;
    this->deviceName = deviceName;
    this->baud = baud;
    handle = open(this->deviceName.c_str(), O_RDWR | O_NOCTTY);

    if (handle < 0) {
        return false;
    }

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

    // flush buffer
    ioctl(handle, TCFLSH, TCIOFLUSH);

    return true;
}

bool CRadio::IsOpen() {
    return (handle >= 0);
}

bool CRadio::Send(unsigned char* data, int len) {
    if (!IsOpen()) {
        return false;
    }
    int rlen = write(handle, data, len);
    return (rlen == len);
}

bool CRadio::Send(unsigned char value) {
    if (!IsOpen()) {
        return false;
    }
    int rlen = write(handle, &value, 1);
    return (rlen == 1);
}

bool CRadio::Send(std::string value) {
    if (!IsOpen()) {
        return false;
    }
    int rlen = write(handle, value.c_str(), value.size());
    return (rlen == value.size());
}

int CRadio::Receive(unsigned char* data, int len) {
    if (!IsOpen()) {
        return -1;
    }

    // this is a blocking receive
    int lenRCV = 0;
    while (lenRCV < len) {
        int rlen = read(handle, &data[lenRCV], len - lenRCV);
        lenRCV += rlen;
    }
    return lenRCV;
}

bool CRadio::NumberByteRcv(int& bytelen) {
    if (!IsOpen()) {
        return false;
    }
    ioctl(handle, FIONREAD, &bytelen);
    return true;
}

char CRadio::readChar() {
    if (!IsOpen()) {
        std::cerr << "Le port série n'a pas été initialisé." << std::endl;
        return '\0';
    }

    // Lire un caractère
    char data;
    int bytesRead = read(handle, &data, 1);

    if (bytesRead == 1) {
        return data;
    }
    else {
        return '\0'; // Retourner un caractère nul en cas d'erreur de lecture
    }
}

