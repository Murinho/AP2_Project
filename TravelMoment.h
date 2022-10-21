#include <iostream>

using namespace std;

class TravelMoment{
    private:
        string username;
        string place;
        int currtime;
    public:
        TravelMoment();
        TravelMoment(string username, string place, int currtime);
        string getUsername(){ return username;};
        string getPlace(){ return place;};
        int getCurrtime(){ return currtime;};
        void setUsername(string username);
        void setPlace(string place);
        void setCurrtime(int currtime);

        bool operator<(const TravelMoment &other) const{
            if (currtime == other.currtime){
                return place < other.place;
            }
            else{
                return currtime < other.currtime;
            }
        }
};

TravelMoment::TravelMoment(){}

TravelMoment::TravelMoment(string username, string place, int currtime){
    this->username = username;
    this->place = place;
    this->currtime = currtime;
}

void TravelMoment::setUsername(string username){
    this->username = username;
}

void TravelMoment::setPlace(string place){
    this->place = place;
}

void TravelMoment::setCurrtime(int currtime){
    this->currtime = currtime;
}