#ifndef GALERIE_H_INCLUDED
#define GALERIE_H_INCLUDED

#include <string>
#include <vector>
#include "Image.h"

class Galerie {
public:

    Galerie(int id, int idUtilisateur, const std::string& nom);

    int getId() const;
    int getIdUtilisateur() const;
    std::string getNom() const;
    const std::vector<Image>& getImages() const;

    void ajouterImage(const Image& image);
    void supprimerImage(int imageId);

private:
    int id;
    int idUtilisateur;
    std::string nom;
    std::vector<Image> images;
};

#endif // GALERIE_H_INCLUDED
