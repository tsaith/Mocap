#ifndef HOLISTIC_H
#define HOLISTIC_H

class Holistic {
public:

    Holistic() {
        SetInitialValues();
    }

    ~Holistic() {
    }

    int GetFacemeshLandmarkNum() {
        return FACEMESH_LANDMARK_NUM;
    }

    int GetPoseLandmarkNum() {
        return POSE_LANDMARK_NUM;
    }

    int GetHandLandmarkNum() {
        return HAND_LANDMARK_NUM;
    }

    const int GetDimensions() {
        return DIMENSIONS;
    }
 
    // Left hand
    float* GetHandWristL() {
        return LeftHand[mIWrist]; 
    }

    float* GetThumb01L() {
        return LeftHand[mIThumb01]; 
    }

    float* GetThumb02L() {
        return LeftHand[mIThumb02]; 
    }

    float* GetThumb03L() {
        return LeftHand[mIThumb03]; 
    }

    float* GetThumb04L() {
        return LeftHand[mIThumb04]; 
    }

    float* GetIndex01L() {
        return LeftHand[mIIndex01]; 
    }

    float* GetIndex02L() {
        return LeftHand[mIIndex02]; 
    }

    float* GetIndex03L() {
        return LeftHand[mIIndex03]; 
    }

    float* GetIndex04L() {
        return LeftHand[mIIndex04]; 
    }

    float* GetMiddle01L() {
        return LeftHand[mIMiddle01]; 
    }

    float* GetMiddle02L() {
        return LeftHand[mIMiddle02]; 
    }

    float* GetMiddle03L() {
        return LeftHand[mIMiddle03]; 
    }

    float* GetMiddle04L() {
        return LeftHand[mIMiddle04]; 
    }

    float* GetRing01L() {
        return LeftHand[mIRing01]; 
    }

    float* GetRing02L() {
        return LeftHand[mIRing02]; 
    }

    float* GetRing03L() {
        return LeftHand[mIRing03]; 
    }

    float* GetRing04L() {
        return LeftHand[mIRing04]; 
    }

    float* GetPinky01L() {
        return LeftHand[mIPinky01]; 
    }

    float* GetPinky02L() {
        return LeftHand[mIPinky02]; 
    }

    float* GetPinky03L() {
        return LeftHand[mIPinky03]; 
    }

    float* GetPinky04L() {
        return LeftHand[mIPinky04]; 
    }

    // Right hand
    float* GetHandWristR() {
        return RightHand[mIWrist]; 
    }

    float* GetThumb01R() {
        return RightHand[mIThumb01]; 
    }

    float* GetThumb02R() {
        return RightHand[mIThumb02]; 
    }

    float* GetThumb03R() {
        return RightHand[mIThumb03]; 
    }

    float* GetThumb04R() {
        return RightHand[mIThumb04]; 
    }

    float* GetIndex01R() {
        return RightHand[mIIndex01]; 
    }

    float* GetIndex02R() {
        return RightHand[mIIndex02]; 
    }

    float* GetIndex03R() {
        return RightHand[mIIndex03]; 
    }

    float* GetIndex04R() {
        return RightHand[mIIndex04]; 
    }

    float* GetMiddle01R() {
        return RightHand[mIMiddle01]; 
    }

    float* GetMiddle02R() {
        return RightHand[mIMiddle02]; 
    }

    float* GetMiddle03R() {
        return RightHand[mIMiddle03]; 
    }

    float* GetMiddle04R() {
        return RightHand[mIMiddle04]; 
    }

    float* GetRing01R() {
        return RightHand[mIRing01]; 
    }

    float* GetRing02R() {
        return RightHand[mIRing02]; 
    }

    float* GetRing03R() {
        return RightHand[mIRing03]; 
    }

    float* GetRing04R() {
        return RightHand[mIRing04]; 
    }

    float* GetPinky01R() {
        return RightHand[mIPinky01]; 
    }

    float* GetPinky02R() {
        return RightHand[mIPinky02]; 
    }

    float* GetPinky03R() {
        return RightHand[mIPinky03]; 
    }

    float* GetPinky04R() {
        return RightHand[mIPinky04]; 
    }

    // Component is stable or not
    bool IsHeadStable() {
        return mIsHeadStable;
    }

    void SetIsHeadStable(bool Value) {
        mIsHeadStable = Value;
    }

    bool IsLeftHandStable() {
        return mIsLeftHandStable;
    }

    void SetIsLeftHandStable(bool Value) {
        mIsLeftHandStable = Value;
    }

    bool IsRightHandStable() {
        return mIsRightHandStable;
    }

    void SetIsRightHandStable(bool Value) {
        mIsRightHandStable = Value;
    }

    // Number of landmarks
    static constexpr int FACEMESH_LANDMARK_NUM = 468;
    static constexpr int POSE_LANDMARK_NUM = 33;
    static constexpr int HAND_LANDMARK_NUM = 21;
    static constexpr int DIMENSIONS = 4;

