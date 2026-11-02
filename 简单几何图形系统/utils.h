#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
using namespace std;
const double EPSILON = 1e-2; // 判分误差（保留两位小数）
const double PI = acos(-1.0);
const string DATA_FILE = "geometry_record.txt";
string getCurrentTime(); // 三个函数只放声明
int getIntInput(const string &prompt);
double getDoubleInput(const string &prompt);