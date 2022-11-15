#pragma once
#include <iostream>
#include <string>
using namespace std;

class Persona {
private:
  string first_name, last_name, city, gender, dob, phone, email, state;
  int id, zip;

public:
  /*ID,first_name,last_name,gender,dob,phone,email,ZIP,city,state*/
  Persona(int id = 0, string fname = "", string lname = "", string gender = "",
          string dob = "", string phone = "", string email = "", int zip = 0,
          string city = "", string state = "") {
    this->id = id;
    this->first_name = fname;
    this->last_name = lname;
    this->gender = gender;
    this->dob = dob;
    this->phone = phone;
    this->email = email;
    this->zip = zip;
    this->city = city;
    this->state = state;
  }

  /*
  Agrega las sobre cargas de operadores necesarias en la clase Persona.
  */
  bool operator<(const Persona &p) { return zip < p.zip; }
  bool operator>(const Persona &p) { return zip > p.zip; }
  bool operator<=(const Persona &p) { return zip <= p.zip; }
  bool operator>=(const Persona &p) { return zip <= p.zip; }
  operator bool() const{
    return id != 0 && first_name != "" &&  last_name != "";
  }

  friend ostream &operator<<(ostream &out, Persona &p) {
    out << " | " << p.id << " | " << p.first_name << " | " << p.last_name
        << " | " << p.gender << " | " << p.dob << " | " << p.phone << " | "
        << p.email << " | " << p.zip << " | " << p.city << " | " << p.state
        << " |\n";
    return out;
  }
  string getLastName() {
    return last_name;
  }
  string getCity(){
    return city;
  }
};