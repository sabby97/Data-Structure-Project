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

int main(){
  Conditions C(10, 10);
  C.readFile("conditions.txt");
  //C.system();

  C.printConditions();
  C.printSymptoms();
  //C.menu();
  //cout<<"TEST SEARCH FUNCTION"<<endl;
  //C.searchSymptom("nausea");
  //C.searchCondition("lung cancer");
  //C.printSymptoms();
//C.writeDescription();
  /*
  set<int> test;
  test.insert(1);
  test.insert(2);
  test.insert(3);
  set<int>::iterator i;
  for (i=test.begin(); i!=test.end(); ++i){
    cout<<*i<<endl;
  }*/
  return 0;
}
