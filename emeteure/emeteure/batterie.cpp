#include "batterie.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>

batterie::batterie(int address) : fd(wiringPiI2CSetup(address)) {
    if (fd < 0) {
        // Vous pouvez choisir de g�rer l'erreur diff�remment ici
        std::cerr << "Erreur initialisation du bus I2C !" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int batterie::readAIN1() {
    return wiringPiI2CReadReg8(fd, AIN0);
}

batterie::~batterie() {
    // Lib�ration des ressources � la fin
    // Cela pourrait inclure la fermeture du fichier I2C, par exemple
}
