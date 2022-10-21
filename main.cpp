#include <bits/stdc++.h>
#include <ctime>
#include "Usuario.h"
#include "Lodgment.h"
#define ll long long
#define pb push_back

using namespace std;

void clearConsole(){
    system("pause");
    system("cls");
}

int randomizer(int minic, int maxic){
    return rand()%(maxic-minic+1) + minic;
}

set<Usuario> getListUsers(){
    set <Usuario> a;
    string text;
    ifstream archivo;
    archivo.open("Usuarios.txt",ios::in);
    if (!archivo.fail()){
        while(!archivo.eof()){
            string currname = "",currpwd = "",type = "";
            getline(archivo,text);
            if (text.size() > 0){
                int separators = 0;
                for (int i = 0; i<text.size(); i++){
                    if (text[i] == '|') separators++;
                    else if (separators == 0) currname += text[i];
                    else if (separators == 1) currpwd += text[i];
                    else type += text[i];
                }
                Usuario aux(currname,currpwd,type);
                a.insert(aux);
            }
        }
    }
    return a;
} 

void getClients(){
    set <Usuario> st = getListUsers();
    for (auto a: st){
        if (a.getUserType() == "Client") cout<<a.getUsername()<<" "<<a.getPassword()<<" "<<a.getUserType()<<"\n";
    }
    clearConsole();
}

set <string> getDestinations(){
    set <string> st;
    ifstream archivo;
    string text;
    archivo.open("Destinations.txt",ios::in);
    if (!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,text);
            st.insert(text);
        }
        archivo.close();
    }
    return st;
}

map < pair <string, string>,int > getTransportationTimes(){
    map < pair <string, string>, int > tempos;
    set <string> st = getDestinations();
    ifstream archivo;
    string text;
    for (auto destino : st){
        archivo.open(destino + "_Transportation.txt", ios::in);
        if (!archivo.fail()){
            while(!archivo.eof()){
                getline(archivo,text);
                if(text.size() > 0){
                    string destino2 = "", tempo = "";
                    int separators = 0;
                    for (int i = 0; i<text.size(); i++){
                        if (text[i] == '|') separators++;
                        else if (separators == 0) destino2 += text[i];
                        else if (separators == 2) tempo += text[i];
                    }
                    int aux = stoi(tempo);
                    //cout<<destino<<" "<<destino2<<"\n";
                    tempos[{destino,destino2}] = aux;
                }
                
            }
        }
        archivo.close();
    }
    return tempos;
}

void addDestination(){
    set <string> st = getDestinations();
    ofstream archivo;
    string text,newdestin;
    cout<<"Type the name of the new destination\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,newdestin);
    if (!st.count(newdestin)){
        archivo.open("Destinations.txt",ios::app);
        if (!archivo.fail()){
            archivo<<newdestin<<"\n";
        }
        archivo.close();
    }
    else cout<<"This destination already exists\n";
    clearConsole();
}

string trashNewname(){
    string trashname = "trash_file_";
    for (int i = 0; i<=10; i++){ 
        trashname += randomizer(97,122);
    }
    return trashname;
}

void ourDestinations(){
    set <string> st = getDestinations();
    for (auto a: st){
        if (a.size() > 0) cout<<a<<"\n";
    }
    clearConsole();
}

void deleteTransportation(string desta, string destb){
    //Deleting from the file "Desta" all the connecting transportation to destb:
    vector <string> v;
    ifstream ifs;
    ofstream ofs;
    string text;
    ifs.open(desta + "_Transportation.txt",ios::in);
    if (!ifs.fail()){ //Reading the file and not including all appearances of destb:
        while(!ifs.eof()){
            string destin = "";
            bool flag = true;
            getline(ifs,text);
            for (int i = 0; i<text.size(); i++){
                if (text[i] == '|'){
                    if (destin == destb){
                        flag = false;
                        break;
                    }
                }
                destin += text[i];
            }
            if (flag && destin.size() > 0){
                v.pb(destin);
            }
        }
        ifs.close();
    }
    ofs.open(desta + "_Transportation.txt",ios::out);
    if (!ofs.fail()){
        for (int i = 0; i<v.size(); i++) ofs<<v[i]<<"\n";
        ofs.close();
    }
}

