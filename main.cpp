#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
using namespace std;
#include "bst.h"
#include "hashtable.h"
#include "lista.h"
#include "avl.h"
#include "persona.h"



void censo(Hashtable<string, Persona> &c, const string PATH) {
  ifstream file(PATH);
  string line;
  int count = 0;
  getline(file, line);
  while (getline(file, line)) {
    stringstream ss(line);
    string first_name, last_name, city, gender, dob, phone, email, state, id,
        zip;
    getline(ss, id, ',');
    getline(ss, first_name, ',');
    getline(ss, last_name, ',');
    getline(ss, gender, ',');
    getline(ss, dob, ',');
    getline(ss, phone, ',');
    getline(ss, email, ',');
    getline(ss, zip, ',');
    getline(ss, city, ',');
    getline(ss, state, ',');
    Persona p(stoi(id), first_name, last_name, gender, dob, phone, email,
              stoi(zip), city, state);
    c.put(city, p);
  }
}

void sortStack(Stack<Persona> &inputStack) {
  Stack<Persona> tmpStack;
  while (!inputStack.is_empty()) {
    Persona temp = inputStack.pop();
    string temp2 = temp.getLastName();
    while (!tmpStack.is_empty() && tmpStack.getLast().getLastName() < temp2) {
      inputStack.push(tmpStack.pop());
    }
    tmpStack.push(temp);
  }
  while (!tmpStack.is_empty()) {
    inputStack.push(tmpStack.pop());
  }
}

void loadStack3(const string PATH, Stack<Persona> &stack) {
  ifstream file(PATH);
  string line;
  string name;
  getline(file, line);
  while (getline(file, line)) {
    stringstream ss(line);
    string first_name, last_name, city, gender, dob, phone, email, state, id,
        zip;
    getline(ss, id, ',');
    getline(ss, first_name, ',');
    getline(ss, last_name, ',');
    getline(ss, gender, ',');
    getline(ss, dob, ',');
    getline(ss, phone, ',');
    getline(ss, email, ',');
    getline(ss, zip, ',');
    getline(ss, city, ',');
    getline(ss, state, ',');
    Persona p(stoi(id), first_name, last_name, gender, dob, phone, email,
              stoi(zip), city, state);
    stack.push(p);
  }
}

void loadDataLinkedLists(Hashtable<string, Persona> &h,
                         LinkedList<Persona> &personas) {
  LinkedList<string> keys = h.keys();
  while (!keys.is_empty()) {
    string key = keys.remove_front();
    do {
      Persona p = h.getOrDefault(key, Persona());
      // cout << p;
      if (p)
        personas.addLast(p);
    } while (h.remove(key));
  }
}

void desplegarCenso(Hashtable<string, Persona> &h) {
  LinkedList<Persona> personas;
  LinkedList<string> ciudades = h.keys();
  loadDataLinkedLists(h, personas);
  while (!ciudades.is_empty() && !personas.is_empty()) {
    string ciudad = ciudades.remove_front();
    int n = 0;
    cout << "-\t" << ciudad << ": ";
    while (personas.getFirst().getCity() == ciudad) {
      personas.remove_front();
      n++;
      if (personas.is_empty())
        break;
    }
    cout << n << "\n";
  }
}

void printCiudades(Hashtable<string, Persona> &h){
  LinkedList<Persona> personas;
  LinkedList<string> ciudades = h.keys();
  loadDataLinkedLists(h, personas);
  AVL<string> cities;
  while(!ciudades.is_empty() && !personas.is_empty()){
    string ciudad = ciudades.remove_front();
    cities.insert(ciudad);
  }

  cities.inOrden();
}

void displayPriority(Queue<Persona> &personas) {
  PriorityQueue<Persona> priorizada;
  while (!personas.is_empty()) {
    priorizada.insert(personas.dequeue());
  }
  // priorizada.printAsc(); Hace lo mismo sin borrar datos
  while (!priorizada.is_empty()) {
    Persona p = priorizada.dequeueMin();
    cout << p;
  }
}

void menu(const string PATH) {
  Hashtable<string, Persona> c(10000);
  Queue<Persona> queuePersonas;
  Stack<Persona> stackPersonas;
  censo(c, PATH);
  int num;
  do {
    cout << " -- Ingresa una opcion --\n"
         << "1. Censo poblacional" << endl
         << "2. Ordenamiento de los habitantes" << endl
         << "3. Imprimir habitantes usando el ZIP" << endl
         << "4. Ordenar ciudades\n";
    cin >> num;
    switch (num) {
    case 1:
      desplegarCenso(c);
      break;

    case 2:
      loadDataLinkedLists(c, stackPersonas);
      // sortStack(stackPersonas);
      cout << stackPersonas;
      break;

    case 3:
      loadDataLinkedLists(c, queuePersonas);
      displayPriority(queuePersonas);
      break;

    case 4:
      printCiudades(c);
      break;

    default:
      cout << "opción no válida" << endl;
    }

  } while (num <= 4 && num >= 1);
}

int main(int argc, char **argv) {
  string path = "";
  if (argc < 2)
    path = "bitacora.csv";
  else
    path = argv[1];
  menu(path);
  return 0;


}