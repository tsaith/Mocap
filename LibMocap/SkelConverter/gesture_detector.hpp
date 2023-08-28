#ifndef GESTURE_DETECTOR_H
#define GESTURE_DETECTOR_H 

#define LC_MODIFY_GESTURE
#if defined (LC_MODIFY_GESTURE)
    #define SetNumRecogStaticGesture 5 // static gesture voting: amount of gesture for voting
    #define SetDurRecogStaticGesture 2 // static gesture voting: recog. duration
    #define NumClassStGesture 14 // =eStGesture_Str.size()
#endif

namespace gd {

    #include <iostream>
    #include <string>
    #include <vector>
    #include <cmath>
    //#include <Eigen/Dense>

    using namespace std;
    //using namespace Eigen;
        
    class GestureDetector {
    public:
        GestureDetector() {
            SetZeros(mRefPoint);
            SetZeros(mRefPointPrev);
                
        #if defined (LC_MODIFY_GESTURE)
            mRecogStaticGestureIdx = 0;
            mCntDurRecogStaticGesture = 0;
            
            for (int i = 0; i < SetNumRecogStaticGesture; i ++) {
                mArrRecogStaticGestureIdx[i] = 0;
            }
            
            for (int i = 0; i < 2; i ++) {
                for (int j = 0; j < eStGesture_Str.size(); j ++) {
                    mArrCntRecogStaticGestureIdx[i][j] = 0;
                }
            }
        #endif

        }

        ~GestureDetector() {}

        float GetNorm(float* v) {
            float norm;
            norm = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

            return norm;
        }

        float InnerProduct(float* a, float* b) {
            return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
        }

        void VecAssign(float* des, float* src) {
            for (int i=0; i < 3; i++) {
                des[i] = src[i];
            }    
        }

        float GetAngleFrom(float* p0, float* p1, float* p2) {
            float v1[3], v2[3];
            for (int i=0; i < 3; i++) {
                v1[i] = p0[i] - p1[i]; 
                v2[i] = p2[i] - p1[i]; 
            }
    
            float v1u[3], v2u[3];
            float v1Norm = GetNorm(v1);
            float v2Norm = GetNorm(v2);

            for (int i=0; i < 3; i++) {
                v1u[i] = v1[i] / v1Norm;
                v2u[i] = v2[i] / v2Norm;
            }    
    
            float dot = InnerProduct(v1u, v2u);
            if (dot < -1.0) dot = -1.0; 
            if (dot > 1.0) dot = 1.0; 

            float angle = acos(dot);

            return angle;
        }
    
        bool IsBent(float angle, float AngleC) {
            bool result = false;
            if (angle < AngleC) {
                result = true;
            }

            return result;
        }

        float GetLength(float* a, float* b) {
            float dx = a[0]-b[0];
            float dy = a[1]-b[1];
            float dz = a[2]-b[2];

            return sqrt(dx*dx+dy*dy+dz*dz);
        }

        bool IsTwoPointsClose(float* a, float* b, float dc) {
            float d = GetLength(a, b);
            bool IsClose = false;
            if (d < dc) IsClose = true;

            return IsClose;
        }

        void SetZeros(float* p) {
            for (int i=0; i < 3; i++) {
                p[i] = 0.0;
            }
        }

        void CopyPoint(float* dest, float* src) {
            for (int i=0; i < 3; i++) {
                dest[i] = src[i];
            }
        }

    #if defined (LC_MODIFY_GESTURE)
        float GetAngleFrom_ProjectionPt(float* p0, float* p1, float* p2, float* proj) {
            // ref 1. https://math.libretexts.org/Bookshelves/Differential_Equations/Book%3A_Differential_Equations_for_Engineers_(Lebl)/Appendix_A%3A_Linear_Algebra/A.5%3A_Inner_Product_and_Projections
            // ref 2. https://web.ntnu.edu.tw/~algo/Point.html
            float v1[3], v2[3];
            for (int i=0; i < 3; i++) {
                v1[i] = p0[i] - p1[i]; 
                v2[i] = p2[i] - p1[i]; 
            }
    
            float v1u[3], v2u[3];
            float v1Norm = GetNorm(v1);
            float v2Norm = GetNorm(v2);

            for (int i=0; i < 3; i++) {
                v1u[i] = v1[i] / v1Norm;
                v2u[i] = v2[i] / v2Norm;
            }    
    
            float dot = InnerProduct(v1u, v2u);
            if (dot < -1.0) dot = -1.0; 
            if (dot > 1.0) dot = 1.0; 

            float angle = acos(dot);
            
            // [lc add start]
            for (int i=0; i < 3; i++) {
                //proj[i] = (dot*pow(v1Norm,2))*v2[i] + p1[i];
                //proj[i] = (dot*InnerProduct(v1, v1))*v2[i] + p1[i];
                proj[i] = (dot*v1Norm/v2Norm)*v2[i] + p1[i];
            }
            //cout << "A0:" << proj[0] << ", " << proj[1] << ", " << proj[2] << endl;
            // [lc add end]

            return angle;
        }
        