void deleteDestination(){
    set <string> st = getDestinations();
    set <string> contrans;
    vector <string> v;
    ifstream archivo;
    string text,newdestin,filename;
    int aux;
    cout<<"Type the name of the destination to erase\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,newdestin);
    newdestin[0] = toupper(newdestin[0]);
    if (st.count(newdestin)){
        //Removing the desired destination from the destination list file:
        archivo.open("Destinations.txt",ios::in);
        while(!archivo.eof()){
            getline(archivo,text);
            if (text != newdestin) v.pb(text);
        }
        archivo.close();
        ofstream archivo2;
        archivo2.open("Destinations.txt",ios::out);
        if (!archivo2.fail()){
            for (int i = 0; i<v.size(); i++) archivo2<<v[i]<<"\n";
            archivo2.close();
        }   
        //Remove all transportation appearances from all the connecting destinations:
        archivo.open(newdestin + "_Transportation.txt",ios::in);
        if (!archivo.fail()){
            while(!archivo.eof()){
                string conn = "";
                getline(archivo,text);
                for (int i = 0; i<text.size(); i++){
                    if (text[i] == '|') break;
                    conn += text[i];
                }
                conn[0] = toupper(conn[0]);
                contrans.insert(conn);
            }
            archivo.close();
        }
        //Iterate over those values and erase every transportation one by one
        for (auto cns : contrans){
            cout<<cns<<"\n";
            deleteTransportation(cns,newdestin);
        }
        cout<<"Connecting destinations succesfully deleted\n";
        //return;

        //Erase all the files that are related with the deleting destination:
        filename = newdestin + "_Transportation.txt";
        aux = rename(filename.c_str(),trashNewname().c_str());
        filename = newdestin + "_Lodgment.txt";
        aux = rename(filename.c_str(),trashNewname().c_str());
        filename = newdestin + "_Spots.txt";
        aux = rename(filename.c_str(),trashNewname().c_str());
        cout<<"Destination succesfully deleted\n";
    }
    else cout<<"Destination not found\n";
    clearConsole();
}

void addTransportation(string desta, string destb, int cost, int tempo){ //From A to the B
    ofstream ofs;
    destb += "|";
    destb += to_string(cost);
    destb += "|";
    destb += to_string(tempo);
    ofs.open(desta + "_Transportation.txt",ios::app);
    if (!ofs.fail()){
        ofs<<destb<<"\n";
        ofs.close();
    }
}

void addTransportationMenu(){
    set <string> st = getDestinations();
    string desta,destb;
    bool idavuelta;
    int cost,tempo;
    char opc;
    cout<<"Enter the names of both destinations:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,desta);
    getline(cin,destb);
    cout<<"Enter the cost of the transportation\n";
    cin>>cost;
    cout<<"Enter the time of travel between the two cities in minutes\n";
    cin>>tempo;
    cout<<"Enter '1' if the transportation is round or any key if it just goes from point A --> B\n";
    cin>>opc;
    if (st.count(desta) && st.count(destb)){
        addTransportation(desta,destb,cost,tempo);
        if (opc == '1') addTransportation(destb,desta,cost,tempo);

        cout<<"New transportation between: ";
        if (opc == '1') cout<<desta<<" <----> "<<destb<<" ";
        else cout<<desta<<" ----> "<<destb<<" ";
        cout<<"has been added succesfully\n";
    }
    else cout<<"Any of the destinations does not exist\n";
    clearConsole();
}

void deleteTransportationMenu(){
    set <string> st = getDestinations();
    string desta,destb;
    cout<<"Enter the names the destinations where no connection between them is desired\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,desta);
    getline(cin,destb);
    if (st.count(desta) && st.count(destb)){
        deleteTransportation(desta,destb);
        deleteTransportation(destb,desta);
        cout<<"Transportation between "<<desta<<" and "<<destb<<" was succesfully deleted\n";
    }
    else cout<<"Any of the destinations does not exist\n";
    clearConsole();
}

