#ifndef CATEGORIE_INCLUDED
#define CATEGORIE_INCLUDED

#include <string>
#include <sqlite3.h>

class Categorie {
public:

    Categorie(const std::string& theme );


    Categorie creerCategorie(sqlite3* db, const std::string& theme);
    void editerCategorie(sqlite3* db);
    void supprimerCategorie(sqlite3* db);
    int getIdByName(sqlite3* db, const std::string& nom);
    void listeCategorie(sqlite3*db);

    int getId() const;
    std::string getTheme() const;

private:
    std::string theme;
};


#endif // CATEGORIE_INCLUDED
