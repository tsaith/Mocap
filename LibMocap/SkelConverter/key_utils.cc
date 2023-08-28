#include "pch.h"

#include "key_utils.h"

KeyUtils::KeyUtils() {

}

KeyUtils::~KeyUtils() {

}

int KeyUtils::KeyAction(int ASCII) {
    // button '1' 豬探長
    if(ASCII == 49) {
        Role1_enable = 1;
        Role2_enable = 0;
        Role3_enable = 0;
        //Capsule[0] = 0.8;   // limit wrist
        //Capsule[1] = 0.8;   // limit elbow
        Capsule[0] = 0.7;   // limit wrist
        Capsule[1] = 2.0;   // limit elbow
        mState = 1;
    }
    // button '2' 花生
    else if(ASCII == 50) {
        Role1_enable = 0;
        Role2_enable = 1;
        Role3_enable = 0;
        //Capsule[0] = 0.6;   // limit wrist
        //Capsule[1] = 1.0;   // limit elbow
        Capsule[0] = 0.75;   // limit wrist
        Capsule[1] = 2.0;   // limit elbow
        mState = 1;
    }
    // button '3' 狐萊
    else if(ASCII == 51) {
        Role1_enable = 0;
        Role2_enable = 0;
        Role3_enable = 1;
        //Capsule[0] = 0.5;   // limit wrist
        //Capsule[1] = 1.0;   // limit elbow
        Capsule[0] = 0.6;   // limit wrist
        Capsule[1] = 0.65;   // limit elbow
        mState = 1;
    }
    // button 'C', 'c'
    else if(ASCII == 67 || ASCII == 99) {
        Depth_enable = 1;
        mState = 1;
    }
    // button 'M', 'm'
    else if(ASCII == 77|| ASCII == 109) {
        if(Mirror_enable == 0) {
            Mirror_enable = 1;
        }
        else {
            Mirror_enable = 0;
        }
        cout << "Mirror_enable:" << Mirror_enable << endl;
        mState = 1;
    }
    // button 'R', 'r'
    else if(ASCII == 82 || ASCII == 114) {
        Reset_enable = 1;
        mState = 1;
    }
    // button 'esc', 'Q', 'q'
    else if (ASCII == 27 || ASCII == 81 || ASCII == 113) {
        Quit_enable = 1;
        mState = 1;
    }
    // button 'S', 's'
    else if (ASCII == 83 || ASCII == 115) {
        if(Show_enable == 0) {
            Show_enable = 1;
        }
        else {
            Show_enable = 0;
        }
        mState = 1;
    }
    // button 'K', 'k' for manual calibration
    else if (ASCII == 75 || ASCII == 107) {
        if(Manual_calib_enable == 0) {
            Manual_calib_enable = 1;
        }
        cout<<"Press K(k)- Start calibration" <<Manual_calib_enable<<endl;
        mState = 1;
    }
    else {
        mState = 0;
    }

    return mState;
}