set <string> getSpots(string destin){
    set <string> st;
    string text;
    ifstream ifs;
    ifs.open(destin + "_Spots.txt",ios::in);
    if (!ifs.fail()){
        while(!ifs.eof()){
            getline(ifs,text);
            st.insert(text);
        }
        ifs.close();
    }
    return st;
}

void addSpot(string destin, string spot){
    ofstream ofs;
    string text;
    ofs.open(destin + "_Spots.txt",ios::app);
    if (!ofs.fail()){
        ofs<<spot<<"\n";
        ofs.close();
    }
}

void deleteSpot(string destin, string spot){
    set <string> st = getSpots(destin);
    ofstream ofs;
    string text;
    ofs.open(destin + "_Spots.txt",ios::out);
    if (!ofs.fail()){
        for (auto spt : st){
            if (spt != spot) ofs<<spt<<"\n";
        }
        ofs.close();
    }
}

void deleteSpotMenu(){
    set <string> st = getDestinations();
    string destin,spot;
    cout<<"Enter the name of the destination and the name of the spot to be deleted\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,destin);
    getline(cin,spot);
    if (st.count(destin)){
        set <string> spots = getSpots(destin);
        if (spots.count(spot)){
            deleteSpot(destin,spot);
            cout<<"Spot deleted succesfully\n";
        }
        else cout<<"This spot does not exist\n";
    }
    else cout<<"The destination does not exist\n";
    clearConsole();
}

void addSpotMenu(){
    set <string> st = getDestinations();
    string destin,spot;
    cout<<"Enter the name of the destination and the name of the new spot to be added\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,destin);
    getline(cin,spot);
    if (st.count(destin)){
        set <string> spots = getSpots(destin);
        if (!spots.count(spot)){
            addSpot(destin,spot);
            cout<<"Spot added succesfully\n";
        }
        else cout<<"This spot is already added\n";
    }
    else cout<<"The destination does not exist\n";
    clearConsole();
}

void addHotel(string destin, string name, string desc, string hotelchain, bool restaurant, int price){
    ofstream ofs;
    ofs.open(destin + "_Lodgment.txt",ios::app);
    if (!ofs.fail()){
        ofs<<name<<"|"<<to_string(price)<<"|hotel|"<<hotelchain<<"|"<<(restaurant ? "yes" : "no")<<"|"<<desc<<"\n";
        ofs.close();
    }
}

void addAirbnb(string destin, string name, string desc, string owner, int rating, int price){
    ofstream ofs;
    ofs.open(destin + "_Lodgment.txt",ios::app);
    if (!ofs.fail()){
        ofs<<name<<"|"<<to_string(price)<<"|airbnb|"<<owner<<"|"<<to_string(rating)<<"|"<<desc<<"\n";
        ofs.close();
    }
}

void addLodgmentMenu(){
    string destin;
    set <string> st = getDestinations();
    cout<<"Enter the name of the destination where the new lodgment will be added\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,destin);
    if (st.count(destin)){
        string lotype,name,desc;
        int price;
        cout<<"Type 'airbnb' or 'hotel' for the new type of lodgment to add\n";
        cin>>lotype;
        for (int i = 0; i<lotype.size(); i++) lotype[i] = tolower(lotype[i]);

        if (lotype == "airbnb"){  
            string owner;
            int rating;  
            cout<<"Enter the name of the airbnb, description, owner, rating and price\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,name);
            getline(cin,desc);
            getline(cin,owner);
            cin>>rating;
            cin>>price;
            addAirbnb(destin,name,desc,owner,rating,price);
        }
        else if (lotype == "hotel"){
            string hotelchain;
            string restaurant;
            cout<<"Enter the name of the hotel, description, hotelchain, 'yes' or 'no' if it has restaurant, and price\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,name);
            getline(cin,desc);
            getline(cin,hotelchain);
            cin>>restaurant;
            cin>>price;
            for (int i = 0; i<restaurant.size(); i++) restaurant[i] = tolower(restaurant[i]);

            addHotel(destin,name,desc,hotelchain,(restaurant == "yes" ? true : false),price);
        }
        else cout<<"Invalid lodgment type, try again\n";
    }
    clearConsole();
}

