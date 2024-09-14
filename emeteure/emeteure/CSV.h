#pragma once
#ifndef GESTIONNAIRE_CSV_H
#define GESTIONNAIRE_CSV_H

#include <iostream>
#include <fstream>
#include <string>

class CSV {
public:
    // Constructeur
    CSV();

    // Destructeur
    ~CSV();

    // Méthode pour écrire dans le fichier CSV
    void ecrireDansCSV(char, char*);

private:
    std::ofstream fichier; // Le fichier CSV
};

#endif // GESTIONNAIRE_CSV_H

