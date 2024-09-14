#include <iostream>
#include <wiringPi.h>
#include "PCF8591.h"  
#define SEUIL_TENSION 0x7f
int test = 0;
int main() {
	// Création de l'objet PCF8591
	PCF8591 pcf(0x48);

	// Affichage d'un message d'accueil
	std::cout << "Lecture Tension AIN1 - PCF8591\nFin par Ctrl-C\n";
	for (;;)
	{
		// Boucle principale
		if (test != pcf.readAIN1()) {

			// Lecture valeur numérique AIN1
			int hexaAIN2 = pcf.readAIN1();
			test = pcf.readAIN1();

			// Affichage tension hexadécimale
			std::cout << "Valeur hexadécimale AIN1: 0x" << std::hex << hexaAIN2 << std::dec << std::endl;

			// Lecture toutes les secondes


			if (hexaAIN2 > 0x59)
			{
				printf("Votre batterie est chargé\n");
			}
			else
			{
				printf("Votre batterie est déchargé\n");
			}
		}
	}

	return 0;
}