set <string> getLodgment(string destin){
    ifstream ifs;
    string text;
    set <string> st;
    ifs.open(destin + "_Lodgment.txt",ios::in);
    if (!ifs.fail()){
        while(!ifs.eof()){
            string lod = "";
            getline(ifs,text);
            for (int i = 0; i<text.size(); i++){
                if (text[i] == '|') break;
                lod += text[i];
            }
            st.insert(lod);
        }
        ifs.close();
    }
    return st;
}

void deleteLodgment(string destin, string name){
    vector <string> v;
    ifstream ifs;
    ofstream ofs;
    string text;
    ifs.open(destin + "_Lodgment.txt",ios::in);
    if (!ifs.fail()){
        while(!ifs.eof()){
            string lod = "";
            bool flag = false;
            getline(ifs,text);
            for (int i = 0; i<text.size(); i++){
                if (text[i] == '|'){
                    if (lod == name){
                        flag = true;
                        break;
                    }
                }
                lod += text[i];
            }
            if (!flag && text.size() > 0) v.pb(lod);
        }
        ifs.close();
    }
    ofs.open(destin + "_Lodgment.txt",ios::out);
    if (!ofs.fail()){
        for (int i = 0; i<v.size(); i++){
            ofs<<v[i]<<"\n";
        }
        ofs.close();
    }
}

void deleteLodgmentMenu(){
    set <string> st = getDestinations();
    string destin,name;
    cout<<"Type the name of the destination and the name of the lodgment to be deleted\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,destin);
    getline(cin,name);
    if (st.count(destin)){
        set <string> lodges = getLodgment(destin);
        if (lodges.count(name)){
            deleteLodgment(destin,name);
            cout<<"Lodgment deleted succesfully\n";
        }
        else cout<<"Lodgment not found\n";
    }
    else cout<<"The destination does not exist\n";
    clearConsole();
}

void specificDestination(string destino){
    ifstream archivo;
    string text;
    archivo.open(destino + "_Transportation.txt",ios::in);
    cout<<"-------------------\n";
    cout<<"Transportations:\n";
    if (!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,text);
            if (text.size() > 0) cout<<text<<"\n";
        }
    }
    cout<<"\n";
    archivo.close();
    archivo.open(destino + "_Lodgment.txt",ios::in);
    cout<<"Lodgement:\n";
    if (!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,text);
            if (text.size() > 0) cout<<text<<"\n";
        }
    }
    cout<<"\n";
    archivo.close();
    archivo.open(destino + "_Spots.txt",ios::in);
    cout<<"Turistic Spots:\n";
    if (!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,text);
            if (text.size() > 0) cout<<text<<"\n";
        }
    }
    cout<<"\n-------------------\n";
    clearConsole();
}

set <string> getTravelDayInfo(int day){
    set <string> st;
    string text;
    ifstream ifs;
    ifs.open("Trips_" + to_string(day) + ".txt",ios::in);
    if (!ifs.fail()){
        while(!ifs.eof()){
            getline(ifs,text);
            if (text.size() > 0) st.insert(text);
        }
        ifs.close();
    }
    return st;
}



void * simulation(void * date){
    int * day = (int*)date;

}

void adminMenu(){
    cout<<"------------------------\n";
    cout<<"Press 1 to add a destination\n";
    cout<<"Press 2 to delete a destination\n";
    cout<<"Press 3 to add a transportation between 2 destinations\n";
    cout<<"Press 4 to delete a transportation between 2 destinations\n";
    cout<<"Press 5 to add a turistic spot in a destination\n";
    cout<<"Press 6 to delete a turistic spot in a destination\n";
    cout<<"Press 7 to add a lodgement in a destination\n";
    cout<<"Press 8 to delete a lodgement in a destination\n";
    cout<<"Press 9 to see the list of all the destinations\n";
    cout<<"Press 10 to see the features of a specific destination\n";
    cout<<"Press 11 to see the list of all the clients\n";
    cout<<"Press 12 to run simulation of the day\n";
    cout<<"Press 13 to log out\n";
}

