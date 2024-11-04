#include "DB.h"
#include <iostream>
#include <sqlite3.h>

using namespace std;

// Constructeur
Database::Database(const std::string& dbName) : db(nullptr), dbName(dbName) {
     if (!open(dbName)) {
        std::cerr << "Erreur : impossible d'ouvrir la base de données " << dbName << std::endl;
        // Vous pourriez lever une exception ici si nécessaire
    }
}

// Destructeur
Database::~Database() {
    close(); // S'assure que la base de données est fermée à la destruction
}

// Ouvrir la connexion à la base de données
bool Database::open(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        cerr << "Erreur lors de l'ouverture de la base de données : " << sqlite3_errmsg(db) << endl;
        return false;
    }
    cout << "Connexion à la base de données réussie." << endl;

    // Créer la table des utilisateurs si elle n'existe pas
    if (!table_user()) {
        cerr << "Erreur lors de la création de la table utilisateurs." << endl;
        return false;
    }

    return true;
}

// Fermer la connexion à la base de données
void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        cout << "Connexion à la base de données fermée." << endl;
    }
}

bool Database::sql_requete(const std::string& query) {
    char* errorMessage = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        cerr << "Erreur lors de l'exécution de la requête : " << errorMessage << endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}

// Création de la table utilisateurs
bool Database::table_user() {
    std::string requete_table_utilisateur = "CREATE TABLE IF NOT EXISTS utilisateurs ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "username TEXT UNIQUE, "
                                   "password TEXT, "
                                   "is_admin INTEGER);";
    return sql_requete(requete_table_utilisateur);
}

bool Database::table_galerie() {
    std::string requete_table_galerie = "CREATE TABLE IF NOT EXISTS categories ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "nom_galerie VARCHAR(255) NOT NULL, "
                            "id_utilisateur INT, "
                            "FOREIGN KEY (id_utilisateur) REFERENCES utilisateurs(id), "
                            "date_creation DATETIME DEFAULT CURRENT_TIMESTAMP);";
}

bool Database::table_categories(){
     std::string requete_table_categories = "CREATE TABLE IF NOT EXISTS categories ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "theme VARCHAR(255) NOT NULL, "
                            "date_creation DATETIME DEFAULT CURRENT_TIMESTAMP);";
    return sql_requete(requete_table_categories);
}

bool Database::table_image(){
    std::string requete_table_image = "CREATE TABLE IF NOT EXISTS image ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "nom_du_fichier VARCHAR(255) NOT NULL ,"
                            "nom_image VARCHAR(255) NOT NULL, "
                            "description TEXT, "
                            "is_favoris INT, "
                            "telechargement_date DATETIME DEFAULT CURRENT_TIMESTAMP, "
                            "id_utilisateur INT, "
                            "id_categorie INT, "
                            "FOREIGN KEY (id_utilisateur) REFERENCES utilisateurs(id), "
                            "FOREIGN KEY (id_categorie) REFERENCES categories(id), "
                            "statut TEXT CHECK(statut IN ('approuvée', 'en attente', 'rejetée')) DEFAULT 'en attente');";
    return sql_requete(requete_table_image);
}

bool Database::table_statistique(){
     std::string requete_table_statistique = "CREATE TABLE IF NOT EXISTS statistique ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "image_telecharger INT ,"
                            "image_populaire TEXT, "
                            "telechargement_categorie INT, "
                            "activite_users TEXT);";
    return sql_requete(requete_table_statistique);
}

// Retourner le pointeur de la base de données SQLite
sqlite3* Database::getDatabase() const {
    return db;
}

