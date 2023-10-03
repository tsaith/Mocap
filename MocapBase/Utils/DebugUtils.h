#pragma once

#include <iostream>
#include <string>


namespace db_utils {

	using namespace std;
	using std::string;

	void DbPrintArray(string name, float* arr, int dims);
	void DbPrintPoint(string name, float* point);
	void DbPrintVector(string name, float* vec);
	void DbPrintQuat(string name, float* quat);

} // Namespace
