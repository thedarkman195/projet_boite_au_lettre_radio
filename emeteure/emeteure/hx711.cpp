#include <stdio.h>
#include <wiringPi.h>
#include "hx711.h" // Bibliothèque pour le capteur de poids HX711

/* Mesure de la masse */
long readHx711()
{
    long mesure = 0;
    int i;

    // Attend que la broche DOUT soit basse
    while (digitalRead(DOUT));

    // Lecture des 24 bits de données du capteur
    for (i = 0; i < 24; i++)
    {
        // Active le signal d'horloge (SCK) et attend
        digitalWrite(SCK, HIGH);
        delayMicroseconds(1);

        // Décale les bits de mesure vers la gauche
        mesure = mesure << 1;

        // Désactive le signal d'horloge (SCK) et lit le bit de données
        digitalWrite(SCK, LOW);
        if (digitalRead(DOUT))
            mesure++;

        // Attend avant la prochaine lecture
        delayMicroseconds(1);
    }

    // Termine la séquence de lecture
    digitalWrite(SCK, HIGH);
    delayMicroseconds(1);
    digitalWrite(SCK, LOW);
    delayMicroseconds(1);

    // Inversion du bit de signe
    mesure ^= 0x800000;

    return (mesure);
}

/* Lecture moyenne de plusieurs mesures */
long read_averageHx711(int nb_mesures)
{
    long somme = 0;
    int i;

    // Effectue plusieurs mesures et les somme
    for (i = 0; i < nb_mesures; i++)
    {
        somme += readHx711();
    }

    // Calcule la moyenne des mesures
    return (somme / nb_mesures);
}
