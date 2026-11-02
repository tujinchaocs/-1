#include "person.h"
#include <iostream>
#include <string.h>
using namespace std;
Person::Person(char nameV[], bool sexV, int ageV, float heightV, float weightV)
{
    cout << "设置人的属性" << endl;
    strcpy(name, nameV);
    sex = sexV;
    age = ageV;
    height = heightV;
    weight = weightV;
}
Person::~Person()
{
    cout << "析构" << name << endl;
}
int main()
{

    return 0;
}