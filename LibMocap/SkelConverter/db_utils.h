#ifndef DB_UTILS_H
#define DB_UTILS_H 

#include <iostream>
#include <string>

using namespace std;
using std::string;

namespace db_utils {

void DbPrintArray(string name, float* arr, int dims);
void DbPrintPoint(string name, float* point);
void DbPrintVector(string name, float* vec);
void DbPrintQuat(string name, float* quat);

} // namespace

#endif // DB_UTILS_H