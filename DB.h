#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED


#include <sqlite3.h>
#include <string>

class Database {
private:
    sqlite3* db;
    std::string dbName;

public:
    // Constructeur et destructeur
    Database(const std::string& dbName);
    ~Database();

    // Méthodes de gestion de la base de données
    bool open(const std::string& dbName); // Ouvrir la connexion
    void close();                         // Fermer la connexion

    bool sql_requete(const std::string& query);
    bool table_user();
    bool table_image();
    bool table_categories();
    bool table_galerie();
    bool table_statistique();
    sqlite3* getDatabase() const;
};

#endif // DB_H_INCLUDED
