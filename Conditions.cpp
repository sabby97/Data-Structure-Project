#include "Conditions.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <queue>
using namespace std

/*

  Constructor set's ChashTable size to ChashTableSize and ShashTable size to ShashTableSize

*/

Conditions::Conditions(int ChashTableSize, int ShashTableSize){
  this->ChashTableSize=ChashTableSize;
  this->ShashTable=ShashTableSize;
  ChashTable= new condition* [ChashTableSize]; //condition type
  ShashTable= new symptom* [ShashTableSize]; //symtom type
  for (int i=0; i<ChashTableSize; i++) // set ChashTable indicies to nullptr;
  {
    ChashTable[i]=nullptr;
  }
  for (int j=0; j<ShashTableSize; j++) // set ShashTable indicies to nullptr;
  {
    ShashTable[j]=nullptr;
  }
}

/*
  Hastable delete so basically go down the array and than go down the linked list for a given index in an array
*/
Conditions::~Conditions(){
  for (int i=0; i<ChashTableSize; i++) // deleting from the ChashTable
  {
    condition* temp=ChashTable[i];
    while (temp!=0)
    {
      condition* del = temp;//create del and repoint
      temp=temp->next;
      delete del;
    }
  }
  delete []ChashTable;

  for (int j=0; j<ShashTableSize; j++) // deleting from ShashTable
  {
    symptom* temp=ShashTable[i];
    while (temp!=0)
    {
      symptom* del = temp;//create del and repoint
      temp=temp->next;
      delete del;
    }
  }
  delete []ShashTable;
}

/*
  Pass in file name, opens file, first while loop reads in every line with getline and saves in "line",
  stringstream gets name and priority(use stoi to turn into integer), then use another while loop to
  read in the associated symptoms with stringstream, create symptoms, create pointers and put into a set.
  Then call add function and pass in all parameters
*/
void Conditions::readFile(string file){
  ifstream file;
  file.open(file);
  if (! file.is_open()){
    cout<<"File didn't open"<<endl;
    return;
  }
  string line;
  while(getline(file, line))//gets each line in file
  {
    if (line=="") break;
    stringstream s1(line);
    string name;
    string prior;
    int priority;
    getline(s1, name, ',');//stringstream gets name of condition
    getline(s1,prior,',');//gets priority
    priority=stoi(prior);
    string sympt;
    set<symptom*> symptoms;
    while(getline(s1, sympt,','))//gets each symptom
    {
      if (sympt=="") break;
      symptom temp;//create a symptom
      temp.name=sympt;
      symptom* pointer=temp;//create a pointer to symptom
      symptoms.insert(pointer);//push pointer into set of symptoms
      }
    condition* conditionpointer=Cadd(name, priority, symptoms);//add condition to ChashTable
    set<symptom*>::iterator i=symptoms.begin();
    while(it!=symptoms.end())//iterate through set of symptoms
    {
      *i->conditions.insert(conditionpointer);//at each symptom insert condition pointer into set of condition pointers
      Sadd(*i);//add symptom to ShashTable
      i++;
    }
  }
}

/*
  we pass in the string name, it's priority, a set of symptom pointers; add the condition to the hastable at the correct index
*/

condition* Conditions::Cadd(string name, int priority, set<symptom*> symptoms ){
  int index = ChashFunction(name);
  condition temp;
  temp.name = name;
  temp.priority = priority;
  temp.symptoms = symptoms;
  if(ChashTable[index] == 0){
    ChashTable[index] = temp;
    return ChashTable[index];
  }
  else{
    condition *trav = ChashTable[index];
    while(trav->next != 0){
      trav = trav->next;
    }
    trav->next = temp;
    return trav->next;
  }
}

/*
  we pass in a symtom and we just add to the ShashTable
*/

void Conditions::Sadd(symptom* temp1){
  int index = ShashFunction(temp1.name);
  if(ChashTable[index] == 0){
    ChashTable[index] = temp1;
  }
  else{
    condition *trav = ChashTable[index];
    while(trav->next != 0){
      trav = trav->next;
    }
    trav->next = temp1;
  }
}

/*
  The ChashFunction
*/

int Conditions::ChashFunction(string word){
  unsigned int hashValue = 5381;
  int length = word.length();
  for (int i=0;i<length;i++)
  {
  hashValue=((hashValue<<5)+hashValue) + word[i];
  }
  hashValue %= ChashTableSize;
  return hashValue;
}

/*
  The ShashFunction
*/

int Conditions::ShashFunction(string word){
  unsigned int hashValue = 5381;
  int length = word.length();
  for (int i=0;i<length;i++)
  {
  hashValue=((hashValue<<5)+hashValue) + word[i];
  }
  hashValue %= ShashTableSize;
  return hashValue;
}

/*
  used when the patient already knows their condition and we add them to the queue
*/
condition* Conditions::searchCondition(string name){
  int index = ShashFunction(name);
  if( ShashTable[index] == 0){
    cout<<"Your condition does not exist in our database, please go to the menu to diagnose you condition"<<endl;
    return 0;
  }
  else{
    condition *trav = ChashTable[index];
    while(trav->next != 0){
      if(trav->name != name){
        trav = trav->next;
      }
      else{
        return trav;
      }
    }
    cout<<"Your condition does not exist in our database, please go to the menu to diagnose you condition"<<endl;
    return 0;
  }
}

void Condition::menu(){
  while(){
    cout<<"1. If this is an medical emergency please e"
  }
}

void Condition::createPatient(string name, int pain)
{
  delete 
}
