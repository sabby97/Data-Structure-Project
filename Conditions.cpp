#include "Conditions.hpp"
#include <string>
#include <iterator>
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
  this->ShashTableSize=ShashTableSize;
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
    symptom* temp=ShashTable[j];
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
void Conditions::readFile(string filename){
  ifstream file;
  file.open(filename);
  if (! file.is_open()){
    cout<<"File didn't open"<<endl;
    return;
  }
  cout<<"File opened"<<endl;
  string line;
  while(getline(file, line))//gets each line in file
  {
    if (line=="") break;
    //cout<<"reading a line"<<endl;
    stringstream s1(line);
    string name;
    string prior;
    int priority;
    getline(s1, name, ',');//stringstream gets name of condition
    getline(s1,prior,',');//gets priority
    priority=stoi(prior);
    string sympt;
    set<symptom*> symptoms;
    set<int> test;
    int n=0;
    symptom* pointer=0;
    while(getline(s1, sympt,','))//gets each symptom
    {
      if (sympt=="") break;
      symptom* temp= new symptom;//create a symptom
      temp->name=sympt;
      //cout<<"reading a symptom"<<temp.name<<endl;
      pointer=temp;//create a pointer to symptom
      cout<<"insert into S-table "<<pointer->name<<endl;
      n++;
      //test.insert(n);
      cout<<"Adding symptom number "<<n<<endl;
      symptoms.insert(pointer);//push pointer into set of symptoms
      cout<<"first in set: "<<(*symptoms.begin())->name<<"; size of set is "<<symptoms.size()<<endl;
      if (searchSymptom((pointer)->name)==0){
              Sadd(pointer);//add symptom to ShashTable
      }
    condition* conditionpointer=Cadd(name, priority, symptoms);//add condition to ChashTable
    //cout<<"iterator"<<endl;
    set<symptom*>::iterator i;
    //cout<<"before while loop"<<endl;
    cout<<"size of symptoms is "<<symptoms.size()<<endl;
    for(i=symptoms.begin(); i!=symptoms.end(); ++i)//iterate through set of symptoms
    {
      //cout<<"inserting condition pointer"<<endl;
      cout<<"adding symptom "<<(*i)->name<<endl;
      (*i)->conditions.insert(conditionpointer);//at each symptom insert condition pointer into set of condition pointers
      //if (searchSymptom((*i)->name)==0){
              //Sadd(*i);//add symptom to ShashTable
      }
    }
  }
  //cout<<"Done"<<endl;
}

/*
  we pass in the string name, it's priority, a set of symptom pointers; add the condition to the hastable at the correct index
*/

condition* Conditions::Cadd(string name, int priority, set<symptom*> symptoms ){
  //cout<<"Entered Cadd"<<endl;
  int index = ChashFunction(name);
  //cout<<"hashed"<<endl;
  condition* temp= new condition;
  temp->name = name;
  temp->priority = priority;
  temp->symptoms = symptoms;
  if(searchCondition(temp->name) != 0) return 0;
  if(ChashTable[index] == 0){
    ChashTable[index] = temp;
    //cout<<"added "<<ChashTable[index]->name<<endl;
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
  int index = ShashFunction(temp1->name);
  cout<<"Sadd is adding "<<temp1->name<<endl;
  if(searchSymptom(temp1->name)!=0) return;
  if(ShashTable[index] == 0){
    ShashTable[index] = temp1;
    cout<<"added "<<ShashTable[index]->name<<endl;
  }
  else{
    symptom* trav = ShashTable[index];
    while(trav->next != 0){
      trav = trav->next;
    }
    trav->next = temp1;
    cout<<"added "<<trav->next->name<<endl;
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
        cout<<"We found "<<trav->name<<endl;
        return trav;
      }
    }
    cout<<"Your condition does not exist in our database, please go to the menu to diagnose you condition"<<endl;
    return 0;
  }
}

void Conditions::menu(){
  string a1;
  int a;
  cout<<"1. If this is an medical emergency please enter 1"<<endl;
  cout<<"2. If you would like to make a appointment please enter 2"<<endl;
  getline(cin, a1);
  a = stoi(a1);

  if(a == 1){
    cout<<"We are contacting emergency service. We will get you help as soon as possible"<<endl;
    return;
  }
  else{
    cout<<"Before createPatient"<<endl;
    createPatient();
    menu1();
    cin.ignore(0);
    getline(cin, a1);
    a=stoi(a1);
    if (a==1){
      cout<<"Enter your medical condition: "<<endl;
      string a2;
      cin.ignore();
      getline(cin, a2);
      thepatient->condition=searchCondition(a2);
      if (thepatient->condition==0){
        cout<<"Please try entering your symptoms."<<endl;
        a=2;
      }
    }
    if (a == 2){
      string done;
      int temp;
      set<symptom*> p;
      cout<<"Select from the following symptoms: "<<endl;
      while( done != "done"){
        printSymptoms();
        cout<<"Please enter the name condition and If you are done selecting your symptoms please type: done"<<endl;
        cin.ignore(0);
        getline(cin, done);
        if (done != "done"){
          symptom* temp1 = searchSymptom(done);
          p.insert(temp1);
        }
      }
      cout<<"Out of while loop"<<endl;
      set<symptom*> s;
      //s=p;
      thepatient->symptoms = p;
      cout<<"Before analyzing"<<endl;
      analyzeMatchedConditions(getBestMatchConditions());
    }
    else{
      return;
    }
  }
}

