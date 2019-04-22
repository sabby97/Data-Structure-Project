#include "Conditions.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*

  Constructor set's ChashTable size to ChashTableSize and ShashTable size to

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
    while(i!=symptoms.end())//iterate through set of symptoms
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
  int index = ChashFunction(name);
  if( ChashTable[index] == 0){
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
  string a1;
  int a;
  cout<<"1. If this is an medical emergency please enter 1"<<endl;
  cout<<"2. If you would like to make a appointment please enter 2"<<endl;
  getline(cin, a1));
  a = stoi(a1);

  if(a == 1){
    cout<<"We are contacting emergency service. We will get you help as soon as possible"<<endl;
    return;
  }
  else{
    createPatient();
    menu1();
    cin.ignore();
    getline(cin, a1);
    a=stoi(a1);
    if (a==1){
      cout<<"Enter your medical condition: "<<endl;
      string a2;
      cin.ignore();
      getline(cin, a2);
      patient->condition=searchCondition(a2);
    }
    if (a == 2){
      string done;
      int temp;
      set<symptom*> p;
      cout<<"Select from the following symptoms: "<<endl;
      while( done != "done"){
        printSymptoms();
        cout<<"Please enter the name condition and If you are done selecting your symptoms please type: done"<<endl;
        getline(cin, done);
        if (done != "done"){
          symptom* temp1 = searchSymptom(done);
          p.insert(temp1);
        }
      }
      patient->symptoms = p;
    }
    else{
      return;
    }
  }
}

void Condition::menu1(){
  cout<<"Choose from one of the following options: "<<endl;
  cout<<"1. If you are know your medical condition "<<endl;
  cout<<"2. Help diagnose your medical condition "<<endl;
  cout<<"3. Exit the program "<<endl;
}

void Condition::menu2(){}

/*Aks for imput, creates new patient, points patient to new patient and deletes old patient*/
void Condition::createPatient(){
  patient* temp=this->patient;
  string name;
  string painstr;
  int pain;
  cout<<"Please enter your name: ";
  cin.ignore();
  getline(cin, name);
  cout<<"Please enter your current pain level ranging from 1-20 :";
  getline(cin, painstr);
  pain=stoi(painstr);
  patient newpatient;
  newpatient.name=name;
  newpatient.pain=pain;
  this->patient=newpatient;
  delete temp;
}

/*prints symptoms from hashtable*/
void Condition::printSymptoms(){
  int cnt=1;
  for (int i=0; i<ShashTableSize; i++)
  {
    if (ShashTable[i]!=0)
    {
      condition* temp=ShashTable[i];
      while(temp!=0)
      {
        cout<<cnt<<"."<<temp->name<<endl;
        temp=temp->next;
        cnt++;
      }
    }
  }
}

symptom* Conditions::searchSymptom(string name){
  int index =ShashFunction(name);
  if( ShashTable[index] == 0){
    cout<<"Sorry, you mistyped the symptom."<<endl;
    return 0;
  }
  else{
    condition *trav = ShashTable[index];
    while(trav->next != 0){
      if(trav->name != name){
        trav = trav->next;
      }
      else{
        return trav;
      }
    }
    cout<<"Sorry, you mistyped the symptom."<<endl;
    return 0;
  }
}

