#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <mcp23017.h>
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include "CRadio.h"
#include "hx711.h" // Bibliothèque pour le capteur de poids HX711
#include "batterie.h"
#include "CSV.h"

int main(void)
{
    // Initialisation des variables
    long tar;
    long rep = 100;
    char temp = 'n';
    CSV historique;
    batterie bat(0x48);
    long mesure = 100;
    CRadio MaRadio("/dev/ttyUSB0", 19200);

    // Initialisation de la bibliothèque WiringPi
    printf("teste assemblage\n");
    wiringPiSetup();
    pinMode(SCK, OUTPUT);
    pinMode(DOUT, INPUT);
    digitalWrite(DOUT, HIGH);
    digitalWrite(SCK, LOW);
    
    tar = read_averageHx711(50) / 100;
    
    // Boucle principale du programme
    for (;;)
    {
        // Mesure de la masse
        mesure = read_averageHx711(10) / 100 - tar;
        printf("mesure de la masse\n");

        // Vérification des changements dans la mesure de la masse
        if (mesure != rep)
        {         
            delay(2000);
            rep = mesure;
            printf("masse : %ld\n", mesure);

            // Vérification de la présence de courrier
            if (mesure > 30)
            {
                printf("il y a du courrier");
                MaRadio.Send("1");

                // Enregistrement de la date et heure actuelles
                struct tm* tm;
                time_t now = time(NULL);
                tm = localtime(&now);
                char date_heure[20];
                strftime(date_heure, sizeof(date_heure), "%d/%m/%Y %H:%M:%S", tm);
                printf("(%s)\n", date_heure);

                // Enregistrement de l'envoi dans le fichier CSV
                std::cerr << "Envoi :  " << '1' << std::endl;
                std::ofstream fichier("historique.csv", std::ios::app);
                historique.ecrireDansCSV('1', date_heure);
            }
            else
            {
                printf("il n'y a pas de courrier\n");
                MaRadio.Send("0");

                // Enregistrement de la date et heure actuelles
                struct tm* tm;
                time_t now = time(NULL);
                tm = localtime(&now);
                char date_heure[20];
                strftime(date_heure, sizeof(date_heure), "%d/%m/%Y %H:%M:%S", tm);
                printf("(%s)\n", date_heure);

                // Enregistrement de l'envoi dans le fichier CSV
                std::cerr << "Envoi :  " << '1' << std::endl;
            }
        }

        // Vérification du niveau de batterie
        if (bat.readAIN1() >= 0xBB)
        {
            

            delay(2000);
            if (temp != '0')
            {
                temp = '0';
                printf("batterie ok\n");
                MaRadio.Send('a');

                // Enregistrement de la date et heure actuelles
                struct tm* tm;
                time_t now = time(NULL);
                tm = localtime(&now);
                char date_heure[20];
                strftime(date_heure, sizeof(date_heure), " %d/%m/%Y %H:%M:%S", tm);
                printf("(%s)\n", date_heure);

                // Enregistrement de l'envoi dans le fichier CSV
                std::cerr << "Envoi :  " << 'a' << std::endl;
                std::ofstream fichier("historique.csv", std::ios::app);
                historique.ecrireDansCSV('a', date_heure);
            }
        }

        // Vérification de la batterie faible
        if (bat.readAIN1() < 0xBB)
        {
            delay(2000);
            if (temp != '1')
            {
                temp = '1';
                printf("batterie faible\n");
                MaRadio.Send('b');

                // Enregistrement de la date et heure actuelles
                struct tm* tm;
                time_t now = time(NULL);
                tm = localtime(&now);
                char date_heure[20];
                strftime(date_heure, sizeof(date_heure), " %d/%m/%Y %H:%M:%S", tm);
                printf("(%s)\n", date_heure);

                // Enregistrement de l'envoi dans le fichier CSV
                std::cerr << "Envoi :  " << 'b' << std::endl;
                std::ofstream fichier("historique.csv", std::ios::app);
                historique.ecrireDansCSV('b', date_heure);
            }
        }
    }
}
