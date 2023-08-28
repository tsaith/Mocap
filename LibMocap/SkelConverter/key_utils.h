#ifndef KEYUTILS_H
#define KEYUTILS_H

#include <iostream>
using namespace std;

class KeyUtils {
public:
    KeyUtils();
    ~KeyUtils();
    int KeyAction(int ASCII);

    // enable parameter 0:OFF 1:ON
    int key_enable = 0;
    int Role1_enable = 0;
    int Role2_enable = 0;
    int Role3_enable = 0;
    int Depth_enable = 0;
    int Mirror_enable = 1;
    int Reset_enable = 0;
    int Quit_enable = 0;
    int Show_enable = 1;
    int Manual_calib_enable = 0;

    // [Ratio, InnerRatio]
    double Capsule[2] = {0.01, 0.01};
    
private:
    int mState = 0;

};

#endif // KEYUTILS_H