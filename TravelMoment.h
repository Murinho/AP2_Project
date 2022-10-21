#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

Class TravelMoment{
    private:
        string username;
        string place;
        int currtime;
    public:
        TravelMoment(){}
        TravelMoment(string username, string place, int currtime);
        string getUsername(){ return username;};
        string getPlace(){ return place;};
        int getTime(){ return currtime;};
}

TravelMoment::TravelMoment(string username, string place, int currtime){
    this->username = username;
    this->place = place;
    this->currtime = currtime;
}