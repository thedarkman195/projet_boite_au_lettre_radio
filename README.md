# Projet : Système de Boîte aux Lettres Radio avec Détection de Courrier

## Description

Ce projet consiste en la réalisation d'un **système de boîte aux lettres radio** permettant de détecter la présence de courrier et de surveiller le niveau de batterie. Le système utilise deux Raspberry Pi avec deux applications distinctes : une **application émettrice** installée sur la boîte aux lettres, et une **application réceptrice** installée à l'intérieur de la maison.

- **Application Émettrice :** Elle détecte la présence de courrier grâce à un **capteur de poids** (peson) et surveille le niveau de batterie. Les données sont envoyées via un module radio au Raspberry Pi récepteur.
- **Application Réceptrice :** Elle reçoit les données envoyées par l'émetteur et les affiche sur un **écran LCD**.

## Fonctionnalités

### Application Émettrice
- Détection de courrier à l'aide d'un capteur de poids.
- Surveillance du niveau de batterie.
- Envoi des données (courrier et batterie) via un module radio.

### Application Réceptrice
- Affichage des données sur un écran LCD.
- Réception en continu des informations envoyées par l'émetteur.

## Matériel Utilisé

- 2x **Raspberry Pi** (un pour l’émetteur et un pour le récepteur)
- 1x **Capteur de poids** (peson)
- 1x **Écran LCD**
- **Modules de communication radio** (ex : modules RF 433 MHz)
- **Capteur de niveau de batterie** (ou un script de surveillance)

## Installation

### Prérequis
- Un système Raspberry Pi avec Raspberry Pi OS.
- Installation de **C++** et **WiringPi**.

### Compilation
Clonez ce dépôt sur chaque Raspberry Pi, puis compilez les fichiers C++ :

```bash
g++ -o emetteur emetteur.cpp
g++ -o recepteur recepteur.cpp


Voici le texte avec la mise en page correcte et un format simple à copier :

```
## Exécution

### Sur l’émetteur :
```bash
./emetteur
```

### Sur le récepteur :
```bash
./recepteur
```

## Dépendances

- **WiringPi** pour la gestion des GPIOs sur le Raspberry Pi.

### Installation de WiringPi :
```bash
sudo apt-get install wiringpi
```

## Schéma du Système

### Boîte aux Lettres (Émetteur)
- Capteur de poids connecté au Raspberry Pi via GPIO.
- Module radio émetteur connecté au Raspberry Pi.
- Capteur de batterie ou surveillance via script.

### Récepteur (Maison)
- Module radio récepteur connecté au Raspberry Pi.
- Écran LCD connecté via GPIO ou I2C pour afficher les informations.

## Fonctionnement

### Détection de Courrier
- Le capteur de poids détecte le courrier et envoie l'information au Raspberry Pi récepteur via le module radio.

### Surveillance de la Batterie
- Le niveau de batterie est surveillé, et un signal est envoyé en cas de batterie faible.

### Communication
- Les deux Raspberry Pi communiquent via un module radio, et les données sont affichées en temps réel sur le récepteur.

## Améliorations Futures
- Interface web pour consulter l'état de la boîte aux lettres à distance.
- Optimisation de la consommation énergétique de l’émetteur.
- Utilisation de la technologie LoRa pour une portée plus longue.

## Auteurs
- **Pinto Alexy**
- **Contact :** alexy.pinto@epitech.eu


