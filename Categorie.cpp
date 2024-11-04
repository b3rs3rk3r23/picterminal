#include <iostream>
#include "categorie.h"

Categorie::Categorie(const std::string& theme): theme(theme) {}


Categorie Categorie::creerCategorie(sqlite3* db, const std::string& theme) {
    Categorie nouvelleCategorie(theme);

    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO categories (theme) VALUES (?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête : " << sqlite3_errmsg(db) << std::endl;
        return Categorie("");
    }

    sqlite3_bind_text(stmt, 1, theme.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur lors de la création de la catégorie : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return Categorie("");
    }

    sqlite3_finalize(stmt);
    return nouvelleCategorie;
}


void Categorie::editerCategorie(sqlite3* db) {
    std::string themeActuel, new_theme;

    std::cout << "Entrez le nom de la catégorie que vous souhaitez modifier : ";
    std::cin >> themeActuel;

    int id = getIdByName(db, themeActuel);
    if (id == -1) {
        std::cerr << "La catégorie spécifiée n'existe pas." << std::endl;
        return;
    }

    std::cout << "Entrez le nouveau nom ou thème de la catégorie : ";
    std::cin >> new_theme;

    sqlite3_stmt* stmt;
    const char* sql = "UPDATE categories SET theme = ? WHERE id = ?"; // Utilisation de l'ID pour identifier la catégorie

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, new_theme.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur lors de la mise à jour de la catégorie : " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Catégorie mise à jour avec succès." << std::endl;
    }

    sqlite3_finalize(stmt);
}



void Categorie::supprimerCategorie(sqlite3* db) {
    std::string theme;
    std::cout << "Entrez le nom de la catégorie à supprimer : ";
    std::cin >> theme;

    int id = Categorie::getIdByName(db, theme); // Méthode à implémenter dans Categorie

    if (id != -1) { // Vérifier si la catégorie existe
        std::cout << "Catégorie non trouvée." << std::endl;
    }
    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM categories WHERE id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Lier l'ID à la requête
    sqlite3_bind_int(stmt, 1, id);

    // Exécuter la requête
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur lors de la suppression de la catégorie : " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Catégorie '" << theme << "' a été supprimée avec succès." << std::endl;
    }

    sqlite3_finalize(stmt);
}



int Categorie::getIdByName(sqlite3* db, const std::string& nom) {
    int id = -1;
    sqlite3_stmt* stmt;

    const char* sql = "SELECT id FROM categories WHERE theme = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête : " << sqlite3_errmsg(db) << std::endl;
        return id;
    }

    sqlite3_bind_text(stmt, 1, nom.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return id;
}

void Categorie::listeCategorie(sqlite3*db){
    sqlite3_stmt* stmt;

    const char* sql = "SELECT theme FROM categories";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* theme = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::cout << "- " << (theme ? theme : "Inconnu") << std::endl;
    }

    sqlite3_finalize(stmt);
}



std::string Categorie::getTheme() const { return theme; }
