#pragma once

#include "Core.h"

namespace core {

    using namespace std;

	template<typename T>
	void ArrayToVector(T* A, vector<T>& V, int Dims);

	void ArrayToVector(float* A, FVector2f& V, int N0, int N1);

	template<typename T>
	void ArrayToVector(T* A, FVector2f& V, int N0, int N1);

	template<typename T>
	void VecorToArray(vector<T>& V, T* A, int Dims);

} // Namespace