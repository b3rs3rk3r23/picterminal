#include <iostream>
#include "image.h"

#include <string>

void Image::soumettreImage(sqlite3* db) {
    // Demande à l'utilisateur de saisir les détails de l'image
    std::string chemin_Fichier, titre, description;

    std::cout << "Entrez le chemin du fichier de l'image : ";
    std::cin.ignore(); // Ignore le caractère de nouvelle ligne restant
    std::getline(std::cin, chemin_Fichier);

    std::cout << "Entrez le titre de l'image : ";
    std::getline(std::cin, titre);

    std::cout << "Entrez la description de l'image : ";
    std::getline(std::cin, description);

    // Préparation de la requête SQL
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO images (chemin_fichier, titre, description, id_utilisateur) VALUES (?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Liaison des valeurs saisies à la requête SQL
    sqlite3_bind_text(stmt, 1, chemin_Fichier.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, titre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, id_utilisateur);

    // Exécution de la requête
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur lors de l'insertion de l'image : " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Image soumise avec succès !" << std::endl;
    }

    // Finalisation de la déclaration
    sqlite3_finalize(stmt);
}


void Image::voirMesImage(sqlite3* db){

}
