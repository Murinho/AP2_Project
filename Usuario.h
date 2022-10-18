#include <iostream>

using namespace std;

class Usuario{
    public:
        string username;
        string password;
        string usertype;
        Usuario();
        Usuario(string username, string password, string usertype);
        //void setUser(string username, string password, string usertype);

        string getUsername(){ return username; }
        string getPassword(){ return password; }
        string getUserType(){ return usertype; }

        bool operator<(const Usuario &other) const{
            if (username == other.username){
                return usertype < other.usertype;
            }
            else{
                return username < other.username;
            }
        }
};

Usuario::Usuario(){}

Usuario::Usuario(string username, string password, string usertype){
    this->username = username;
    this->password = password;
    this->usertype = usertype;
}

