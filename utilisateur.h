#ifndef UTILISATEUR_INCLUDED
#define UTILISATEUR_INCLUDED


#include <string>
#include <sqlite3.h>

class Utilisateur{
private:
    int id;
    std::string username;
    std::string password;
    bool is_admin;

public:
    Utilisateur(int id, const std::string& username, const std::string& password, bool is_admin = false) ;

    bool login(sqlite3 *db, std::string& username, std::string& password);

    bool registerUser(sqlite3 *db);

    bool reset_passwd(sqlite3 *db, std::string& username);

    void menu_utilisateur(sqlite3* db);

    std::string getUsername() const;

    std::string getPassword() const;
};

#endif // UTILISATEUR_INCLUDED
