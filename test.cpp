#include <bits/stdc++.h>
#include <ctime>
#define ll long long
#define pb push_back

using namespace std;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
vector <string> v;

void * simulation(void * info){
    for (int i = 0; i<v.size(); i++) cout<<v[i]<<"\n";
    pthread_exit(NULL);
}

int main(){
    pthread_t hilos[100];
    pthread_t thrdy;
    time_t tim = time(0);
    tm *gottime = localtime(&tim);
    int day = gottime->tm_yday;
    int tam = -1;
    ifstream ifs;
    string text;
    cout<<day<<"\n";
    ifs.open("Trips_" + to_string(day) + ".txt",ios::in);
    if (!ifs.fail()){
        while(!ifs.eof()){
            getline(ifs,text);
            //string * newtxt = &text;
            cout<<"Inside: "<<text<<"\n";
            if (text.size() > 0){
                tam++;
                v.pb(text);
                //int res = pthread_create( &hilos[tam], NULL, &simulation, (void*)newtxt);
                //pthread_join( hilos[tam], NULL); 
            } 
        }
        int res = pthread_create( &thrdy, NULL, &simulation, (void*) NULL);
        pthread_join( thrdy, NULL); 
        if (res) cout<<"Error ocurred in the thread\n";
    }
}