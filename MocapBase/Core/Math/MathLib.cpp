#include "pch.h"

#include "MathLib.h"

namespace zen_math {

    float RadianToDegree(float radian) {
        return radian / M_PI * 180.0;
    }

    float DegreeToRadian(float degree) {
        return degree / 180.0 * M_PI;
    }


    float CalculateVecNorm(std::vector<float>& Vec)
    {
        int dims = Vec.size();

        float out = 0.f;
        for (int i = 0; i < dims; i++) {
            out += Vec[i] * Vec[i];
        }
        out = sqrt(out);

        return out;
    }

    vector<float> CalculateVecTwoPoints(vector<float>& Point1, vector<float>& Point2)
    {
        int dims = Point1.size();

        vector<float> vec;
        for (int i = 0; i < dims; i++) {
            vec.push_back(Point2[i] - Point1[i]);
        }

        return vec;
    }

    float CalculateLengthTwoPoints(std::vector<float>& Point1, std::vector<float>& Point2)
    {
        vector<float> vec = CalculateVecTwoPoints(Point1, Point2);
        return CalculateVecNorm(vec);
    }


    vector<float> CalculateUnitVecTwoPoints(vector<float>& Point1, std::vector<float>& Point2)
    {
        vector<float> vec = CalculateVecTwoPoints(Point1, Point2);
        float length = CalculateVecNorm(vec);

        vector<float> unitVec;
        int dims = vec.size();
        for (int i = 0; i < dims; i++) {
            unitVec.push_back(vec[i] / length);
        }

        return unitVec;
    }


    // ---------------------------------------------
    void VecSet(float* vec, float x, float y, float z) {

        vec[0] = x;
        vec[1] = y;
        vec[2] = z;

    }

    void VecCopy(float* dest, float* src) {

        for (int i = 0; i < 3; i++) {
            dest[i] = src[i];
        }

    };

    void VecCopy(float* dest, float* src, int dims) {

        for (int i = 0; i < dims; i++) {
            dest[i] = src[i];
        }

    };

    template <typename T>
    void VecCopy(T* dest, T* src) {
        std::copy(std::begin(src), std::end(src), std::begin(dest));
    };

    void VecNorm(float& result, float* vec) {

        result = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

    }

    void NormalizeVec(float* dest, float* src) {

        float norm;
        VecNorm(norm, src);

        float v0 = src[0] / norm;
        float v1 = src[1] / norm;
        float v2 = src[2] / norm;

        VecSet(dest, v0, v1, v2);

    }

    void VecAdd(float* vec, float* a, float* b) {

        for (int i = 0; i < 3; i++) {
            vec[i] = a[i] + b[i];
        }

    }

    void VecSubstract(float* vec, float* a, float* b) {

        for (int i = 0; i < 3; i++) {
            vec[i] = a[i] - b[i];
        }

    }

    void VecSubstractNorm(float* vec, float* a, float* b) {

        VecSubstract(vec, a, b);
        float norm;
        VecNorm(norm, vec);
        VecDivide(vec, vec, norm);

    }

    void VecMultiply(float* vec, float* a, float fac) {

        for (int i = 0; i < 3; i++) {
            vec[i] = a[i] * fac;
        }

    }

    void VecDivide(float* vec, float* a, float denominator) {

        for (int i = 0; i < 3; i++) {
            vec[i] = a[i] / denominator;
        }

    }

    void VecInverse(float* vec, float* vecRef) {

        for (int i = 0; i < 3; i++) {
            vec[i] = -vecRef[i];
        }

    }

    void VecMean(float* vec, float* a, float* b) {

        for (int i = 0; i < 3; i++) {
            vec[i] = 0.5 * (a[i] + b[i]);
        }

    }


    void InterpPoint(float* target, float* a, float* b, float weight) {
        /*
        Vector interpolation.
        target: Target point which is determined by interpolation.
        a: Vector A.
        b: Vector B.
        weight: Weighting factor defined as Len(TA)/Len(AB), where T stands for Target.
        */

        float weightA = weight;
        float weightB = 1.0 - weightA;

        for (int i = 0; i < 3; i++) {
            target[i] = a[i] * weightB + b[i] * weightA;
        }

    }

