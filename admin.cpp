#include "admin.h"
#include "categorie.h"
#include <iostream>
#include "admin.h"
#include "categorie.h"
#include <iostream>

Administrateur::Administrateur(int id, const std::string& username, const std::string& password)
    : Utilisateur(id, username, password, true) {}

void Administrateur::menuAdmin(sqlite3* db) {
    int choices;
    std::string theme;

    while (true) {
        std::cout << "\n\t\t\t_______________ MENU ADMINISTRATEUR ________________________\n\n";
        std::cout << "\t| 1. Créer catégorie                                  |" << std::endl;
        std::cout << "\t| 2. Éditer catégorie                                 |" << std::endl;
        std::cout << "\t| 3. Consulter les catégories                         |" << std::endl;
        std::cout << "\t| 4. Supprimer catégorie                              |" << std::endl;
        std::cout << "\t| 5. Soumission des utilisateurs                      |" << std::endl;
        std::cout << "\t| 6. Statistiques                                     |" << std::endl;
        std::cout << "\t| 7. Se déconnecter                                   |" << std::endl;
        std::cout << "\n\t\t\t Entrez votre choix : ";
        std::cin >> choices;
        std::cout << std::endl;

        switch (choices) {
            case 1:{
                std::cout << "Nom ou thème de la catégorie:" << std::endl;
                std::cin >> theme;
                {
                    Categorie nouvelleCategorie(theme);
                    std::cout << "Catégorie créée avec succès : " << nouvelleCategorie.getTheme() << std::endl;
                }
                break;
                }
            case 2:{
                Categorie new_categorie("");
                new_categorie.editerCategorie(db);
                break;
                }
            case 3:{
                Categorie categorie("");
                categorie.listeCategorie(db);
                break;
                }
            case 4:{
                std::cout << "Entrez le nom de la catégorie à supprimer : ";
                std::cin >> theme;
                Categorie categori("");
                categori.supprimerCategorie(db);
                break;
                }
            case 7:
                std::cout << "Déconnexion..." << std::endl;
                return;
            default:
                std::cout << "Choix invalide!" << std::endl;
                break;
        }
    }
}