/*gets intersection of two symptom sets and returns intersection as a set*/
set<symptom*> Conditions::getIntersection(set<symptom*> set1, set<symptom*> set2){
  set<symptom*> intersect;
  set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersect, intersect.begin()));
  return intersect;
}
/*gets union of two condition sets and returns union as a set*/
set<condition*> Conditions::getUnion(set<condition*> set1, set<condition*> set2){
  set<condition*> union;
  set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(union, union.begin()));
  return union;
}
/*returns size of intersect divided by patient set (matching percentage)*/
float Conditions::getPercentage(set<symptom*> intersect){
  float percent=intersect.size()/patient->symptoms.size();
  return percent;
}
/*puts conditions in priority queue based on matching percentage, returns priority queue*/
priority_queue<condition*> Conditions::getBestMatchConditions(){

<<<<<<< HEAD
  set<condition*> allconditions;
  set<condition*>::iterator i;
  for(i=patient->symptoms.begin(); i!=patient->symptoms.end(); ++i){
    allconditions=getUnion(allconditions, (*i)->conditions);
  }
  priority_queue<condition*> matchedlist;
  set<condition*>::iterator j;
  for(j=allconditions.begin(); j!=allconditions.end(); ++j){
=======
  set<condition> allconditions;
  set<condition>::iterator i;
  for(i=patient->symptoms.begin(); i!=patient->symptoms.end(); i++){
    allconditions=getUnion(allconditions, (*i)->conditions);
  }
  priority_queue<condition> matchedlist;
  set<condition>::iterator j;
  for(j=allconditions.begin(); j!=allconditions.end(); j++){
>>>>>>> ee93cb52926465981a77a23d0a03216d3ed17428
    (*j)->percentage=getPercentage(getIntersection(*i, patient->symptoms));
    matchedlist.push(*j);
  }
  return matchedlist;
}
/*if there is one perfect match, saves that as patient's condition; if multiple perfect matches or close matches,
patient gets to choose their condition or describe to doctor. If no close matches, patient describes their condition.*/
void Conditions::analyzeMatchedConditions(priority_queue<condition*> Q){
  vector<condition*> C;
  if(Q.top->percentage==1){
    while(Q.top->percentage==1){
      condition* temp=Q.top();
      Q.pop();
      C.push(temp);//unfinished
    }
<<<<<<< HEAD
    if(C.size==1){
      cout<<"We have found one perfect match condition: "<<C.front()->name<<endl;
      patient->condition=c.front();
      return;
    }
    else{
      cout<<"Here are the perfect matches with their lists of symptoms. Enter the number of the one you identify with the most "<<endl;
      cout<<"If you don't identify with any of the matched conditions, type 'none' to open a window to describe your symptoms and allow our doctors to judge your condition."<<endl;
      //print symptoms (choices)
      for (int i=0; i<C.size(); i++){
        cout<<i+1<<")["<<C[i]->name<<"] -- symptoms:";
        set<symptom*>::iterator j;
        for(j=C[i]->symptoms.begin(); j!=C[i]->symptoms.end(); ++j){
          cout<<"||"<<(*j)->name;
        }
        cout<<endl;
      }
      //patient's choice
      int choice;
      string temp;
      cin.ignore(0);
      getline(cin, temp);
      choice=stoi(temp);
      if (choice==0){
        //call description
        writeDescription();
      }
      else if(choice>0 && choice<=C.size()){
        patient->condition=C[choice-1];
      }
      return;
    }
  }
  else if (Q.top->percentage>=0.3){
    while(Q.top->percentage>=1){
      condition* temp=Q.top();
      Q.pop();
      C.push(temp);//unfinished
    }
    cout<<"These are close matches to your symptoms. Enter the number of the one you identify with the most."<<endl;
    cout<<"If you don't identify with any of these conditions, enter 0 to open a window to describe your symptoms to the doctor."<<endl;
    for (int i=0; i<C.size(); i++){
      cout<<i+1<<")["<<C[i]->name<<"] -- matching percentage:"<<C[i]->percentage<<" ; symptoms:";
      set<symptom*>::iterator j;
      for(j=C[i]->symptoms.begin(); j!=C[i]->symptoms.end(); ++j){
        cout<<"||"<<(*j)->name;
      }
      cout<<endl;
    }
    //patient's choice
    int choice;
    string temp;
    cin.ignore(0);
    getline(cin, temp);
    choice=stoi(temp);
    if (choice==0){
      //call description
      writeDescription();
    }
    else if(choice>0 && choice<=C.size()){
      patient->condition=C[choice-1];
    }
    return;

  }
  else{
    cout<<"Sorry we didn't not find a match for your symptoms in our database."
    //call description function
    writeDescription();
    return;
=======
    if
>>>>>>> ee93cb52926465981a77a23d0a03216d3ed17428
  }
}
/*patient describes symptoms, send to doctor*/
void Conditions::writeDescription(){
  cout<<"Please describe your symptoms as precisely as possible: "<<endl;
  string description;
  cin.ignore(0);
  getline(cin, description);
  ofstream file;
  file.open("patientdescription.txt");
  if(file.is_open()){
    file<<patient->name<<":"<<description<<endl;
  }
  file.close();//FIGURE OUT HOW TO NOT OVERWRITE EACH TIME.
  cout<<"Your description has been sent to the doctor for further analysis."<<endl;
}
/*resets percentage of all conditions to 0 for next patient*/
void Conditions::resetPercentage(){
  for(int i=0; i<ChashTableSize; i++)
  {
    if (ChashTable[i]!=0)
    {
      condition* temp=ChashTable[i];
      while(temp!=0)
      {
        temp->percentage=0;
        temp=temp->next;
      }
    }
  }
}
/**/
void Condition::treatPatient(){
  patient* temp;
  temp=queue.top();
  queue.pop();
  cout<<"Now treating patient "<<temp->name<<endl;
  updateQueue();
  cout<<"Next patient (predicted): "<<queue.top()->name<<endl;
}
void Condition::addPatienttoqueue(){

}
void Condition::updateQueue();//NOT IMPLEMENTED
void Condition::printOrder();//NOT IMPLEMENTED
