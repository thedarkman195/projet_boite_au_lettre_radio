#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <mcp23017.h>
#include <lcd.h>
#include "lcd-adafruit.c"
#include "lcd-adafruit.h"
#include "CLCD.h"

CLCD::CLCD()
{
    // Initialisation d'une variable de couleur pour l'écran LCD
    int colour = 1;

    // Configuration des broches pour le MCP23017
    mcp23017Setup(AF_BASE, 0x20);

    // Configuration de l'écran LCD avec la couleur spécifiée
    adafruitLCDSetup(colour);
}

CLCD::~CLCD()
{
    // Destructeur de la classe CLCD
    // Aucune action spécifique n'est nécessaire pour l'instant
}

void CLCD::Affichelcd(char vall)
{
    // Fonction pour afficher du texte sur l'écran LCD en fonction de la valeur passée en paramètre

    if (vall == '0')
    {
        // Affichage d'un message en cas d'absence de courrier
        lcdPosition(lcdHandle, 0, 0);
        lcdPuts(lcdHandle, "pas de courrier ");
    }
    else if(vall=='1')
    {
        // Affichage d'un message en cas de présence de courrier
        lcdPosition(lcdHandle, 0, 0);
        lcdPuts(lcdHandle, "courrier present");
    }
    else if(vall=='a')
    {
        // Affichage d'un message en cas de batterie OK
        lcdPosition(lcdHandle, 0, 1);
        lcdPuts(lcdHandle, "batterie ok     ");
    }
    else if(vall=='b')
    {
        // Affichage d'un message en cas de batterie faible
        lcdPosition(lcdHandle, 0, 1);
        lcdPuts(lcdHandle, "batterie faible ");
    }
}

void CLCD::Clear()
{
    // Fonction pour effacer le contenu de l'écran LCD
    lcdClear(lcdHandle);
}