void adminMode(string username){
    cout<<"This is admin mode\n";
    while(true){
        adminMenu();
        string opc;
        cin>>opc;
        if (opc == "1") clearConsole(), addDestination();
        else if (opc == "2") clearConsole(), deleteDestination();
        else if (opc == "3") clearConsole(), addTransportationMenu();
        else if (opc == "4") clearConsole(), deleteTransportationMenu();
        else if (opc == "5") clearConsole(), addSpotMenu();
        else if (opc == "6") clearConsole(), deleteSpotMenu();
        else if (opc == "7") clearConsole(), addLodgmentMenu();
        else if (opc == "8") clearConsole(), deleteLodgmentMenu();
        else if (opc == "9") clearConsole(), ourDestinations();
        else if (opc == "10"){
            string destino;
            cout<<"Enter the name of the Destination\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,destino);
            destino[0] = toupper(destino[0]);
            clearConsole();
            specificDestination(destino);
        }
        else if (opc == "11") clearConsole(), getClients();
        else if (opc == "12"){
            clearConsole();
            break;
        }
        else cout<<"Invalid option, try again\n", clearConsole();
    }
}

void myPurchases(string username){
    ifstream archivo;
    string text;
    archivo.open(username + "_Purchases.txt",ios::in);
    cout<<"My Purchases: \n";
    if (!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,text);
            cout<<text<<"\n";
        }
    }
    clearConsole();
}
vector < pair <vector<string>, int> >posroutes;
vector < pair <vector<string>, int> >postimes;
//DFS  
void dfsRoutes(map <string, vector <string> > adj, map < pair <string, string>, int> costs, map < pair <string,string>, int > tempos, vector <string> ruta,string currcity, string b, int minic, int maxic, set <string> st, int totcost, int tottime){
    st.insert(currcity);
    ruta.pb(currcity);
    if (currcity == b){
        if (minic <= totcost && totcost <= maxic){
            cout<<posroutes.size()+1<<". $"<<totcost<<", total time: "<<tottime<<", route:\n";
            for (auto r: ruta){
                cout<<r;
                if (r != b) cout<<"-->";
            }
            cout<<"\n";
            posroutes.pb({ruta,totcost});
            postimes.pb({ruta,tottime});
        }
    }
    else{
        for (auto r: adj[currcity]){
            if (!st.count(r)){
                dfsRoutes(adj,costs,tempos,ruta,r,b,minic,maxic,st,totcost+costs[{r,currcity}],tottime+tempos[{r,currcity}]);
            }
        }
    }
}

map <string, vector <string> > getAdjacencyList(){
    map <string, vector <string> > adj;
    set <string> st = getDestinations();
    for (auto destino : st){
        ifstream archivo;
        string text;
        archivo.open(destino + "_Transportation.txt", ios::in);
        //cout<<destino<<" ";
        if (!archivo.fail()){
            while(!archivo.eof()){
                getline(archivo,text);
                string destino2 = "";
                for (int i = 0; i<text.size() && text[i] != '|'; i++) destino2 += text[i];
                adj[destino].pb(destino2);
            }
        }
        archivo.close();
    }
    //cout<<"Finished\n";
    return adj;
}

