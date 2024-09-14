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
    // Configuration initiale de WiringPi pour accéder aux broches GPIO sur Raspberry Pi
    wiringPiSetup();

    // Instanciation d'un objet CLCD pour la gestion de l'afficheur LCD
    CLCD Afficheur;

    // Instanciation d'un objet CRadio pour la gestion de la communication série
    // avec le port /dev/ttyUSB0 à une vitesse de 19200 bauds
    CRadio maRadio("/dev/ttyUSB0", 19200);

    // Vérification si l'ouverture du port série s'est effectuée correctement
    if (!maRadio.IsOpen()) {
        std::cerr << "Erreur lors de l'ouverture du port série." << std::endl;
        return 1;
    }

    // Boucle principale du programme
    while (true) {
        // Lecture d'un caractère depuis le port série
        char data = maRadio.readChar();

        // Vérification si un caractère valide a été lu
        if (data != '\0') {
            // Affichage du caractère sur l'écran LCD
            Afficheur.Affichelcd(data);

            // Affichage du caractère reçu sur la sortie standard
            std::cout << "Caractère reçu : " << data << std::endl;
        }
    }

    // Le programme ne devrait jamais atteindre ce point, mais on retourne 0 pour indiquer une sortie normale
    return 0;
}
