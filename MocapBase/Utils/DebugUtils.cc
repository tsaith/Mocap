#include "pch.h"

#include "DebugUtils.h"

namespace db_utils {

void DbPrintArray(string name, float* arr, int dims) {

    string msg = "";
    msg += name + ":";

    int lastIndex = dims - 1;
    for (int i=0; i < lastIndex; i++) {
        msg += to_string(arr[i]) + ", ";
    }

    if (lastIndex > 0) {
        msg += to_string(arr[lastIndex]);
    }

    cout << msg << endl;

}

void DbPrintPoint(string name, float* point) {
    DbPrintArray(name, point, 3);
}

void DbPrintVector(string name, float* vec) {
    DbPrintArray(name, vec, 3);
}

void DbPrintQuat(string name, float* quat) {
    DbPrintArray(name, quat, 4);
}

} // namespace