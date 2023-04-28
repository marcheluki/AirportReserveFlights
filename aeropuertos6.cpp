//MARCELA BEATRIZ DE LA ROSA BARRIOS A01637239
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include "flight.h"
#include <cstdlib>
using namespace std;

bool registraUser(vector<Passenger> &vector){
    string name, password, phone;
    float kms; 
    cout<<"Nombre de usuario: ";
    cin>>name;
    cout<<"Contrasena: ";
    cin>>password;
    cout<<"Telefono: ";
    cin>>phone;
    kms=0;
    for (int i=0; i<vector.size();i++){
        if (vector[i].getName()==name && vector[i].getPhone()==phone){
            cout<<"El usuario ya existe"<<endl;
            return false;
        }
    }
    Passenger nuevoPassenger(name, password, phone, kms);
    vector.push_back(nuevoPassenger);
    ofstream archivo;
    archivo.open("Usuarios.txt", ios::app);
    if (archivo.fail()){
        cout << "Error al abrir archivo"<<endl;
        return false;
    } else {
        archivo << name << " " << password << " " << phone << " " << kms <<endl;
        archivo.close();
        return true;
    }
}

void addReservationToFile(Flight vuelo, Passenger p, int price) {
    ofstream archivo;
    archivo.open("reservacion.txt", ios::app);
    if (archivo.fail()){
        cout << "Error al abrir archivo"<<endl;
    } else {
        archivo << vuelo.generateReservation(p, price) <<endl;
        archivo.close();
    }
}
void cancelReservationToFile(Flight vuelo, Passenger p, int price) {
    string line;
    char* temp=(char*)malloc(sizeof(20));
    sprintf(temp, "Flight number: %d",vuelo.getNumFlight());
    fstream archivo;
    archivo.open("reservacion.txt");
    if (archivo.fail()){
        cout << "Error al abrir archivo"<<endl;
    } else {
        while (getline(archivo, line)){
            if (line==temp){
                line=" ***CANCELADO*** ";
                archivo<<line<<endl;
            }
        }
    }
}

void fillVecUsers(vector<Passenger> &vector){
    string name, password, phone;
    float kms;
    ifstream archivo;
    archivo.open("Usuarios.txt");
    if (archivo.fail()){
        cout << "Error al abrir archivo"<<endl;
    } else {
        while (archivo >> name >> password >> phone >> kms){
            Passenger userTemp(name, password, phone, kms);
            vector.push_back(userTemp);
        }
    archivo.close();
    }
}

void login(vector<Passenger> vector, Passenger &passenger) {
    string name, password;
    bool entra = false;
    cout<<"Usuario: ";
    cin>>name;
    cout<<"Contrasena: ";
    cin>>password;
    while (!entra){
        for (int i=0;i<vector.size();i++){
            if (vector[i].getName() == name && vector[i].getPassword()==password){
                passenger=vector[i];
                cout<<"Bienvenido "<<name<<endl;
                return;
            }
        }
        cout<< "Usuario y/o contrasena incorrectos o usuario inexistente"<<endl;
        cout<<"Ingrese su usuario: ";
        cin>>name;
        cout<<"Ingrese su contrasena: ";
        cin>>password;
    }
}

void printVecPasajeros(vector<Passenger> vector) {
    for (int i = 0; i < vector.size(); i++) {
        vector[i].printPassenger();
    }
}

void fillVecVuelos(vector<Flight> &vecVuelo){
    int numFlight, passengers;
    string date, hour, airplaneModel, fromTo, crew, duracion;
    float price, distance, fuel; 
    ifstream archivo;
    archivo.open("Vuelos.txt");
    if (archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
    }else{
        while (archivo >> date>>numFlight >>fromTo>>price>>distance>>airplaneModel>>hour>>crew>>fuel>>duracion) {
            cout<< date << " " << numFlight;
            Flight vuelo(numFlight, date, fromTo, price, distance, airplaneModel, hour,crew,fuel,duracion);
            vecVuelo.push_back(vuelo);
        }
        archivo.close();
    }
}
void printVecVuelos(vector<Flight> vector) {
    for (int i = 0; i < vector.size(); i++){
        vector[i].printFlight();
    }
}

void filterVueloFecha (string date, vector<Flight> vector) {
    int found;
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].getDate() == date){
        vector[i].printFlight();
        found++;
        }
    }
    if (found==0){
        cout<< "No hay vuelos para el: "<<date<<endl;
    }
}
int reservaAsientos(int index, vector<Flight> &vuelos){
    string op;
    int count = 0;
    cout<<"Deseas agregar un pasajero?(si/no) ";
    cin>>op;
    while (op =="si"){
        int seatNumber;
        cout << "Cual asiento quieres, entre 1-10: ";
        cin >> seatNumber;
        if (vuelos.at(index).reserveSeat(seatNumber)) {
            count++;
        }
        cout<<"Deseas agregar un pasajero?(si/no) ";
        cin>>op;
    }
    return count;
}
void updatePassengerInfo(vector<Passenger> passengers,Passenger loggedInPassenger){
    string name, phone,password;
    float kms;
    for (int i=0;i<passengers.size();i++){
        if (passengers[i].getName() ==loggedInPassenger.getName() && passengers[i].getPhone()==loggedInPassenger.getPhone()){
            passengers[i].setKms(loggedInPassenger.getKms());
            ifstream archivo;
            archivo.open("Usuarios.txt");
            if (archivo.fail()){
                cout << "Error al abrir archivo"<<endl;
            } else {
                while (archivo >> name >> password >> phone >> kms){
                    Passenger userTemp(name, password, phone, kms);
                }
            archivo.close();
            }
        }
    }
}

