#pragma once
#include "KDTree.h"

#ifndef Command_H
#define Command_H
#endif


vector<City> loadCitiesFromCSV(string filename);
double stringToDouble(const std::string& str);
void distinguishPoints(Point& point1, Point& point2, Point& bottomLeft, Point& topRight);
bool isCSVFormat(string filename);
bool isNumber(string str);
void writeCitiesToCSVFilee(string fileName, vector<City> cities);
void writeCityToCSVFile(string fileName, City city);

