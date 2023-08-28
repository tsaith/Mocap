#ifndef GESTURE_H
#define GESTURE_H

#include <iostream>
#include <string>

using namespace std;

class Gesture {

public:

    Gesture() {
        SetInitialValues();
    }

    ~Gesture() {
    }

    // Flags and arrays
    string LeftStaticGesture;
    string LeftDynamicGesture;
    string RightStaticGesture;
    string RightDynamicGesture;
    
    int LeftStaticGestureIdx;
    int LeftDynamicGestureIdx;
    int RightStaticGestureIdx;
    int RightDynamicGestureIdx;

    void SetInitialValues() {
        LeftStaticGesture = "NULL";
        LeftDynamicGesture = "NULL";
        RightStaticGesture = "NULL";
        RightDynamicGesture = "NULL";

        LeftStaticGestureIdx = 0;
        LeftDynamicGestureIdx = 0;
        RightStaticGestureIdx = 0;
        RightDynamicGestureIdx = 0;
    }

    // Copy constructor
    Gesture(const Gesture &g) {
        LeftStaticGesture = g.LeftStaticGesture;
        LeftDynamicGesture = g.LeftDynamicGesture;
        RightStaticGesture = g.RightStaticGesture;
        RightDynamicGesture = g.RightDynamicGesture;

        LeftStaticGestureIdx = g.LeftStaticGestureIdx;
        LeftDynamicGestureIdx = g.LeftDynamicGestureIdx;
        RightStaticGestureIdx = g.RightStaticGestureIdx;
        RightDynamicGestureIdx = g.RightDynamicGestureIdx;
    }
};

#endif // GESTURE_H
