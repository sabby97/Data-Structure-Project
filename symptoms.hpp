#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

struct Condition // AKA diseases
{
  string name;
  string description;
  int priority;
  set <string> symptoms;
};

struct Patient // AKA diseases
{
  string name;
  int pain;
  int date;
  int time;
  Condition myCondition;
};

public:
  void createCondition(string name, string description, int priority);
  Condition* searchCondition(string name);
  void addPain(int pain);
  void addName(string name);



private:


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
