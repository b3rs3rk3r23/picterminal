#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include <string>
#include <sqlite3.h>
#include "utilisateur.h"
#include "DB.h"

class Administrateur : public Utilisateur {
public:
    Administrateur(int id, const std::string& username, const std::string& password);
    void menuAdmin(sqlite3* db);
};


#endif // ADMIN_H_INCLUDED
