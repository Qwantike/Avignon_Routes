#ifndef RAWTOJSON_H
#define RAWTOJSON_H

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <algorithm>

using json = nlohmann::json;
using namespace std;

void arcsCsvToJson(const string &inputFilePath, const string &outputFilePath);
void nodesCsvToJson(const string &inputFilePath, const string &outputFilePath);

#endif // RAWTOJSON_H
