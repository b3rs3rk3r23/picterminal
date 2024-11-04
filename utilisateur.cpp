#include "utilisateur.h"
#include <iostream>
#include <string>
#include "DB.h"
#include "image.h"


Utilisateur::Utilisateur(int id, const std::string& username, const std::string& password, bool is_admin):username(username), password(password), is_admin(is_admin) {}

bool Utilisateur::registerUser(sqlite3 *db) {
    std::cout << "Choisissez un nom d'utilisateur: ";
    std::cin >> this->username;
    std::cout << "Choisissez un mot de passe: ";
    std::cin >> this->password;

    // Note : Hasher le mot de passe ici avec une bibliothèque sécurisée

    std::string sql = "INSERT INTO utilisateurs (username, password, is_admin) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Associer les valeurs aux paramètres de la requête
    if (sqlite3_bind_text(stmt, 1, this->username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, this->password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 3, this->is_admin ? 1 : 0) != SQLITE_OK) {
        std::cerr << "Erreur lors de l'association des valeurs: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur lors de l'inscription: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    std::cout << "Inscription réussie !" << std::endl;
    return true;
}

bool Utilisateur::login(sqlite3 *db, std::string& username, std::string& password){
    bool is_authenticated = false;
    std::cout << "Entrez votre nom d'utilisateur: ";
    std::cin >> username;
    std::cout << "Entrez votre mot de passe: ";
    std::cin >> password;

    std::string sql = "SELECT id, is_admin FROM utilisateurs WHERE username = ? AND password = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur!!!! " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Associer les valeurs aux paramètres de la requête
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Exécuter la requête et vérifier les résultats

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        this->id = sqlite3_column_int(stmt, 0);
        this->is_admin = sqlite3_column_int(stmt, 1) == 1;
        is_authenticated = true;
    }

    // Finaliser la requête
    sqlite3_finalize(stmt);

    if (is_authenticated) {
        std::cout << "Connexion réussie !" << std::endl;
    } else {
        std::cout << "Nom d'utilisateur ou mot de passe incorrect." << std::endl;
    }

    return is_authenticated;
};

bool Utilisateur::reset_passwd(sqlite3 *db, std::string& username) {
    std::string newPassword;
    std::cout << "Entrez votre nouveau mot de passe: ";
    std::cin >> newPassword;

    // Note : Hasher le mot de passe ici

    std::string sql = "UPDATE utilisateurs SET password = ? WHERE username = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erreur lors de l'association des valeurs: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur lors de la mise à jour du mot de passe: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    std::cout << "Mot de passe réinitialisé avec succès." << std::endl;
    return true;
}

std::string Utilisateur::getUsername() const {
    return this->username;
}

std::string Utilisateur::getPassword() const {
    return this->password;
}

void Utilisateur::menu_utilisateur(sqlite3* db){
    int choix;
    do{
     std::cout << "\n\t\t\t_______________ MENU PRINCIPAL ________________________\n\n";
     std::cout << "\t| 1. Soumettre une nouvelle image                     |" << std::endl;
     std::cout << "\t| 2. Voir mes images                                  |" << std::endl;
     std::cout << "\t| 3. Consulter les catégories                         |" << std::endl;
     std::cout << "\t| 4. Ajouter aux favoris                              |" << std::endl;
     std::cout << "\t| 5. Se déconnecter                                   |" << std::endl;
     std::cout << "\n\t\t\t Entrez votre choix : ";
     std::cin >> choix;
     std::cout << std::endl;

    switch (choix) {
            case 1:{
                Image nouvelleImage;
                nouvelleImage.soumettreImage(db);
                break;
                }
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                std::cout << "\t\t\t Vous vous êtes déconnecté avec succès! \n\n";
                return;
            default:
                std::cout << "\t\t\t Choix invalide! Veuillez réessayer. \n" << std::endl;
        }
    } while (choix != 5);
}
