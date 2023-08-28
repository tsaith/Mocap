#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <limits>

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <vector>
#include <algorithm>
#include <numeric>



#ifndef M_PI
static const double M_PI = 3.14159265358979323846;
#endif

namespace math_utils {

float RadianToDegree(float radian);
float DegreeToRadian(float degree);

void VecSet(float *vec, float x, float y, float z);
void VecCopy(float *dest, float *src);
void VecCopy(float *dest, float *src, int dims);
template <typename T>
void VecCopy(T *dest, T *src);
void VecNorm(float &result, float* vec);
void NormalizeVec(float* dest, float* src);
void VecAdd(float *vec, float* a, float* b);
void VecSubstract(float *vec, float* a, float* b);
void VecSubstractNorm(float *vec, float* a, float* b);
void VecMultiply(float* vec, float* a, float fac);
void VecDivide(float* vec, float* a, float denominator);
void VecInverse(float* vec, float* vecRef);
void VecMean(float* vec, float* a, float* b);
void VecDot(float &result, float* a, float* b);
void VecCross(float* vec, float *a, float *b);
void VecCrossNorm(float* vec, float *a, float *b);
void EstimateUnitVector(float* vec, float *target, float *base);
void EstimateUnitVector(float* vec, float *vecRef);
void EstimateProjectedVector(float *vec, float* vecA, float* vecB);
void EstimateVerticalVector(float* vec, float* vecA, float* vecB);
void EstimateIncludedAngle(float& angle, float *vecA, float *vecB);

void EstimateDistanceFromTwoPoints(float &distance, float* p1, float* p2);
void EstimatePerpendicularDistanceFromTwoPoints(float& distance, float* p, float* a, float* b);
void InterpPoint(float *target, float* a, float* b, float weight);
bool IsParallel(float* vecA, float* vecB, float angleTol);
bool IsAntiParallel(float* vecA, float* vecB, float angleTol);

bool IsBetweenTwoValues(float v, float a, float b);
bool IsBetweenTwoPoints(float* p, float* a, float b);

void ToEigenVector(Eigen::Vector3d &dest, float* src);
void ToEigenAngleAxis(Eigen::AngleAxisd &dest, float* src);
void ToEigenQuaternion(Eigen::Quaterniond &dest, float* src);
void ToArrayVector(float* dest, Eigen::Vector3d &src);
void ToArrayAngleAxis(float* dest, Eigen::AngleAxisd &src);
void ToArrayQuaternion(float* dest, Eigen::Quaterniond &src);

Eigen::Vector3d QuatToVec(Eigen::Quaterniond q);
Eigen::Quaterniond VecToQuat(Eigen::Vector3d v);
Eigen::Vector3d QuatToEuler(Eigen::Quaterniond &q, int i, int j, int k);
Eigen::Quaterniond EulerToQuat(Eigen::Vector3d &ea, int i, int j, int k);
Eigen::AngleAxisd QuatToAngleAxis(Eigen::Quaterniond &q);
Eigen::Quaterniond AngleAxisToQuat(Eigen::AngleAxisd &a);
Eigen::Vector3d RotateVec(Eigen::Vector3d v, Eigen::Quaterniond q);

void ConvertQuatToEuler(float* quat, float* euler, int i, int j, int k);
void ConvertQuatToEulerXYZ(float* quat, float* euler);
void ConvertQuatToEulerZXY(float* quat, float* euler);
void ConvertEulerToQuat(float* euler, float* quat, int i, int j, int k);
void ConvertEulerToQuatXYZ(float* euler, float* quat);
void ConvertEulerToQuatZXY(float* euler, float* quat);

void ConvertQuatToAngleAxis(float* quat, float* a);
void ConvertAngleAxisToQuat(float* a, float* quat);

void EstimateRotatedVector(float* vecRotated, float* vec, float* quat);
void EstimateQuatFromTwoVectors(float* quat, float* vecSrc, float* vecDest);
void EstimateQuatMultiply(float* quat, float* quat1, float* quat2);

/*
    Numerical methods
*/

float EstimateMean(const std::vector<float> &vec);
float EstimateUnbiasedVariance(const std::vector<float> &vec);
float EstimateStandardDeviation(const std::vector<float> &vec);

// For backward compatibility
void LengthFromTwoPoints(float &length, float* p1, float* p2);

//Quaternion normalize
void QuatNorm(float* quat);

} // namespace

//#endif // MATH_UTILS_H