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
  float percentage;
  set <symptom*> symptoms;
  condition* next = 0;
  condition* after = 0;
};

struct patient{
  string name;
  set<string> symptoms;
  condition* condition;
  int pain;
  int totalP; // total priority, priority of the disease plus the pain level
};


class Conditions {// AKA diseases
private:
  Conditions();
  ~Conditions();
  int ChashFunction(string word);
  int ShashFunction(string word);


public:
  void menu();
  void menu1();
  void menu2();

  condition** ChashTable;
  int ChashTableSize;
  void readFile(string file);
  void Cadd(string name, int priority, set<symptom> symptoms);


  symptom** ShashTable;
  int ShashTableSize;
  void Sadd(symptom* sympt);
  void assignOrder();
  condition* searchCondition(string name);
  void printSymptoms();
  symptom* searchSymptom(string name);

  patient* patient=0;
  void createPatient();
  set<symptom> getIntersection(set<symptom> set1, set<symptom> set2);
  set<condition> getUnion(set<condition> set1, set<condition> set2);
  float getPercentage(set<symptom> intersect);
  set<condition> getBestMatchConditions();


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
