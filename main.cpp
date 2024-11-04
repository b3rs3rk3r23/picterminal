#include <iostream>
#include "utilisateur.h"
#include "DB.h"
#include "categorie.h"
#include "admin.h"

using namespace std;

int main()
{
    Database db("test.db");
    int choice;
    std::string username, password;

    Utilisateur user(0, username, password, false);
    Administrateur admin(1, "admin", "password");
    cout << "\n\t\t\t_______________ WELCOME TO THE LOGIN PAGE ________________________\n\n";

    cout << "\n\t\t\t_______________       MENU      ________________________\n\n";

    cout << "\t| PRESSER 1 POUR SE  CONNECTER                      |"<<endl;
    cout << "\t| PRESSER 2 POUR  S'ENREGISTRER                     |"<<endl;
    cout << "\t| PRESSER 3 POUR  MOT DE PASSE OUBLIE               |"<<endl;
    cout << "\t| PRESSER 4 POUR  QUITTER                           |"<<endl;
    cout << "\n\t\t\t Please enter your choice : ";
    cin >>choice;
    cout << endl;

    switch(choice){
        case 1:
            user.login(db.getDatabase(), username, password);
            if (username == admin.getUsername() && password == admin.getPassword()){
            cout << "\n\t\t\t Bienvenue, Administrateur ! Redirection vers le menu admin...\n\n";
            admin.menuAdmin(db.getDatabase());
        } else {
            user.menu_utilisateur(db.getDatabase());
        }
            break;
        case 2:
            user.registerUser(db.getDatabase());
            break;
        case 3:
             user.reset_passwd(db.getDatabase(), username);
            break;
        case 4:
            cout <<"\t\t\t MERCI POUR LA VISITE! \n\n";
            break;
        default:
            cout <<"\t\t\t Choix invalide! REASSEYEZ, MERCI \n"<<endl;
            main();
    }


    return 0;
}