map < pair <string, string>,int > getTransportationCosts(){
    map < pair <string, string>, int > costs;
    set <string> st = getDestinations();
    ifstream archivo;
    string text;
    for (auto destino : st){
        archivo.open(destino + "_Transportation.txt", ios::in);
        if (!archivo.fail()){
            while(!archivo.eof()){
                getline(archivo,text);
                if(text.size() > 0){
                    string destino2 = "", costic = "";
                    int separators = 0;
                    for (int i = 0; i<text.size(); i++){
                        if (text[i] == '|') separators++;
                        else if (separators == 0) destino2 += text[i];
                        else if (separators == 1) costic += text[i];
                    }
                    int aux = stoi(costic);
                    //cout<<destino<<" "<<destino2<<"\n";
                    costs[{destino,destino2}] = aux;
                }
                
            }
        }
        archivo.close();
    }
    return costs;
}

set <Hotel> getHotels(string destination){
    set <Hotel> st;
    ifstream archivo;
    string text,lodgename,price,lodgetype,desc,extra,extra2;
    archivo.open(destination + "_Lodgment.txt",ios::in);
    if (!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,text);
            int tam = text.size();
            if (tam > 0){
                int sepp = 0;
                lodgename = price = lodgetype = desc = extra = extra2 = "";
                for (int i = 0; i<tam; i++){
                    if (text[i] == '|') sepp++;
                    else{
                        if (sepp == 0) lodgename += text[i];
                        if (sepp == 1) price += text[i];
                        if (sepp == 2) lodgetype += text[i];
                        if (sepp == 3) extra += text[i];
                        if (sepp == 4) extra2 += text[i];
                        if (sepp == 5) desc += text[i];
                    }
                }
                cout<<lodgename<<"\n";
                int currprice = stoi(price);
                for (int i = 0; i<lodgetype.size(); i++) lodgetype[i] = tolower(lodgetype[i]);
                if (lodgetype == "hotel"){
                    for (int i = 0; i<extra2.size(); i++) extra2[i] = tolower(extra2[i]);
                    Hotel aux(currprice,lodgename,desc,lodgetype,extra,(extra2 == "yes" ? true : false));
                    st.insert(aux);
                }
            }
        }
    }
    return st;
}

set <AirBnb> getAirBnbs(string destination){
    set <AirBnb> st;
    ifstream archivo;
    string text,lodgename,price,lodgetype,desc,extra,extra2;
    archivo.open(destination + "_Lodgment.txt",ios::in);
    if (!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,text);
            int tam = text.size();
            if (tam > 0){
                int sepp = 0;
                lodgename = price = lodgetype = desc = extra = extra2 = "";
                for (int i = 0; i<tam; i++){
                    if (text[i] == '|') sepp++;
                    else{
                        if (sepp == 0) lodgename += text[i];
                        if (sepp == 1) price += text[i];
                        if (sepp == 2) lodgetype += text[i];
                        if (sepp == 3) extra += text[i];
                        if (sepp == 4) extra2 += text[i];
                        if (sepp == 5) desc += text[i];
                    }
                }   
                int currprice = stoi(price);
                for (int i = 0; i<lodgetype.size(); i++) lodgetype[i] = tolower(lodgetype[i]);
                if (lodgetype == "airbnb"){
                    int rated = stoi(extra2);
                    AirBnb aux(currprice,lodgename,desc,lodgetype,extra,rated);
                    st.insert(aux);
                }
            }
        }
    }
    return st;
}

