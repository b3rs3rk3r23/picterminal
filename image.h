#ifndef IMAGE_INCLUDED
#define IMAGE_INCLUDED

#include <string>
#include <sqlite3.h>

class Image {
public:
    Image() = default;
    Image(const std::string& chemin_Fichier, const std::string& titre, const std::string& description, int id_utilisateur, int id_Categorie, bool is_favoris);

    void soumettreImage(sqlite3* db);
    void voirMesImage(sqlite3* db);
    void ajouterAuxFavoris();


private:
    std::string chemin_Fichier;
    std::string titre;
    std::string description;
    bool is_favoris;
    int id_utilisateur;
    int id_Categorie;
    std::string statut;
};
#endif // IMAGE_INCLUDED
