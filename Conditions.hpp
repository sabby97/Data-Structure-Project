#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <queue>
using namespace std;


struct condition{
  string name;
  int priority;
  set <symptom> symptoms;

};


class Conditions {// AKA diseases
private:
  Conditions();
  ~Conditions();
  unsigned int getHash(string word);


public:
  condition** ChashTable;
  int ChashTableSize;
  void CreadFile(string file);
  void Cadd(condition* cond);
  int hashFunction(int);

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