void book(string username){
    time_t tim = time(0);
    tm *gottime = localtime(&tim);
    int today = gottime->tm_yday;
    Lodgment * stay[1000];
    map <string, vector <string> > adj = getAdjacencyList();
    map < pair <string, string>, int > costs = getTransportationCosts();
    map < pair <string,string>, int> tempos = getTransportationTimes();
    set <string> destinos = getDestinations();
    string a,b;
    int tminic,tmaxic,hminic,hmaxic,days,opc,inx = 0;
    cout<<"Enter the place of departure and your destination\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,a);
    getline(cin,b);
    cout<<"Enter the range of your transportation budget and lodgment budget (minimum and maximum for each)\n";
    cin>>tminic>>tmaxic;
    cin>>hminic>>hmaxic;
    cout<<"Enter the amount of days you want to spend in that destination\n";
    cin>>days;
    set <Hotel> hotels = getHotels(b);
    set <AirBnb> abnb = getAirBnbs(b);
    if (destinos.count(a) && destinos.count(b)){
        set <string> aux;
        vector <string> aux2;
        cout<<"Suitable results ways for given budget : \n";
        posroutes.clear();
        posroutes.resize(0);
        postimes.clear();
        postimes.resize(0);
        dfsRoutes(adj,costs,tempos,aux2,a,b,tminic,tmaxic,aux,0,0);
        cout<<"Suitable lodgment for the given budget (price per night): \n";
        for (auto ht : hotels){
            if (hmaxic < ht.getPrice()) break;
            else if (hminic <= ht.getPrice()){
                inx++;
                cout<<inx<<". "<<ht.getName()<<" $"<<ht.getPrice()<<" "<<ht.getLodgetype()<<" "<<ht.getHotelChain()<<" "<<ht.getRestaurant()<<" "<<ht.getDescription()<<"\n";
                //(currprice,lodgename,desc,lodgetype,extra,rated)
                stay[inx] = new Hotel(ht.getPrice(),ht.getName(),ht.getDescription(),ht.getLodgetype(),ht.getHotelChain(),ht.getRestaurant());
            }
        }
        for (auto abbs : abnb){
            if (hmaxic < abbs.getPrice()) break;
            else if (hminic <= abbs.getPrice()){
                inx++;
                cout<<inx<<". "<<abbs.getName()<<" $"<<abbs.getPrice()<<" "<<abbs.getLodgetype()<<" "<<abbs.getOwner()<<" "<<abbs.getRating()<<" "<<abbs.getDescription()<<"\n";
                stay[inx] = new AirBnb(abbs.getPrice(),abbs.getName(),abbs.getDescription(),abbs.getLodgetype(),abbs.getOwner(),abbs.getRating());
            }
        }
        cout<<"Click 1 if you would like to book: \n";
        cin>>opc;
        if (opc == 1){
            int roadopc,lodgeopc;
            cout<<"Enter the number of the way option, you would like to choose: \n";
            cin>>roadopc;
            roadopc--;
            cout<<"Enter the number of the hotel you would like to book\n";
            cin>>lodgeopc;
            if (roadopc < posroutes.size() && 0 < lodgeopc && lodgeopc <= inx){
                cout<<"You have succesfully booked!\n";
                int tamic = posroutes[roadopc].first.size();
                int trans = posroutes[roadopc].second;
                cout<<"$"<<trans<<" transport: ";
                for (int j = 0; j<tamic; j++){
                    cout<<posroutes[roadopc].first[j];
                    if (j+1 < tamic) cout<<"-->";
                }
                int loprice = stay[lodgeopc]->getPrice() * days;
                cout<<"\n$"<<stay[lodgeopc]->getPrice()<<" per night: "<<stay[lodgeopc]->getName()<<", "<<stay[lodgeopc]->getLodgetype()<<", "<<stay[lodgeopc]->getDescription()<<", total lodgement cost: $"<<loprice<<"\n";
                cout<<"Total: $"<<trans + loprice<<"\n";
                //write in the personal purchase file the purchases and bookings made:
                ofstream archivo;
                archivo.open(username + "_Purchases.txt",ios::app);
                if (!archivo.fail()){
                    archivo<<"Transportation|"<<to_string(trans)<<"|";
                    for (int j = 0; j<tamic; j++){
                        archivo<<posroutes[roadopc].first[j];
                        if (j+1 < tamic) archivo<<"-->";
                    }
                    archivo<<"|\n";
                    archivo<<"Lodgment|"<<to_string(loprice)<<"|"<<stay[lodgeopc]->getName()<<"|"<<stay[lodgeopc]->getLodgetype()<<"|\n";
                    archivo.close();
                }
                archivo.open("Trips_" + to_string(today) + ".txt",ios::app);
                if (!archivo.fail()){
                    archivo<<username<<"|";
                    for (int j = 0; j<tamic; j++){
                        archivo<<posroutes[roadopc].first[j];
                        if (j+1 < tamic) archivo<<">";
                    }
                    archivo<<"|\n";
                    archivo.close();
                }
            }
            else cout<<"Some of the options was not found, try again\n";
        }
    }
    else cout<<"The departure and/or destination does not exists\n";
    clearConsole();
}

