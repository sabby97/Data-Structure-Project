#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

struct symptom{
    string name;
    set<condition*> conditions;
    symptom* next = 0;
};

struct condition{
  string name;
  int priority;
  set <symptom*> symptoms;
  symptom* next = 0;

};

struct patient{
  string name;
  set<string> symptoms;
  condition* condition;
  int pain;
};


class Conditions {// AKA diseases
private:
  Conditions();
  ~Conditions();
  int ChashFunction(string word);
  int ShashFunction(string word);


public:
  void menu();
  condition** ChashTable;
  int ChashTableSize;
  void readFile(string file);
  void Cadd(string name, int priority, set<symptom> symptoms);


  symptom** ShashTable;
  int ShashtableSize;
  void Sadd(symptom* sympt);
  condition* searchCondition(string name);

  patient* patient;
  void createPatient(string name, int pain);



};










// BUILDING THE SYMPTOMS/CONDITION LIBRARY
///////

// read symptoms/condition(name) file into vector set.
//read condition/priority file into vector of structs(which includes the description of the condiation and pirority)

///////

// FUNCTIONS TO DEAL WITH PATIENT
////////
//function to input information
//function to configure medical condition
// function to add the condition pirority and the pain level
//add condition to maxheap
//function to output estimated appointment time

/////////////
