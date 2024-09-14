#include "CSV.h"

// Constructeur
CSV::CSV() {
    // Ouvrir le fichier CSV en mode ajout (append) lors de la création de l'instance de la classe
    fichier.open("historique.csv", std::ios::app);

    // Vérifier si le fichier est ouvert avec succès
    if (!fichier.is_open()) {
        std::cerr << "Copier sur le csv" << std::endl;
    }
}

// Destructeur
CSV::~CSV() {
    // Fermer le fichier lors de la destruction de l'instance de la classe
    if (fichier.is_open()) {
        fichier.close();
    }
}

// Méthode pour écrire dans le fichier CSV
void CSV::ecrireDansCSV(char val, char* date) {
    // Vérifier si le fichier est ouvert avec succès avant d'écrire
    if (fichier.is_open()) {
        // Écrire les données dans le fichier
        if (val == '1')
        {
            fichier << date << "," << "courrier recue\n" << std::endl;
        }
        else if (val == 'b')
        {
            fichier << date << "," << "batterie faible\n " << std::endl;
        }

        else if (val == 'a')
        {
            fichier << date << "," << "batterie ok\n " << std::endl;
        }


        /* fichier << date_heure << "," << data << "," << batterie << "\n";

         std::cout << "Données écrites avec succès dans le fichier CSV." << std::endl;
     }*/
        else {
            std::cerr << "Erreur lors de l'ouverture du fichier CSV." << std::endl;
        }
    }
}
