#pragma once
// Directive de préprocesseur pour éviter les inclusions multiples du fichier d'en-tête

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
// Inclusions des fichiers d'en-tête des bibliothèques standard du langage C

#include <wiringPi.h>
#include <mcp23017.h>
#include <lcd.h>
// Inclusions des fichiers d'en-tête spécifiques à WiringPi, MCP23017 et LCD

#include "lcd-adafruit.h"
// Inclusion du fichier d'en-tête local "lcd-adafruit.h"

class CLCD
{
	char TexteAfficher;
	// Membre privé de la classe pour stocker le texte à afficher sur l'écran LCD

public:
	CLCD();
	// Constructeur de la classe

	~CLCD();
	// Destructeur de la classe

	void Affichelcd(char val);
	// Fonction publique pour afficher du texte sur l'écran LCD
	// Prend un argument de type char pour le texte à afficher

	void Clear();
	// Fonction publique pour effacer le contenu de l'écran LCD
};
