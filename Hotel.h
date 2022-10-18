#include <iostream>

using namespace std;

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