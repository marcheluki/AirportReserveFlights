#ifndef flight_h
#define flight_h

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "passenger.h"
using namespace std;

const int SIZE = 10;
const int NUM_FLIGHTS=5;

class Flight{
private:
    string date;
    string hour;
    float price;
    string airplaneModel;
    string fromTo;
    float distance;
    string crew;
    float fuel;
    string duracion;
    int numFlight;
    int num;
    vector<Passenger> seats;
public:
    Passenger passenger;
    Flight();//pModel /seats        /date /price /hour /fromTo /diste /fuel /crew
    Flight(const Flight &f);
    Flight(int numFlight, string date, string fromTo, float price, float distance, string airplaneModel, string hour, string crew, float fuel, string duracion);
    ~Flight();
    void setDate(string d);
    void setNumFlight(int nf);
    void setDuracion(string dur);
    void setFromTo(string ft);
    void setPrice(float pr);
    void setDistance(float di);
    void setAirplaneModel(string am);
    void setHour(string h);
    void setCrew(string crw);
    void setFuel(float);
    void calculateFuel();
    void scheduleFlight(Flight &f);
    void initSeats();
    bool reserveSeat(int);
    int getNumPassengers();
    void printFlight();
    // getters
    string getDate();
    string getDuracion();
    int getNumFlight() const;
    string getFromTo() const;
    float getPrice();
    float getDistance() const;
    string getAirplaneModel() const;
    string getHour() const;
    string getCrew()const;
    float getFuel() const;
    string generateReservation(Passenger, int);
    Flight*flights[NUM_FLIGHTS];
};

Flight::Flight(){
    crew= " undefined ";
    fuel= 0;
    numFlight=0;
    fromTo = "Sin especificar";
    price = 0;
    distance = 0;
    airplaneModel = "Sin especificar";
    hour= "";
    date="";
    initSeats();
}
Flight::Flight(const Flight &f){
    date = f.date;
    setNumFlight(f.numFlight);
    duracion=f.duracion;
    fromTo = f.fromTo;
    price=f.price;
    distance= f.distance;
    airplaneModel = f.airplaneModel;
    hour = f.hour;
    fuel=f.fuel;
    crew = f.crew;
    initSeats();
}
Flight::Flight(int _numFlight, string _date, string _fromTo, float _price, float _distance, string _airplaneModel, string _hour, string _crew, float _fuel, string _duracion){
    crew= _crew;
    fuel= _fuel;
    numFlight= _numFlight;
    fromTo = _fromTo;
    price = _price;
    distance = _distance;
    airplaneModel = _airplaneModel;
    hour= _hour;
    date= _date;
    duracion = _duracion;
    initSeats();
}
// destructor
Flight::~Flight(){}

// getters
string Flight::getCrew()const{
    return crew;
}
float Flight::getFuel()const{
    return fuel;
}
string Flight::getDate(){
    return date;
}
int Flight::getNumFlight()const{
    return numFlight;
}
string Flight::getFromTo()const{
    return fromTo;
}
float Flight::getPrice(){
    return price;
}
float Flight::getDistance()const{
    return distance;
}
string Flight::getAirplaneModel()const{
    return airplaneModel;
}
string Flight::getHour()const{
    return hour;
}
string Flight::getDuracion(){
    return duracion;
}

void Flight::initSeats(){
    for (int i=0;i<SIZE;i++){
        seats.push_back(Passenger("", ""));
    }
}

string Flight::generateReservation(Passenger p, int price) {
    stringstream output;
    output<<"-----------------------"<<endl;
    output<<"*** VUELO ***"<<endl;
    output<< "Flight number: " <<getNumFlight()<<endl;
    output<<"Date: "<<getDate()<<endl;
    output<<"Destination: "<<getFromTo() <<endl;
    output<<"Price: $"<<getPrice()<<endl;
    output<<"Distance: " << getDistance() << "km" << endl;
    output<<"Airplane Model: "<<getAirplaneModel()<<endl;
    output<<"Hour: "<<getHour()<<endl;
    output<<"Crew: "<<getCrew()<<endl;
    output<<"Fuel: "<<getFuel()<<endl;
    output<<"Duracion: "<<getDuracion()<<endl;
    output<<"Passenger Name: " << p.getName()<<endl;
    output<<"TOTAL AMOUNT: $" << price << endl;
    output<<"-----------------------"<<endl;
    return output.str();
}

