#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <mcp23017.h>
#include <lcd.h>
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>

#include "lcd-adafruit.h"
#include "CLCD.h"
#include "CRadio.h"

int main()
{
    // Configuration initiale de WiringPi pour acc�der aux broches GPIO sur Raspberry Pi
    wiringPiSetup();

    // Instanciation d'un objet CLCD pour la gestion de l'afficheur LCD
    CLCD Afficheur;

    // Instanciation d'un objet CRadio pour la gestion de la communication s�rie
    // avec le port /dev/ttyUSB0 � une vitesse de 19200 bauds
    CRadio maRadio("/dev/ttyUSB0", 19200);

    // V�rification si l'ouverture du port s�rie s'est effectu�e correctement
    if (!maRadio.IsOpen()) {
        std::cerr << "Erreur lors de l'ouverture du port s�rie." << std::endl;
        return 1;
    }

    // Boucle principale du programme
    while (true) {
        // Lecture d'un caract�re depuis le port s�rie
        char data = maRadio.readChar();

        // V�rification si un caract�re valide a �t� lu
        if (data != '\0') {
            // Affichage du caract�re sur l'�cran LCD
            Afficheur.Affichelcd(data);

            // Affichage du caract�re re�u sur la sortie standard
            std::cout << "Caract�re re�u : " << data << std::endl;
        }
    }

    // Le programme ne devrait jamais atteindre ce point, mais on retourne 0 pour indiquer une sortie normale
    return 0;
}
