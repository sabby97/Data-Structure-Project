#include "Conditions.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

Conditions::Conditions(int ChashTableSize, int ShashTableSize){  //Check Sabby
  this->ChashTableSize=ChashTableSize;
  this->ShashTable=ShashTableSize;
  ChashTable= new condition* [ChashTableSize]; //condition type
  ShashTable= new symptom* [ShashTableSize]; //symtom type
  for (int i=0; i<ChashTableSize; i++)
  {
    ChashTable[i]=nullptr;
  }
  for (int j=0; j<ShashTableSize; j++)
  {
    ShashTable[j]=nullptr;
  }
}

Conditions::~Conditions(){ //Check Sabby
  for (int i=0; i<ChashTableSize; i++)
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

  for (int j=0; j<ShashTableSize; j++)
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

void Conditions::CreadFile(string file){//Check Sabby
  ifstream file;
  file.open(file);
  if (! file.is_open()){
    cout<<"File didn't open"<<endl;
    return;
  }
  string line;
  while(getline(file, line))
  {
    if (line=="") break;
    stringstream s1(line);
    string name;
    string prior;
    int priority;
    getline(s1, name, ',');
    getline(s1,prior,',');
    priority=stoi(priority);
    string sympt;
    set<string> symptoms;
    while(getline(s1, sympt,','))
    {
      if (sympt=="")break;
      symptoms.insert(sympt);
    }
    Cadd(name, priority, symptoms);

  }
}

void Conditions::Cadd(string name, int priority, set<symptom> symptoms ){
  int index = ChashFunction(name);
  condition temp;
  temp.name = name;
  temp.priority = priority;
  temp.symptoms = symptoms;
  if(ChashTable[index] == 0){
    ChashTable[index] = temp;
  }
  else{
    condition *trav = ChashTable[index];
    while(trav->next != 0){
      trav = trav->next;
    }
    trav->next = temp;
  }
}

int Condition::hashFunction(string word){
  unsigned int hashValue = 5381;
  int length = word.length();
  for (int i=0;i<length;i++)
  {
  hashValue=((hashValue<<5)+hashValue) + word[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}