bool Flight::reserveSeat(int seat) {
    if (seat <= 0 || seat > SIZE) {
        cout << "Invalid seat" << endl;
        return false;
    }
    if (seats.at(seat-1).getName() != "") {
        cout << "The seat is taken" << endl;
        return false;
    }
    string name, phone;
    cout << "Passenger Name: ";
    cin >> name;
    cout << "Passenger Phone: ";
    cin >> phone;
    seats.at(seat-1) = Passenger(name, phone);
    return true;
}

// bool cancelSeat(Passenger p)
// recorrer tu vector de seats hasta que encuentres el pasajero que tenga el nombre y telefono igaul a p
//ya que lo encuentres, en esa posicion del vecotr cambias el pasajero a que sea un pasajero con nombre y telefono vacios

int Flight::getNumPassengers() {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        if (seats.at(i).getName() != "") {
            count++;
        }
    }
    return count;
}

// setters
void Flight::setCrew(string _crew){
    crew = _crew;
}
void Flight::setFuel(float _fuel){
    fuel = _fuel;
}
void Flight::setDate(string _date){
    date = _date;
}
void Flight::setNumFlight(int _numFlight){
    if (_numFlight>0){
        numFlight=_numFlight;
    }else{
        numFlight = 1;
    }
}
void Flight::setFromTo(string _fromTo){
    fromTo = _fromTo;
}
void Flight::setPrice(float _price){ 
    if (_price>=0){
        price = _price;
        
    }else{
        price=0;
    }
}
void Flight::setDistance(float _distance){
    if (_distance>=0){
        distance=_distance;
    }else{
        distance=0;
    }
}
void Flight::setAirplaneModel(string _airplaneModel){
    airplaneModel = _airplaneModel;
}
void Flight::setHour(string _hour){
    hour = _hour;
}
void Flight::setDuracion(string _duracion){
    duracion=_duracion;
}
void Flight::calculateFuel(){
    fuel=(distance/100)*1200;
    cout<<"El combustible requerido para viajar a "<<fromTo<<" es de: "<<fuel<< " litros"<<endl;
}
void Flight::scheduleFlight(Flight &f){
    if (num==NUM_FLIGHTS){
        cout<<"Vuelos de: "<<airplaneModel<<" saturados, imposible programar"<<endl;
    }else{
        string am,ft,crw,h;
        float di,pr;
        flights[num]=&f;
        cout<<"Modelo del avion: "<<endl;
        cin>>am;
        flights[num]->setAirplaneModel(am);
        cout<<"Identifica la trayectoria"<<endl;
        cin>>ft;
        flights[num]->setFromTo(ft);
        cout<<"Identifica la distancia del vuelo"<<endl;
        cin>>di;
        flights[num]->setDistance(di);
        cout<<"Identifica la clave de tripulacion"<<endl;
        cin>>crw;
        flights[num]->setCrew(crw);
        cout<<"Identifica la hora del vuelo"<<endl;
        cin>>h;
        flights[num]->setHour(h);
        cout<<"Precio del boleto: "<<endl;
        cin>>pr;
        flights[num]->setPrice(pr);
        num++;
    }
}

void Flight::printFlight(){
    stringstream output;
    cout<<"-----------------------"<<endl;
    cout<<"*** VUELO ***"<<endl;
    cout<< "Flight number: " <<getNumFlight()<<endl;
    cout<<"Date: "<<getDate()<<endl;
    cout<<"Destination: "<<getFromTo() <<endl;
    cout<<"Price: $"<<getPrice()<<endl;
    cout<<"Distance: " << getDistance() << "km" << endl;
    cout<<"Airplane Model: "<<getAirplaneModel()<<endl;
    cout<<"Hour: "<<getHour()<<endl;
    cout<<"Crew: "<<getCrew()<<endl;
    cout<<"Fuel: "<<getFuel()<<endl;
    cout<<"Duracion: "<<getDuracion()<<endl;
    cout<<"Cantidad de pasajeros: "<<getNumPassengers()<<endl;
    for (auto passenger : seats) {
        if (passenger.getName() != "") {
            passenger.printPassenger();
        }
    }
    cout<<"-----------------------"<<endl;
}
#endif