        int FindIntArrayMaxLexsort (int a[2][NumClassStGesture]) {
            int max = 0;
            int idx = 0;
            //for (int i = 0; i < _msize(*a)/sizeof(int); i ++) {
            for (int i = 0; i < NumClassStGesture; i ++) {
                if (a[0][i] > max) {
                    max = a[0][i];
                    idx = i;
                } else if (a[0][i] == max) {
                    //cout << "eq0, "<< i << ", " << a[1][i] << ", " << a[1][idx]  << endl;
                    if (a[1][i] > a[1][idx]) {
                        //cout << "eq1, " << idx;
                        idx = i; //a[1][i];
                        //cout << ", " << idx << endl;
                    }
                }
            }

            return idx;
        }
    #endif

    #if defined (LC_MODIFY_GESTURE)
        void Detect(float hand[21][4], bool HasHand) {
    #else
        void Detect(float hand[21][4]) {
    #endif
            mWrist = hand[0];
            mThumbCMC = hand[1];
            mThumbMCP = hand[2];
            mThumbIP = hand[3];
            mThumbTIP = hand[4];
            mIndexFingerMCP = hand[5];
            mIndexFingerPIP = hand[6];
            mIndexFingerDIP = hand[7];
            mIndexFingerTIP = hand[8];
            mMiddleFingerMCP = hand[9];
            mMiddleFingerPIP = hand[10];
            mMiddleFingerDIP = hand[11];
            mMiddleFingerTIP = hand[12];
            mRingFingerMCP = hand[13];
            mRingFingerPIP = hand[14];
            mRingFingerDIP = hand[15];
            mRingFingerTIP = hand[16];
            mPinkyFingerMCP = hand[17];
            mPinkyFingerPIP = hand[18];
            mPinkyFingerDIP = hand[19];
            mPinkyFingerTIP = hand[20];

            // Characteristic length
            mLenC = GetLength(mIndexFingerMCP, mWrist);
            
        #if defined (LC_MODIFY_GESTURE)
            // New Gestures
            mStaticGestureIdxPerFrame = DetectStaticGesture();

            // drop oldest gesture
            for (int i = 0; i < SetNumRecogStaticGesture - 1; i ++) {
                mArrRecogStaticGestureIdx[i] = mArrRecogStaticGestureIdx[i+1];
            }
            if (!HasHand) {
                mArrRecogStaticGestureIdx[SetNumRecogStaticGesture - 1] = 0;
            } else {
                // receive new gesture
                mArrRecogStaticGestureIdx[SetNumRecogStaticGesture - 1]
                    = mStaticGestureIdxPerFrame;
            }
            // recognize while reaching SetDurRecogStaticGesture
            if (mCntDurRecogStaticGesture == SetDurRecogStaticGesture - 1) {                
                for (int i = 0; i < eStGesture_Str.size(); i ++) {
                    mArrCntRecogStaticGestureIdx[0][i] = 0;
                    mArrCntRecogStaticGestureIdx[1][i] = 0;
                }

                for (int i = 0; i < SetNumRecogStaticGesture; i ++) {
                    mRecogStaticGestureIdx = mArrRecogStaticGestureIdx[i];
                    mArrCntRecogStaticGestureIdx[0][mRecogStaticGestureIdx] ++;
                    mArrCntRecogStaticGestureIdx[1][mRecogStaticGestureIdx] = i;
                }

                // Gestures
                mStaticGestureIdx 
                    = FindIntArrayMaxLexsort (mArrCntRecogStaticGestureIdx);
                mStaticGesture = eStGesture_Str[mStaticGestureIdx];
                mCntDurRecogStaticGesture = 0;

                /*for (int i = 0; i < SetNumRecogStaticGesture; i ++) {
                    cout << ", " << ArrRecogLeftStaticGestureIdx[i];
                }
                cout << "; ";
                for (int i = 0; i < eStGesture_Str.size(); i ++) {
                    cout << ", " << ArrCntRecogLeftStaticGestureIdx[0][i];
                }   
                cout << "; ";
                for (int i = 0; i < eStGesture_Str.size(); i ++) {
                    cout << ", " << ArrCntRecogLeftStaticGestureIdx[1][i];
                } 
                cout << "; " << FinalRecogLeftStaticGestureIdx << endl;*/ 
            } else {
                mCntDurRecogStaticGesture ++;
            }
        #else
            // Gestures 
            mStaticGestureIdx = DetectStaticGesture();
            mStaticGesture = eStGesture_Str[mStaticGestureIdx];
        #endif
            
            mDynamicGestureIdx = DetectDynamicGesture();
            mDynamicGesture = eDyGesture_Str[mDynamicGestureIdx];
        }
 

        int DetectStaticGesture() {
            /*
            Return the gesture detected.

            '': No gesture.
            'fist': Fist.
            'pinch_index': Pinch index.
            'pinch_middle': Pinch middle.
            'good': Good.
            */

            float ThumbAngleC = 0.9*M_PI;
            float AngleC = 0.8*M_PI;

            float ThumbAngle = GetAngleFrom(mThumbIP, mThumbMCP, mThumbCMC);
            float IndexAngle = GetAngleFrom(mIndexFingerDIP, mIndexFingerPIP, mIndexFingerMCP);
            float MiddleAngle = GetAngleFrom(mMiddleFingerDIP, mMiddleFingerPIP, mMiddleFingerMCP);
            float RingAngle = GetAngleFrom(mRingFingerDIP, mRingFingerPIP, mRingFingerMCP);
            float PinkyAngle = GetAngleFrom(mPinkyFingerDIP, mPinkyFingerPIP, mPinkyFingerMCP);

            bool IsThumbBent = IsBent(ThumbAngle, ThumbAngleC);
            bool IsIndexBent = IsBent(IndexAngle, AngleC);
            bool IsMiddleBent = IsBent(MiddleAngle, AngleC);
            bool IsRingBent = IsBent(RingAngle, AngleC);
            bool IsPinkyBent = IsBent(PinkyAngle, AngleC);

            float* wrist = mWrist;  
            float* ThumbTIP = mThumbTIP;  
            float* IndexTIP = mIndexFingerTIP;  
            float* MiddleTIP = mMiddleFingerTIP;  
            float* RingTIP = mRingFingerTIP;  
            float* PinkyTIP = mPinkyFingerTIP;  

        #if defined (LC_MODIFY_GESTURE)
            //float dc = 0.25*mLenC;
            //float* ProjThumbTIP;
            float ProjThumbTIP[3];
            for (int i=0; i < 3; i++) {
                ProjThumbTIP[i] = 0;
            }
            float ThumbTipAngle = GetAngleFrom_ProjectionPt(mThumbTIP, mThumbIP, mThumbMCP, ProjThumbTIP); // (kp4, kp3, kp2) => v1=kp4-kp3, v2=kp2-kp3
            bool IsThumbTipBent = IsBent(ThumbTipAngle, ThumbAngleC);
            //GetProjectionPt(mThumbTIP, mThumbIP, mThumbMCP, ProjThumbTIP);
            float LenProjThumbTIP2Kp17 = GetLength(ProjThumbTIP, mPinkyFingerMCP);
            bool IsThumbTIPCloseKp17 = IsTwoPointsClose(mThumbTIP, mPinkyFingerMCP, LenProjThumbTIP2Kp17);
            
            float IndexMCPAngle = GetAngleFrom(mIndexFingerPIP, mIndexFingerMCP, mWrist);
            float MiddleMCPAngle = GetAngleFrom(mMiddleFingerPIP, mMiddleFingerMCP, mWrist);
            float RingMCPAngle = GetAngleFrom(mRingFingerPIP, mRingFingerMCP, mWrist);
            float PinkyMCPAngle = GetAngleFrom(mPinkyFingerPIP, mPinkyFingerMCP, mWrist);
            bool IsIndexMCPBent = IsBent(IndexMCPAngle, AngleC);
            bool IsMiddleMCPBent = IsBent(MiddleMCPAngle, AngleC);
            bool IsRingMCPBent = IsBent(RingMCPAngle, AngleC);
            bool IsPinkyMCPBent = IsBent(PinkyMCPAngle, AngleC);

            float dc0 = 0.45*mLenC;
            float dc1 = 0.4*mLenC;
            bool IsIndexThumbClose = IsTwoPointsClose(IndexTIP, ThumbTIP, dc0);
            bool IsMiddleThumbClose = IsTwoPointsClose(MiddleTIP, ThumbTIP, dc1);
        #else
            float dc = 0.25*mLenC;
            bool IsIndexThumbClose = IsTwoPointsClose(IndexTIP, ThumbTIP, dc);
            bool IsMiddleThumbClose = IsTwoPointsClose(MiddleTIP, ThumbTIP, dc);
        #endif

            //string gesture = "";
            int gesture_idx = (int)eStGesture::None;

        #if defined (LC_MODIFY_GESTURE)
            // Numeric gestures
            if ( ( (IsThumbTipBent || IsThumbBent) && IsThumbTIPCloseKp17) && !IsIndexBent &&
            //if (   (IsThumbTipBent || IsThumbBent)                         && !IsIndexBent &&
                IsMiddleBent && IsRingBent && IsPinkyBent) {

                    gesture_idx = (int)eStGesture::Number1;
                    return gesture_idx;
            }

            if ( ( (IsThumbTipBent || IsThumbBent) && IsThumbTIPCloseKp17) && !IsIndexBent &&
            //if (   (IsThumbTipBent || IsThumbBent)                         && !IsIndexBent &&
                !IsMiddleBent && IsRingBent && IsPinkyBent) {

                    gesture_idx = (int)eStGesture::Number2;
                    return gesture_idx;
            }

            if ( ( (IsThumbTipBent || IsThumbBent) && IsThumbTIPCloseKp17) && !IsIndexBent &&
            //if (   (IsThumbTipBent || IsThumbBent)                         && !IsIndexBent &&
                !IsMiddleBent && !IsRingBent && IsPinkyBent) {

                    gesture_idx = (int)eStGesture::Number3;
                    return gesture_idx;
            }

            /*if ( ( (IsThumbTipBent || IsThumbBent) && IsThumbTIPCloseKp17) && !IsIndexBent &&
            //if (   (IsThumbTipBent || IsThumbBent)                         && !IsIndexBent &&
                !IsMiddleBent && !IsRingBent && !IsPinkyBent) {*/
            if ( ( (IsThumbTipBent || IsThumbBent) && IsThumbTIPCloseKp17)
                && !(IsIndexBent || IsIndexMCPBent)
                && !(IsMiddleBent || IsMiddleMCPBent)
                && !(IsRingBent || IsRingMCPBent)
                && !(IsPinkyBent  || IsPinkyMCPBent) ) {

                    gesture_idx = (int)eStGesture::Number4;
                    return gesture_idx;
            }

            //if (!IsThumbBent && !IsIndexBent &&
            //    !IsMiddleBent && !IsRingBent && !IsPinkyBent) {
            //if (   !IsThumbBent
            if (   !IsThumbTIPCloseKp17
                && !(IsIndexBent || IsIndexMCPBent)
                && !(IsMiddleBent || IsMiddleMCPBent)
                && !(IsRingBent || IsRingMCPBent)
                && !(IsPinkyBent  || IsPinkyMCPBent) ) {
                
                    gesture_idx = (int)eStGesture::Number5;
                    return gesture_idx;
            }

            if (!IsThumbBent && IsIndexBent &&
                IsMiddleBent && IsRingBent && !IsPinkyBent) {
                
                    gesture_idx = (int)eStGesture::Number6;
                    return gesture_idx;
            }

            /*//if ( ( (!IsThumbTIPCloseKp17) && (!IsThumbBent) ) && !IsIndexBent &&
            //if ( ( (!IsThumbTipBent) && (!IsThumbBent) ) && !IsIndexBent &&
            if (!IsThumbBent && !IsIndexBent &&
                IsMiddleBent && IsRingBent && IsPinkyBent) {*/
            if (   !IsThumbBent
                && !(IsIndexBent || IsIndexMCPBent)
                && IsMiddleBent && IsRingBent && IsPinkyBent) {
                
                    gesture_idx = (int)eStGesture::Number7;
                    return gesture_idx;
            }

            /*//if ( ( (!IsThumbTIPCloseKp17) && (!IsThumbBent) ) && !IsIndexBent &&
            //if ( ( (!IsThumbTipBent) && (!IsThumbBent) ) && !IsIndexBent &&
            if (!IsThumbBent && !IsIndexBent &&
                !IsMiddleBent && IsRingBent && IsPinkyBent) {*/
            if (   !IsThumbBent 
                && !(IsIndexBent || IsIndexMCPBent)
                && !(IsMiddleBent || IsMiddleMCPBent)
                && IsRingBent && IsPinkyBent) {
                
                    gesture_idx = (int)eStGesture::Number8;
                    return gesture_idx;
            }

            //if ( ( (!IsThumbTIPCloseKp17) && (!IsThumbBent) ) && !IsIndexBent &&
            //if ( ( (!IsThumbTipBent) && (!IsThumbBent) ) && !IsIndexBent &&
            if (!IsThumbBent && !IsIndexBent &&
                !IsMiddleBent && !IsRingBent && IsPinkyBent) {
                
                    gesture_idx = (int)eStGesture::Number9;
                    return gesture_idx;
            }
            
            // General gestures
            //if (IsThumbBent && IsIndexBent &&
            if ( ( (IsThumbTipBent || IsThumbBent) && IsThumbTIPCloseKp17) && IsIndexBent &&
            //if (   (IsThumbTipBent || IsThumbBent)                         && IsIndexBent &&
                IsMiddleBent && IsRingBent && IsPinkyBent) {

                    gesture_idx = (int)eStGesture::Number0;
                    return gesture_idx;
            }

            /*//if (!IsThumbBent && IsIndexBent &&
            if (IsIndexBent &&
                IsMiddleBent && IsRingBent && IsPinkyBent) {*/
            if (   (IsIndexBent || IsIndexMCPBent)
                && (IsMiddleBent || IsMiddleMCPBent)
                && (IsRingBent || IsRingMCPBent)
                && (IsPinkyBent  || IsPinkyMCPBent) ) {

                if (!IsIndexThumbClose) {
                    gesture_idx = (int)eStGesture::Good;
                }
                return gesture_idx;
            }
        #else
            // Numeric gestures
            if (IsThumbBent && !IsIndexBent &&
                IsMiddleBent && IsRingBent && IsPinkyBent) {

                    gesture_idx = (int)eStGesture::Number1;
                    return gesture_idx;
            }

            if (IsThumbBent && !IsIndexBent &&
                !IsMiddleBent && IsRingBent && IsPinkyBent) {

                    gesture_idx = (int)eStGesture::Number2;
                    return gesture_idx;
            }

            if (IsThumbBent && !IsIndexBent &&
                !IsMiddleBent && !IsRingBent && IsPinkyBent) {

                    gesture_idx = (int)eStGesture::Number3;
                    return gesture_idx;
            }

            if (IsThumbBent && !IsIndexBent &&
                !IsMiddleBent && !IsRingBent && !IsPinkyBent) {

                    gesture_idx = (int)eStGesture::Number4;
                    return gesture_idx;
            }


            if (!IsThumbBent && !IsIndexBent &&
                !IsMiddleBent && !IsRingBent && !IsPinkyBent) {
                
                    gesture_idx = (int)eStGesture::Number5;
                    return gesture_idx;
            }


            // General gestures
            if (IsThumbBent && IsIndexBent &&
                IsMiddleBent && IsRingBent && IsPinkyBent) {

                    gesture_idx = (int)eStGesture::Number0;
                    return gesture_idx;
            }

            if (!IsThumbBent && IsIndexBent &&
                IsMiddleBent && IsRingBent && IsPinkyBent) {

                if (!IsIndexThumbClose) {
                    gesture_idx = (int)eStGesture::Good;
                }
                return gesture_idx;
            }
        #endif

            if (!IsMiddleBent && !IsRingBent && !IsPinkyBent) {

                if (IsIndexThumbClose) {
                    gesture_idx = (int)eStGesture::Pinch_index;
                }
                return gesture_idx;
            }

            if (!IsIndexBent && !IsRingBent && !IsPinkyBent) {

                if (IsMiddleThumbClose) {
                    gesture_idx = (int)eStGesture::Pinch_middle;
                }
                return gesture_idx;
            }

            
            return gesture_idx;

        }

        int DetectDynamicGesture() {
            float dc = 1.5*mLenC;

            // Set reference point
            CopyPoint(mRefPoint, mIndexFingerMCP);

            float dx = mRefPoint[0] - mRefPointPrev[0];
            float dy = mRefPoint[1] - mRefPointPrev[1];
            float dz = mRefPoint[2] - mRefPointPrev[2];

            float distance = GetLength(mRefPoint, mRefPointPrev);
            float AbsDx = abs(dx);
            float AbsDy = abs(dy);

            int gesture_idx = (int)eDyGesture::None;

            if (distance > dc) {
                if (AbsDx > AbsDy) {
                    if (dx > 0) {
                        gesture_idx =  (int)eDyGesture::MoveLeft;
                    } else {
                        gesture_idx = (int)eDyGesture::MoveRight;
                    }
                } else {
                    if (dy > 0) {
                        gesture_idx = (int)eDyGesture::MoveDown;
                    } else {
                        gesture_idx = (int)eDyGesture::MoveUp;
                    }    
                }    
            }

            // Save point
            CopyPoint(mRefPointPrev, mRefPoint);

            return gesture_idx;
        }

        int GetStaticGestureIndex() { return mStaticGestureIdx; };
        string GetStaticGesture() { return mStaticGesture; };
        int GetDynamicGestureIndex() { return mDynamicGestureIdx; };
        string GetDynamicGesture() { return mDynamicGesture; };

    private:
    
        string mStaticGesture = "";
        string mDynamicGesture = "";
        int mStaticGestureIdx;
        int mDynamicGestureIdx;

        // Hand components 
        float *mWrist;
        float *mThumbCMC;
        float *mThumbMCP;
        float *mThumbIP;
        float *mThumbTIP;
        float *mIndexFingerMCP;
        float *mIndexFingerPIP;
        float *mIndexFingerDIP;
        float *mIndexFingerTIP;
        float *mMiddleFingerMCP;
        float *mMiddleFingerPIP;
        float *mMiddleFingerDIP;
        float *mMiddleFingerTIP;
        float *mRingFingerMCP;
        float *mRingFingerPIP;
        float *mRingFingerDIP;
        float *mRingFingerTIP;
        float *mPinkyFingerMCP;
        float *mPinkyFingerPIP;
        float *mPinkyFingerDIP;
        float *mPinkyFingerTIP;

        // Characteristic length
        float mLenC;

        // Reference point
        float mRefPoint[3];
        float mRefPointPrev[3];

        // Static Gesture enum
        enum class eStGesture {
            None,
            Number1,
            Number2,
            Number3,
            Number4,
            Number5,
            Number6,
            Number7,
            Number8,
            Number9,
            Number0,
            Good,
            Pinch_index,
            Pinch_middle
        };

        vector<string> eStGesture_Str = {
            "None", "Number1", "Number2", "Number3", "Number4",
            "Number5", "Number6", "Number7", "Number8", "Number9",
            "Number0", "Good", "Pinch_index", "Pinch_middle"
        };

        // Dynamic Gesture enum
        enum class eDyGesture {
            None,
            MoveUp,
            MoveDown,
            MoveLeft,
            MoveRight
        };

        vector<string> eDyGesture_Str = {
            "None", "MoveUp", "MoveDown", "MoveLeft", "MoveRight"
        };
        
    #if defined (LC_MODIFY_GESTURE)
        int mRecogStaticGestureIdx;
        int mCntDurRecogStaticGesture;
        int mArrRecogStaticGestureIdx[SetNumRecogStaticGesture];
        int mArrCntRecogStaticGestureIdx[2][NumClassStGesture];
        int mStaticGestureIdxPerFrame;
    #endif

    };


}; 

#endif