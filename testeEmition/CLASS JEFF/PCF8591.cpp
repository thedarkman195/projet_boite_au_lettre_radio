#include "PCF8591.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>

PCF8591::PCF8591(int address) : fd(wiringPiI2CSetup(address)) {
    if (fd < 0) {
        // Vous pouvez choisir de gérer l'erreur différemment ici
        std::cerr << "Erreur initialisation du bus I2C !" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int PCF8591::readAIN1() {
    return wiringPiI2CReadReg8(fd, AIN0);
}

PCF8591::~PCF8591() {
    // Libération des ressources à la fin
    // Cela pourrait inclure la fermeture du fichier I2C, par exemple
}