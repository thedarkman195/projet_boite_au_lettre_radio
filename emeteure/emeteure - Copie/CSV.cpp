#include "CSV.h"

// Constructeur
CSV::CSV() {
    // Ouvrir le fichier CSV en mode ajout (append) lors de la cr�ation de l'instance de la classe
    fichier.open("historique.csv", std::ios::app);

    // V�rifier si le fichier est ouvert avec succ�s
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

// M�thode pour �crire dans le fichier CSV
void CSV::ecrireDansCSV(char val, char* date) {
    // V�rifier si le fichier est ouvert avec succ�s avant d'�crire
    if (fichier.is_open()) {
        // �crire les donn�es dans le fichier
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

         std::cout << "Donn�es �crites avec succ�s dans le fichier CSV." << std::endl;
     }*/
        else {
            std::cerr << "Erreur lors de l'ouverture du fichier CSV." << std::endl;
        }
    }
}
