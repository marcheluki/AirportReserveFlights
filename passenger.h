#include <iostream>
#include <vector>
#include <cstdlib>
#ifndef passenger_h
#define passenger_h

using namespace std;
class Passenger{
private:
    string name;
    string password;
    string phone;
    float kms;
public:
    Passenger();
    Passenger(string, string, string, float);
    Passenger(string,string);
    ~Passenger();
    // getters
    string getName() const;
    string getPhone() const;
    float getKms();
    string getPassword() const;
    // setters
    void setName(string _name);
    void setPassword(string _password);
    void setPhone(string _phone);
    void setKms(float _kms);
    //method
    void printPassenger();
};
//constructores
Passenger::Passenger(){
    name = "Sin identificar";
    password="000";
    phone = "Sin proporcionar";
    kms = 0;
}
Passenger::Passenger(string _name, string _password, string _phone, float _kms){
    name = _name;
    password=_password;
    phone = _phone;
    setKms(_kms);
}
Passenger::Passenger(string _name,string _phone){
    name=_name;
    password="";
    kms=0;
    phone=_phone;
}
//destructor
Passenger::~Passenger(){}

//setters
void Passenger::setName(string _name){
    name=_name;
}
void Passenger::setPhone(string _phone){
    phone=_phone;
}
void Passenger::setPassword(string _password){
    password=_password;
}
void Passenger::setKms(float _kms){
    if (kms>=0){
        kms=_kms;
    }else{
        kms=0;
    }
}

//getters
string Passenger::getName() const{
    return name;
}
string Passenger::getPassword() const{
    return password;
}
string Passenger::getPhone()const{
    return phone;
}
float Passenger::getKms(){
    return kms;
}

//metodo adicional
void Passenger::printPassenger(){
    cout<<"-----------------------"<<endl;
    cout<<"** PASAJERO **"<<endl;
    cout<<"Nombre: "<<getName() << endl;
    cout<<"Telefono: "<<getPhone() <<endl;
    cout<<"Kilometros: "<<getKms()<<endl;
    cout<<"-----------------------"<<endl;
}

#endif