void clientMenu(){
    cout<<"------------------------\n";
    cout<<"Press 1 to book a trip\n";
    cout<<"Press 2 to take a look to our destinations\n";
    cout<<"Press 3 to take a look at a specific destination and its features\n";
    cout<<"Press 4 to see all of your bookings and purchases\n";
    cout<<"Press 5 to log out\n";
    cout<<"------------------------\n";
}

void clientMode(string username){
    while(true){
        clientMenu();
        string opc; 
        cin>>opc;
        if (opc == "1") clearConsole(), book(username);
        else if (opc == "2") clearConsole(), ourDestinations();
        else if (opc == "3"){
            clearConsole();
            string destino;
            cout<<"Enter the name of the Destination\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,destino);
            destino[0] = toupper(destino[0]);
            specificDestination(destino);
        }
        else if (opc == "4") clearConsole(), myPurchases(username);
        else if (opc == "5"){
            clearConsole();
            break;
        }
        else cout<<"Choose a valid option\n", clearConsole();
    }
}

void loginMenu(){
    cout<<"-----------------------------------------\n";
    cout<<"Welcome to UP Travel Agency\n";
    cout<<"Don't have an account? Click 1 to sign up\n";
    cout<<"Have an account? Click 2 to login\n";
    cout<<"Click 3 to quit\n";
    cout<<"-----------------------------------------\n";
}

set <string> getOnlyUsernames(){
    set <string> st;
    string text;
    ifstream archivo;
    archivo.open("Usuarios.txt",ios::in);
    if (!archivo.fail()){
        while(!archivo.eof()){
            string currname = "";
            getline(archivo,text);
            for (int i = 0; i<text.size(); i++){
                if (text[i] == '|') break;
                currname += text[i];
            }
            st.insert(currname);
        }
        archivo.close();
    }
    return st;
}

set <string> getUserAndPass(){
    set <string> st;
    string text;
    ifstream archivo;
    archivo.open("Usuarios.txt",ios::in);
    if (!archivo.fail()){
        while(!archivo.eof()){
            text = "";
            getline(archivo,text);
            st.insert(text);
        }
        archivo.close();
    }
    return st;
}

void createAccount(){
    set <string> st = getOnlyUsernames();
    string username,password;
    cout<<"Enter your username and password\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,username);
    getline(cin,password);
    if (st.count(username)){
        cout<<"Username already taken\n";
    }
    else{
        ofstream archivo;
        archivo.open("Usuarios.txt",ios::app);
        if (!archivo.fail()){
            archivo<<username<<"|"<<password<<"|"<<"Client|\n";
            cout<<"Account created successfully\n";
        }
        archivo.close();
    }
    clearConsole();
}


void loginAccount(){
    bool logged = false;
    set <string> st = getUserAndPass();
    string username,password,type,aux,aux2;
    cout<<"Enter your username and password\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,username);
    getline(cin,password);
    aux = username + "|" + password + "|Client|";
    aux2 = username + "|" + password + "|Admin|";
    if (st.count(aux2)){
        cout<<"Welcome "<<username<<" to admin Mode\n";
        clearConsole();
        adminMode(username);
    }
    else if (st.count(aux)){
        st.count(aux2);
        cout<<"Welcome "<<username<<" to UP Travel Agency\n";
        clearConsole();
        clientMode(username);
    }
    if (!logged) cout<<"Cannot log in\n";
    return;
} 


int main(){
    while(true){
        map <Usuario,int> mp;
        loginMenu();
        string opc;
        cin>>opc;
        clearConsole();
        if (opc == "1") createAccount();
        else if (opc == "2") loginAccount();
        else if (opc == "3") break;
        else cout<<"Invalid option, try again\n";
    }
    return 0;
}