    void VecDot(float& result, float* a, float* b) {

        result = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];

    }

    void VecCross(float* vec, float* a, float* b) {

        vec[0] = a[1] * b[2] - a[2] * b[1];
        vec[1] = a[2] * b[0] - a[0] * b[2];
        vec[2] = a[0] * b[1] - a[1] * b[0];

    }

    void VecCrossNorm(float* vec, float* a, float* b) {

        float norm;

        VecCross(vec, a, b);
        VecNorm(norm, vec);
        VecDivide(vec, vec, norm);

    }

    void EstimateUnitVector(float* vec, float* target, float* base) {

        VecSubstract(vec, target, base);
        float norm;
        VecNorm(norm, vec);
        VecDivide(vec, vec, norm);

    }

    void EstimateUnitVector(float* vec, float* vecRef) {

        float norm;
        VecNorm(norm, vecRef);
        VecDivide(vec, vecRef, norm);

    }


    void EstimateProjectedVector(float* vec, float* vecA, float* vecB) {
        /*
        Project vecA onto vecB.
        vec: Projected vector.
        vecA: Vector A.
        vecB: Vector B.
        */

        float uVecB[3];
        float dotValue;

        EstimateUnitVector(uVecB, vecB);
        VecDot(dotValue, vecA, uVecB);
        VecMultiply(vec, uVecB, dotValue);

    }

    void EstimateVerticalVector(float* vec, float* vecA, float* vecB) {
        /*
        Estimate the component of vecA vertical to vecB.
        vec: Output vector.
        vecA: Vector A.
        vecB: Vector B.
        */

        float vecProjected[3];
        EstimateProjectedVector(vecProjected, vecA, vecB);
        VecSubstract(vec, vecA, vecProjected);

    }

    void EstimateIncludedAngle(float& angle, float* vecA, float* vecB) {

        float dotValue;
        VecDot(dotValue, vecA, vecB);

        float normA, normB;
        VecNorm(normA, vecA);
        VecNorm(normB, vecB);

        float denominator = normA * normB;
        angle = acos(dotValue / denominator);

    }


    void EstimateDistanceFromTwoPoints(float& distance, float* p1, float* p2) {

        float dx1 = p1[0] - p2[0];
        float dx2 = p1[1] - p2[1];
        float dx3 = p1[2] - p2[2];

        distance = sqrt(dx1 * dx1 + dx2 * dx2 + dx3 * dx3);

    };

    void EstimatePerpendicularDistanceFromTwoPoints(float& distance, float* p, float* a, float* b) {
        /*
        p: array
            Target point.
        a: array
            Point A.
        b: array
            Point B.
        */

        int i;
        float tmp;

        tmp = 0.0;
        for (i = 0; i < 3; i++) {
            tmp += (a[i] - b[i]) * (a[i] - p[i]);
        }

        float length;
        EstimateDistanceFromTwoPoints(length, a, b);
        float length2 = length * length;
        float alpha = tmp / length2;

        // Perpendicular point
        float c[3];
        for (i = 0; i < 3; i++) {
            c[i] = a[i] + alpha * (b[i] - a[i]);
        }

        // Distance
        EstimateDistanceFromTwoPoints(distance, c, p);

    }

    bool IsParallel(float* vecA, float* vecB, float angleTol) {

        float angle;
        EstimateIncludedAngle(angle, vecA, vecB);
        angle = abs(angle);

        bool bResult = false;
        if (angle < angleTol) bResult = true;

        return bResult;

    }

    bool IsAntiParallel(float* vecA, float* vecB, float angleTol) {

        float angle;
        EstimateIncludedAngle(angle, vecA, vecB);
        angle = abs(angle);

        bool bResult = false;
        if (abs(angle - M_PI) < angleTol) bResult = true;

        return bResult;

    }

    bool IsBetweenTwoValues(float v, float a, float b) {

        bool bResult = false;
        float lowerBound, upperBound;

        if (a < b) {
            lowerBound = a;
            upperBound = b;
        }
        else {
            lowerBound = b;
            upperBound = a;
        }

        if (v > lowerBound && v < upperBound) bResult = true;

        return bResult;

    }

    bool IsBetweenTwoPoints(float* p, float* a, float* b) {

        bool bResult = true;
        for (int i = 0; i < 3; i++) {
            if (IsBetweenTwoValues(p[i], a[i], b[i])) {
                bResult = false;
            }
        }

        return bResult;

    }

    void ToEigenVector(Eigen::Vector3d& dest, float* src) {

        for (int i = 0; i < 3; i++) {
            dest[i] = src[i];
        }

    }

    void ToEigenAngleAxis(Eigen::AngleAxisd& dest, float* src) {

        dest.angle() = src[0];
        dest.axis()[0] = src[1];
        dest.axis()[1] = src[2];
        dest.axis()[2] = src[3];

    }

    void ToEigenQuaternion(Eigen::Quaterniond& dest, float* src) {

        dest.w() = src[0];
        dest.x() = src[1];
        dest.y() = src[2];
        dest.z() = src[3];

    }

    void ToArrayVector(float* dest, Eigen::Vector3d& src) {

        for (int i = 0; i < 3; i++) {
            dest[i] = src[i];
        }

    }

    void ToArrayAngleAxis(float* dest, Eigen::AngleAxisd& src) {

        dest[0] = src.angle();
        dest[1] = src.axis()[0];
        dest[2] = src.axis()[1];
        dest[3] = src.axis()[2];

    }

    void ToArrayQuaternion(float* dest, Eigen::Quaterniond& src) {

        dest[0] = src.w();
        dest[1] = src.x();
        dest[2] = src.y();
        dest[3] = src.z();

    }

    Eigen::Quaterniond VecToQuat(Eigen::Vector3d v) {

        Eigen::Quaterniond q;
        q.w() = 0;
        q.vec() = v;

        return q;

    }

    Eigen::Vector3d QuatToVec(Eigen::Quaterniond q) {

        Eigen::Vector3d v;
        v = q.vec();

        return v;

    }

    /*
    Eigen::Vector3d QuatToEuler(Eigen::Quaterniond &q) {

        double roll, pitch, yaw;

        // roll (x-axis rotation)
        double sinr_cosp = +2.0 * (q.w() * q.x() + q.y() * q.z());
        double cosr_cosp = +1.0 - 2.0 * (q.x() * q.x() + q.y() * q.y());
        roll = atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        double sinp = +2.0 * (q.w() * q.y() - q.z() * q.x());
        if (fabs(sinp) >= 1) {
            pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        } else {
            pitch = asin(sinp);
        }

        // yaw (z-axis rotation)
        double siny_cosp = +2.0 * (q.w() * q.z() + q.x() * q.y());
        double cosy_cosp = +1.0 - 2.0 * (q.y() * q.y() + q.z() * q.z());
        yaw = atan2(siny_cosp, cosy_cosp);

        Eigen::Vector3d euler(roll, pitch, yaw);

        return euler;

    }
    */

    Eigen::Vector3d QuatToEuler(Eigen::Quaterniond& q, int i, int j, int k) {

        Eigen::Vector3d euler;
        euler = q.toRotationMatrix().eulerAngles(i, j, k);

        return euler;

    }

    Eigen::Quaterniond EulerToQuat(Eigen::Vector3d& ea) {

        Eigen::Matrix3d R;
        R = Eigen::AngleAxisd(ea[0], ::Eigen::Vector3d::UnitX()) *
            Eigen::AngleAxisd(ea[1], ::Eigen::Vector3d::UnitY()) *
            Eigen::AngleAxisd(ea[2], ::Eigen::Vector3d::UnitZ());
        Eigen::Quaterniond q;
        q = R;

        return q;

    }

    Eigen::Quaterniond EulerToQuat(Eigen::Vector3d& ea, int i, int j, int k) {

        auto getUnitAxis = [](int i) {

            Eigen::Vector3d unitAxis;

            switch (i) {
            case 0:
                unitAxis = Eigen::Vector3d::UnitX();
                break;
            case 1:
                unitAxis = Eigen::Vector3d::UnitY();
                break;
            case 2:
                unitAxis = Eigen::Vector3d::UnitZ();
                break;
            default:
                unitAxis = Eigen::Vector3d::UnitZ();
                break;
            }

            return unitAxis;

        };

        Eigen::Vector3d unitAlpha = getUnitAxis(i);
        Eigen::Vector3d unitBeta = getUnitAxis(j);
        Eigen::Vector3d unitGamma = getUnitAxis(k);

        Eigen::Matrix3d R;
        R = Eigen::AngleAxisd(ea[0], unitAlpha) *
            Eigen::AngleAxisd(ea[1], unitBeta) *
            Eigen::AngleAxisd(ea[2], unitGamma);
        Eigen::Quaterniond q;
        q = R;

        return q;

    }

    Eigen::AngleAxisd QuatToAngleAxis(Eigen::Quaterniond& q) {

        Eigen::AngleAxisd a(q);

        return a;

    }

    Eigen::Quaterniond AngleAxisToQuat(Eigen::AngleAxisd& a) {

        Eigen::Quaterniond q(a);

        return q;

    }

    Eigen::Vector3d RotateVec(Eigen::Vector3d v, Eigen::Quaterniond q) {
        /*
            v: Vector will be rotated.
            q: Quaternion which should be normalized.
        */

        Eigen::Quaterniond p = VecToQuat(v);
        //Eigen::Quaterniond rotatedP = q.inverse()*p*q; 
        Eigen::Quaterniond rotatedP = q * p * q.inverse();
        Eigen::Vector3d rotatedV = rotatedP.vec();

        return rotatedV;

    }

    void ConvertQuatToEuler(float* quat, float* euler, int i, int j, int k) {

        Eigen::Quaterniond quatE;
        ToEigenQuaternion(quatE, quat);

        Eigen::Vector3d eulerE;
        eulerE = QuatToEuler(quatE, i, j, k);

        ToArrayVector(euler, eulerE);

    }

    void ConvertQuatToEulerXYZ(float* quat, float* euler) {
        ConvertQuatToEuler(quat, euler, 0, 1, 2);
    }

    void ConvertQuatToEulerZXY(float* quat, float* euler) {
        ConvertQuatToEuler(quat, euler, 2, 0, 1);
    }

    void ConvertEulerToQuat(float* euler, float* quat, int i, int j, int k) {

        Eigen::Vector3d eulerE;
        ToEigenVector(eulerE, euler);

        Eigen::Quaterniond quatE;
        quatE = EulerToQuat(eulerE, i, j, k);

        ToArrayQuaternion(quat, quatE);

    }

    void ConvertEulerToQuatXYZ(float* euler, float* quat) {
        ConvertEulerToQuat(euler, quat, 0, 1, 2);
    }

    void ConvertEulerToQuatZXY(float* euler, float* quat) {
        ConvertEulerToQuat(euler, quat, 2, 0, 1);
    }

    void ConvertQuatToAngleAxis(float* quat, float* a) {

        Eigen::Quaterniond quatE;
        ToEigenQuaternion(quatE, quat);

        Eigen::AngleAxisd aE;
        aE = QuatToAngleAxis(quatE);
        ToArrayAngleAxis(a, aE);

    }

    void ConvertAngleAxisToQuat(float* a, float* quat) {

        Eigen::AngleAxisd aE;
        ToEigenAngleAxis(aE, a);

        Eigen::Quaterniond quatE;
        quatE = AngleAxisToQuat(aE);

        ToArrayQuaternion(quat, quatE);

    }

    void EstimateRotatedVector(float* vecRotated, float* vec, float* quat) {

        Eigen::Vector3d v;
        Eigen::Vector3d vRotated;
        Eigen::Quaterniond q;

        ToEigenVector(v, vec);
        ToEigenQuaternion(q, quat);

        vRotated = RotateVec(v, q);

        ToArrayVector(vecRotated, vRotated);

    }

    void EstimateQuatFromTwoVectors(float* quat, float* vecSrc, float* vecDest) {


        Eigen::Vector3d vDest, vSrc;
        ToEigenVector(vSrc, vecSrc);
        ToEigenVector(vDest, vecDest);

        Eigen::Quaterniond q = Eigen::Quaterniond::FromTwoVectors(vSrc, vDest);
        ToArrayQuaternion(quat, q);

    }

    void EstimateQuatMultiply(float* quat, float* quat1, float* quat2) {

        Eigen::Quaterniond q, q1, q2;
        ToEigenQuaternion(q1, quat1);
        ToEigenQuaternion(q2, quat2);

        q = q1 * q2;

        ToArrayQuaternion(quat, q);

    }

    void QuatNorm(float* quat) {

        float l = sqrt(quat[0] * quat[0] + quat[1] * quat[1] + quat[2] * quat[2] + quat[3] * quat[3]);
        for (int i = 0; i < 4; i++)
        {
            quat[i] = quat[i] / l;
        }

    };


    /*
        Numerical methods
    */

    float EstimateMean(const std::vector<float>& vec) {

        const size_t sz = vec.size();
        const float mean = std::accumulate(vec.begin(), vec.end(), 0.0) / sz;

        return mean;

    }

    float EstimateUnbiasedVariance(const std::vector<float>& vec) {

        const size_t sz = vec.size();

        // Calculate the mean
        const float mean = std::accumulate(vec.begin(), vec.end(), 0.0) / sz;

        // Now calculate the variance
        auto varianceFunc = [&mean, &sz](float accumulator, const float& val) {
            return accumulator + ((val - mean) * (val - mean) / sz);
        };

        return std::accumulate(vec.begin(), vec.end(), 0.0, varianceFunc);

    }

    float EstimateStandardDeviation(const std::vector<float>& vec) {
        return sqrt(EstimateUnbiasedVariance(vec));
    }

    /*
    -----------------------------------------------------------------------
        For backward compatibility
    -----------------------------------------------------------------------
    */

    void LengthFromTwoPoints(float& length, float* p1, float* p2) {

        float dx1 = p1[0] - p2[0];
        float dx2 = p1[1] - p2[1];
        float dx3 = p1[2] - p2[2];

        length = sqrt(dx1 * dx1 + dx2 * dx2 + dx3 * dx3);

    }

} // namespace