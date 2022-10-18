#include <iostream>

using namespace std;

class Lodgment{
    private:
        int price;
        string lodgename;
        string description;
        string lodgetype;
    public:
        Lodgment();
        Lodgment(int price, string lodgename, string description, string lodgetype);
        int getPrice(){ return price;};
        string getName(){ return lodgename;};
        string getDescription(){ return description;};
        string getLodgetype(){ return lodgetype;};

        bool operator<(const Lodgment &other) const{
            if (price == other.price){
                return lodgename < other.lodgename;
            }
            else{
                return price < other.price;
            }
        }
};

Lodgment::Lodgment(){}

Lodgment::Lodgment(int price, string lodgename, string description, string lodgetype){
    this->price = price;
    this->lodgename = lodgename;
    this->description = description;
    this->lodgetype = lodgetype;
}

class Hotel: public Lodgment{
    private:
        string hotelchain;
        bool restaurant;
    public:
        Hotel();
        Hotel(int price, string lodgename, string description, string lodgetype, string hotelchain, bool restaurant);
        string getHotelChain(){ return hotelchain;};
        bool getRestaurant(){ return restaurant;};
};

Hotel::Hotel(){}

Hotel::Hotel(int price, string lodgename, string description, string lodgetype, string hotelchain, bool restaurant) : Lodgment(price,lodgename,description,lodgetype){
    this->hotelchain = hotelchain;
    this->restaurant = restaurant;
}

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