void Conditions::menu1(){
  cout<<"Choose from one of the following options: "<<endl;
  cout<<"1. If you are know your medical condition "<<endl;
  cout<<"2. Help diagnose your medical condition "<<endl;
  cout<<"3. Exit the program "<<endl;
}

void Conditions::menu2(){
}

/*Aks for imput, creates new patient, points patient to new patient and deletes old patient*/
void Conditions::createPatient(){
  cout<<"Entered createPatient function"<<endl;
  patient* temp=thepatient;
  string name;
  string painstr;
  int pain;
  cout<<"Please enter your name: ";
  cin.ignore();
  getline(cin, name);
  cout<<"Please enter your current pain level ranging from 1-20 :";
  getline(cin, painstr);
  pain=stoi(painstr);
  patient* newpatient=new patient;
  newpatient->name=name;
  newpatient->pain=pain;
  thepatient=newpatient;
  delete temp;
}

/*prints symptoms from hashtable*/
void Conditions::printSymptoms(){
  int cnt=1;
  for (int i=0; i<ShashTableSize; i++)
  {
    if (ShashTable[i]!=0)
    {
      symptom* temp=ShashTable[i];
      while(temp!=0)
      {
        cout<<cnt<<"."<<temp->name<<endl;
        temp=temp->next;
        cnt++;
      }
    }
  }
}

void Conditions::printConditions(){
  int cnt=1;
  for (int i=0; i<ChashTableSize; i++)
  {
    if (ChashTable[i]!=0)
    {
      condition* temp=ChashTable[i];
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
  int index = ShashFunction(name);
  if( ShashTable[index] == 0){
    cout<<"Sorry, you mistyped the symptom."<<endl;
    return 0;
  }
  else{
    symptom *trav = ShashTable[index];
    while(trav->next != 0){
      if(trav->name != name){
        trav = trav->next;
      }
      else{
        cout<<"Found "<<trav->name<<endl;
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
  set<condition*> union_;
  set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(union_, union_.begin()));
  return union_;
}
/*returns size of intersect divided by patient set (matching percentage)*/
float Conditions::getPercentage(set<symptom*> intersect){
  float percent=intersect.size()/thepatient->symptoms.size();
  return percent;
}
/*puts conditions in priority queue based on matching percentage, returns priority queue*/
priority_queue<condition*> Conditions::getBestMatchConditions(){

  set<condition*> allconditions;
  set<symptom*>::iterator i;
  for(i=thepatient->symptoms.begin(); i!=thepatient->symptoms.end(); ++i){
    allconditions=getUnion(allconditions, (*i)->conditions);
  }
  priority_queue<condition*> matchedlist;
  set<condition*>::iterator j;
  for(j=allconditions.begin(); j!=allconditions.end(); ++j){
    (*j)->percentage=getPercentage(getIntersection((*j)->symptoms, thepatient->symptoms));
    matchedlist.push(*j);
  }
  return matchedlist;
}
/*if there is one perfect match, saves that as patient's condition; if multiple perfect matches or close matches,
patient gets to choose their condition or describe to doctor. If no close matches, patient describes their condition.*/
void Conditions::analyzeMatchedConditions(priority_queue<condition*> Q){
  vector<condition*> C;
  if(Q.top()->percentage==1){
    while(Q.top()->percentage==1){
      condition* temp=Q.top();
      Q.pop();
      C.push_back(temp);//unfinished
    }
    if(C.size()==1){
      cout<<"We have found one perfect match condition: "<<C.front()->name<<endl;
      thepatient->condition=C.front();
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
        thepatient->condition=C[choice-1];
      }
      return;
    }
  }
  else if (Q.top()->percentage>=0.3){
    while(Q.top()->percentage>=1){
      condition* temp=Q.top();
      Q.pop();
      C.push_back(temp);//unfinished
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
      thepatient->condition=C[choice-1];
    }
    return;

  }
  else{
    cout<<"Sorry we didn't not find a match for your symptoms in our database.";
    //call description function
    writeDescription();
    return;
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
  cout<<"After file.open"<<endl;
  if(file.is_open()){
    //cout<<"In if statement"<<endl;
    file<<thepatient->name<<":"<<description<<"\n";
  }
  //cout<<"Out of if statement"<<endl;
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
/*pops patient from queue and updates queue*/
void Conditions::treatPatient(){
  patient* temp;
  temp=queue.top();
  queue.pop();
  cout<<"Now treating patient "<<temp->name<<endl;
  updateQueue();
  cout<<"Next patient (predicted): "<<queue.top()->name<<endl;
}
/*calculates total priority of patient, then pushes patient into queue*/
void Conditions::addPatienttoqueue(){
  thepatient->totalP=thepatient->condition->priority + thepatient->pain;
  patient add=*thepatient;
  queue.push(&add);
}
/*adds 10 to the priority to all patients already in queue*/
void Conditions::updateQueue(){
  priority_queue<patient*> newqueue;
  for(int i=0; i<queue.size(); i++){
    patient* temp=queue.top();
    queue.pop();
    temp->totalP+=10;
    newqueue.push(temp);//pushes updated patient into new queue
  }
  queue=newqueue;
}
/*pops each patient from queue, prints patient, puts back in new queue*/
void Conditions::printOrder(){
  cout<<"Order of patients:"<<endl;
  priority_queue<patient*> newqueue;
  for(int i=0; i<queue.size(); i++){
    patient* temp=queue.top();
    queue.pop();
    cout<<temp->name<<endl;
    newqueue.push(temp);//pushes updated patient into new queue
  }
  queue=newqueue;
}