void reservaVuelo(vector<Flight> &vuelos, Passenger &loggedInPassenger){
    float price;
    int numVuelo;
    float distance;
    cout<<"Ingresa el numero de vuelo que te interesa: ";
    cin>>numVuelo;
    cout<<endl;
    for (int i=0; i<vuelos.size();i++){
        if (vuelos[i].getNumFlight() == numVuelo){
            cout<<"Este es el vuelo que elegiste"<<endl;
            vuelos[i].printFlight();
            int numReserved = reservaAsientos(i, vuelos);
            if (loggedInPassenger.getKms()>50000){
                price=vuelos[i].getPrice() * numReserved * 0.60;
            }else{
                price=vuelos[i].getPrice() * numReserved;
            }
            addReservationToFile(vuelos[i], loggedInPassenger, price);
            cout<<"El precio final es: "<<price<<endl;
            int flightKms = vuelos[i].getDistance() * numReserved + loggedInPassenger.getKms();
            cout<<"Los kilometros acumulados son: "<<flightKms<<endl;
            loggedInPassenger.setKms(flightKms);
        }
    }
}
void cancelaVuelo(vector<Flight> &vuelos, Passenger &loggedInPassenger){
    float price;
    int numVuelo;
    float distance;
    cout<<"Ingresa el numero de vuelo que deseas cancelar: ";
    cin>>numVuelo;
    cout<<endl;
    for (int i=0; i<vuelos.size();i++){
        if (vuelos[i].getNumFlight() == numVuelo){
            cout<<"Este es el vuelo que cancelaras"<<endl;
            vuelos[i].printFlight();
            cancelReservationToFile(vuelos[i], loggedInPassenger, price);
        }
    }
}

void filterVueloDestino (vector<Flight> vector, string destino) {
    int found;
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].getFromTo() == destino) {
        vector [i].printFlight();
        found++;}
    }
    if (found==0){
        cout<< "No hay vuelos con el destino: " << destino << endl;
    }
}

int main(){
    //Login
    vector<Passenger> passengers;
    vector<Flight> vuelos;
    string destino, aerolinea;
    string date;
    fillVecUsers(passengers);
    fillVecVuelos(vuelos);
    Passenger loggedInPassenger;

    int menuUser=0;
    do{
        int opMenuUser;
        cout<<"-----------------------"<<endl;
        cout<<"****** USER MENU ******="<<endl;
        cout<<"1. Registra"<<endl;
        cout<<"2. Ingresa"<<endl;
        cout<<"3. Salir" << endl;
        cout<<"Seleccione la opcion que desea: ";
        cin>>opMenuUser;
        cout<<"-----------------------"<<endl;
        if (opMenuUser ==1){
            if (registraUser(passengers)) {
                cout<<"El usuario ha sido registrado" << endl;
            } else {
                cout<<"Hubo un problema registrando al usuario" << endl;
            }
            /*std::cout << "Precione enter para continuar ... ";
            std::cin.get();
            system("CLS");*/
        }else if (opMenuUser==2){
            login(passengers, loggedInPassenger);
            menuUser=1;
            int menuOp=0;
            do{
                int opMenuOp=0;
                cout<<"----------------------------------"<<endl;
                cout<<"****** OPERACIONES DEL MENU ******"<<endl;
                cout<<"1. Ver la lista de pasajeros"<<endl;
                cout<<"2. Ver lista de vuelos"<<endl;
                cout<<"3. Filtrar vuelos por fecha" << endl;
                cout<<"4. Filtrar vuelos por destino"<<endl;
                cout<<"5. Reserva un vuelo" <<endl;
                cout<<"6. Cancela un vuelo" <<endl;
                cout<<"7. Salir" << endl;
                cout<<"Seleccione la opcion que desea: ";
                cin>>opMenuOp;
                cout<<"----------------------------------"<<endl;

                if (opMenuOp ==1){
                    printVecPasajeros(passengers);
                }else if (opMenuOp==2){
                    printVecVuelos(vuelos);
                }else if (opMenuOp==3){
                    cout<<"Ingrese la fecha (dia mes anio) seperados con / y sin espacios: ";
                    cin>>date;
                    filterVueloFecha(date, vuelos);
                }else if (opMenuOp==4){
                    cout<<"Ingrese la trayectoria del vuelo con un guion (ejemplo:Guadalajara-Puebla): ";
                    cin>>destino;
                    filterVueloDestino(vuelos, destino);
                }else if (opMenuOp==5){
                    reservaVuelo(vuelos, loggedInPassenger);
                    loggedInPassenger.printPassenger();
                    for(auto vuelo : vuelos) {
                        vuelo.printFlight();
                    }
                }else if (opMenuOp==6){
                    cancelaVuelo(vuelos, loggedInPassenger);
                }else if(opMenuOp==7){
                    cout<< "Saliendo . . ."<<endl;
                    menuOp=1;
                }else{
                    cout<<"Opcion no valida"<<endl;
                }
            }while (menuOp==0);
        }else if (opMenuUser==3){
            menuUser=1;
            cout<<"Saliendo . . ."<<endl;
            /*std::cout << "Precione enter para continuar ... ";
            std::cin.get();*/
            system("CLS");
        }else{
            cout<<"Opcion no valida"<<endl;
            system("CLS"); 
        }
    }while (menuUser==0);
    return 0;
}