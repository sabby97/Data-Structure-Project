#include "Conditions.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

Conditions::Conditions()
{
  this->hashTableSize=hashTableSize;//Add this
  hashTable= new wordItem* [hashTableSize];//make wordIten into pointer
  for (int i=0; i<hashTableSize; i++)
  {
    hashTable[i]=nullptr;
  }
}
Conditions::~Conditions()
{

}
void Conditions::readFile(string file)
{
  ifstream file;
  file.open
}
void Conditions::addC(string name, int priority, set<symptom> symptoms ){
  int index = hashFunction(name);
  ChashTable[index]

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
