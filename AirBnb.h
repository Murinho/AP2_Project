#include <iostream>

using namespace std;

class AirBnb: public Lodgment{
    private:
        string owner;
        int rating;
    public:
        AirBnb();
        AirBnb(int price, string lodgename, string description, string lodgetype, string owner, int rating);
        string getOwner(){ return owner;};
        int getRating(){ return rating;};
};

AirBnb::AirBnb(){}

AirBnb::AirBnb(int price, string lodgename, string description, string lodgetype, string owner, int rating) : Lodgment(price,lodgename,description,lodgetype){
    this->owner = owner;
    this->rating = rating;
}