    // Hand landmark indexes
    static constexpr int WRIST = 0;
    static constexpr int THUMB_CMC = 1;
    static constexpr int THUMB_MCP = 2;
    static constexpr int THUMB_IP = 3;
    static constexpr int THUMB_TIP = 4;
    static constexpr int INDEX_FINGER_MCP = 5;
    static constexpr int INDEX_FINGER_PIP = 6;
    static constexpr int INDEX_FINGER_DIP = 7;
    static constexpr int INDEX_FINGER_TIP = 8;
    static constexpr int MIDDLE_FINGER_MCP = 9;
    static constexpr int MIDDLE_FINGER_PIP = 10;
    static constexpr int MIDDLE_FINGER_DIP = 11;
    static constexpr int MIDDLE_FINGER_TIP = 12;
    static constexpr int RING_FINGER_MCP = 13;
    static constexpr int RING_FINGER_PIP = 14;
    static constexpr int RING_FINGER_DIP = 15;
    static constexpr int RING_FINGER_TIP = 16;
    static constexpr int PINKY_FINGER_MCP = 17;
    static constexpr int PINKY_FINGER_PIP = 18;
    static constexpr int PINKY_FINGER_DIP = 19;
    static constexpr int PINKY_FINGER_TIP = 20;

    // Flags and arrays
    bool HasFacemesh = false;
    float facemesh[FACEMESH_LANDMARK_NUM][DIMENSIONS];

    bool HasPose = false; 
    float pose[POSE_LANDMARK_NUM][DIMENSIONS];

    bool HasLeftHand = false;
    float LeftHand[HAND_LANDMARK_NUM][DIMENSIONS]; 

    bool HasRightHand = false;
    float RightHand[HAND_LANDMARK_NUM][DIMENSIONS]; 


    void SetInitialValues() {

        // Facemesh
        HasFacemesh = false;
        for (int i=0; i < FACEMESH_LANDMARK_NUM; i++) {
            for (int j=0; j<DIMENSIONS; j++) {
                facemesh[i][j] = 0.0;
            }
        }

        // Pose
        HasPose = false;
        for (int i=0; i < POSE_LANDMARK_NUM; i++) {
            for (int j=0; j<DIMENSIONS; j++) {
                pose[i][j] = 0.0;
            }
        }

        // Hands
        HasLeftHand = false;
        HasRightHand = false;
        for (int i=0; i < HAND_LANDMARK_NUM; i++) {
            for (int j=0; j<DIMENSIONS; j++) {
                LeftHand[i][j] = 0.0;
                RightHand[i][j] = 0.0;
            }
        }

    }

    // Copy constructor
    Holistic(const Holistic& h) {

        // Facemesh
        HasFacemesh = h.HasFacemesh;
        for (int i=0; i < FACEMESH_LANDMARK_NUM; i++) {
            for (int j=0; j < DIMENSIONS; j++) {
                facemesh[i][j] = h.facemesh[i][j];
            }
        }

        // Pose
        HasPose = h.HasPose;
        for (int i=0; i < POSE_LANDMARK_NUM; i++) {
            for (int j=0; j < DIMENSIONS; j++) {
                pose[i][j] = h.pose[i][j];
            }
        }

        // Hands
        HasLeftHand = h.HasLeftHand;
        HasRightHand = h.HasRightHand;
        for (int i=0; i < HAND_LANDMARK_NUM; i++) {
            for (int j=0; j < DIMENSIONS; j++) {
                LeftHand[i][j] = h.LeftHand[i][j];
                RightHand[i][j] = h.RightHand[i][j];
            }
        }

        // Component is stable or not
        mIsHeadStable = h.mIsHeadStable; 
        mIsLeftHandStable = h.mIsLeftHandStable; 
        mIsRightHandStable = h.mIsRightHandStable; 

    }

private:

    static constexpr int mIWrist = 0;
    static constexpr int mIThumb01 = 1;
    static constexpr int mIThumb02 = 2;
    static constexpr int mIThumb03 = 3;
    static constexpr int mIThumb04 = 4;
    static constexpr int mIIndex01 = 5;
    static constexpr int mIIndex02 = 6;
    static constexpr int mIIndex03 = 7;
    static constexpr int mIIndex04 = 8;
    static constexpr int mIMiddle01 = 9;
    static constexpr int mIMiddle02 = 10;
    static constexpr int mIMiddle03 = 11;
    static constexpr int mIMiddle04 = 12;
    static constexpr int mIRing01 = 13;
    static constexpr int mIRing02 = 14;
    static constexpr int mIRing03 = 15;
    static constexpr int mIRing04 = 16;
    static constexpr int mIPinky01 = 17;
    static constexpr int mIPinky02 = 18;
    static constexpr int mIPinky03 = 19;
    static constexpr int mIPinky04 = 20;

    // Component is stable or not
    bool mIsHeadStable = true;
    bool mIsLeftHandStable = true;
    bool mIsRightHandStable = true;

};

#endif // HOLISTIC_H