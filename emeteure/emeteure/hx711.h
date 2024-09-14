#pragma once
#ifndef HX711_H
#define HX711_H // PESON

/* DECLARATION DES CONSTANTES */
/* Définition des entrées sorties */
#define    DOUT    4   //GPIO23
#define SCK 	5   //GPIO24

/* DECLARATIONS DES VARIABLES GLOBALES*/


/* DECLARATION DES FONCTIONS */
long readHx711(void);
long read_averageHx711(int);

#endif

