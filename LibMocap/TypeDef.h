#pragma once

typedef struct FVector {

	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;

} FVector;

typedef struct FQuat {

	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 1.0f;

} FQuat;

typedef struct FTransform {

	FVector Translation{0.0, 0.0, 0.0};
	FQuat Rotation {0.0, 0.0, 0.0, 1.0};
	FVector Scale3D {1.0, 1.0, 1.0};

} FTransform;

