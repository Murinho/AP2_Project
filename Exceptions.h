#include <iostream>

using namespace std;

class Exceptions: public exception{
    public:
        virtual const char* what() const throw(){
            return "Something bad happened";
        }
};