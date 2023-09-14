#include "pch.h"

#include "pose_utils.h"


    template<typename T>
    void Interp1d(T A, T B, T Weight, T& Target) {
        /*
        Perform 1d interpolation.
        Target: Target point which is determined by interpolation.
        A: Point A.
        B: Point B.
        Weight: Weighting factor defined as Len(TA)/Len(AB), where T stands for Target.
        */

        float WeightA = Weight;
        float WeightB = 1.0 - WeightA;

        Target = A * WeightB + B * WeightA;

    }

    template<typename T>
    void Interp2d(T* A, T* B, T Weight, T* Target) {
        /*
        Perform 2d interpolation.
        Target: Target point which is determined by interpolation.
        A: Point A.
        B: Point B.
        Weight: Weighting factor defined as Len(TA)/Len(AB), where T stands for Target.
        */

        for (int i = 0; i < 2; i++) {
            Interp1d(A[i], B[i], Weight, Target[i]);
        }

    }

    template<typename T>
    void Interp3d(T* A, T* B, T Weight, T* Target) {
        /*
        Perform 3d interpolation.
        Target: Target point which is determined by interpolation.
        A: Point A.
        B: Point B.
        Weight: Weighting factor defined as Len(TA)/Len(AB), where T stands for Target.
        */

        for (int i = 0; i < 3; i++) {
            Interp1d(A[i], B[i], Weight, Target[i]);
        }

    }

    template<typename T>
    void Mean2d(T* A, T* B, T* Target) {
        T weight = 0.5;
        Interp2d(A, B, weight, Target);
    }

    template<typename T>
    void Mean3d(T* A, T* B, T* Target) {
        T weight = 0.5;
        Interp3d(A, B, weight, Target);
    }

    template<typename T>
    void ArrToVec(T* A, vector<T>& V, int Dims) {

        for (int i = 0; i < Dims; i++) {
            V[i] = A[i];
        }

    }

    template<typename T>
    void VecToArr(vector<T>& V, T* A, int Dims) {

        for (int i = 0; i < Dims; i++) {
            A[i] = V[i];
        }

    }


    // Pose related functions
    vector<vector<float>> CreateVectorPoseMp(float* Ptr, int NumJoints, int Dims) {

        const int dimsOut = 3;
        vector<vector<float>> pose(NumJoints, vector<float>(Dims, 0.0));
        //vector<vector<float>> pose(NumJoints, vector<float> (dimsOut, 0.0));

        for (int i = 0; i < NumJoints; i++) {
            for (int j = 0; j < Dims; j++) {

                pose[i][j] = *(Ptr + i * Dims + j);

            }
        }

        return pose;

    }

    vector<vector<float>> ToPixelSpace(vector<vector<float>>& PoseIn, int Width) {

        vector<vector<float>> pose = PoseIn;

        int numJoints = static_cast<int>(pose.size());
        int dims = 3;

        for (int i = 0; i < numJoints; i++) {
            pose[i][0] *= Width;
            pose[i][1] *= Width;
            //pose[i][1] *= Height;
            pose[i][2] *= Width;
        }

        return pose;

    }

    vector<vector<float>> InitPose2d() {

        int numJoints = 17;
        int dims = 2;
        vector<vector<float>> pose(numJoints, vector<float>(dims, 0.0));

        return pose;
    }

    void ConvertPoseMpToPose2d(vector<vector<float>>& PoseMp, vector<vector<float>>& Pose2d) {

        const int num = 17;
        const int dims = 2;
        vector<vector<float>> pose(num, vector<float>(dims, 0.0));

        float leftEar[dims], rightEar[dims], head[dims];
        float leftShoulder[dims], rightShoulder[dims], shoulderCenter[dims];
        float leftHip[dims], rightHip[dims], hipCenter[dims];
        float spine[dims], thorax[dims], neck[dims], headTop[dims];

        // Head
        VecToArr(PoseMp[7], leftEar, 2);
        VecToArr(PoseMp[8], rightEar, 2);
        Mean2d(leftEar, rightEar, head);

        // Shoulder center
        VecToArr(PoseMp[11], leftShoulder, 2);
        VecToArr(PoseMp[12], rightShoulder, 2);
        Mean2d(leftShoulder, rightShoulder, shoulderCenter);

        // Hip center
        VecToArr(PoseMp[23], leftHip, 2);
        VecToArr(PoseMp[24], rightHip, 2);
        Mean2d(leftHip, rightHip, hipCenter);

        // Pelvis
        ArrToVec(hipCenter, Pose2d[0], 2);

        // Right hip
        ArrToVec(rightHip, Pose2d[1], 2);

        // Right knee
        Pose2d[2] = PoseMp[26];

        // Right ankle
        Pose2d[3] = PoseMp[28];

        // Left hip
        Pose2d[4] = PoseMp[23];

        // Left knee
        Pose2d[5] = PoseMp[25];

        // Left ankle
        Pose2d[6] = PoseMp[27];

        // Spine
        Mean2d(hipCenter, shoulderCenter, spine);
        ArrToVec(spine, Pose2d[7], 2);

        // Thorax
        thorax[0] = shoulderCenter[0];
        thorax[1] = shoulderCenter[1];
        ArrToVec(thorax, Pose2d[8], 2);

        // Neck
        Interp2d(shoulderCenter, head, float(0.7), neck);
        ArrToVec(neck, Pose2d[9], 2);

        // Head top
        headTop[0] = head[0];
        headTop[1] = head[1];
        ArrToVec(headTop, Pose2d[10], 2);

        // Left shoulder
        ArrToVec(leftShoulder, Pose2d[11], 2);

        // Left elbow
        Pose2d[12] = PoseMp[13];

        // Left wrist
        Pose2d[13] = PoseMp[15];

        // Right shoulder
        Pose2d[14] = PoseMp[12];

        // Right elbow
        Pose2d[15] = PoseMp[14];

        // Right wrist
        Pose2d[16] = PoseMp[16];

    }


    void PrintPoint(string Msg, vector<float>& Point, int Dims) {

        string outMsg = "";
        outMsg += Msg;
        outMsg += ": ";
        for (int i = 0; i < Dims; i++) {
            outMsg += "[" + std::to_string(Point[i]) + "]";
        }

        cout << outMsg << endl;

    }
