#pragma once
// Directive de pr�processeur pour �viter les inclusions multiples du fichier d'en-t�te

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
// Inclusions des fichiers d'en-t�te des biblioth�ques standard du langage C

#include <wiringPi.h>
#include <mcp23017.h>
#include <lcd.h>
// Inclusions des fichiers d'en-t�te sp�cifiques � WiringPi, MCP23017 et LCD

#include "lcd-adafruit.h"
// Inclusion du fichier d'en-t�te local "lcd-adafruit.h"

class CLCD
{
	char TexteAfficher;
	// Membre priv� de la classe pour stocker le texte � afficher sur l'�cran LCD

public:
	CLCD();
	// Constructeur de la classe

	~CLCD();
	// Destructeur de la classe

	void Affichelcd(char val);
	// Fonction publique pour afficher du texte sur l'�cran LCD
	// Prend un argument de type char pour le texte � afficher

	void Clear();
	// Fonction publique pour effacer le contenu de l'�cran LCD
};
