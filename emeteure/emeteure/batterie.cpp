#include "batterie.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>

batterie::batterie(int address) : fd(wiringPiI2CSetup(address)) {
    if (fd < 0) {
        // Vous pouvez choisir de gérer l'erreur différemment ici
        std::cerr << "Erreur initialisation du bus I2C !" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int batterie::readAIN1() {
    return wiringPiI2CReadReg8(fd, AIN0);
}

batterie::~batterie() {
    // Libération des ressources à la fin
    // Cela pourrait inclure la fermeture du fichier I2C, par exemple
}
