#include "pch.h"

#include "VectorUtils.h"

namespace core {

    template<typename T>
    void ArrayToVector(T* A, vector<T>& V, int Dims) 
    {

        for (int i = 0; i < Dims; i++) {
            V[i] = A[i];
        }

    }

    void ArrayToVector(float* A, FVector2f& V, int N0, int N1)
    {

        for (int i = 0; i < N0; i++) {
            for (int j = 0; j < N1; j++) {
                V[i][j] = A[i*N1 + j];
            }
        }

    }

    template<typename T>
    void ArrayToVector(T* A, FVector2f& V, int N0, int N1)
    {

        for (int i = 0; i < N0; i++) {
            for (int j = 0; j < N1; j++) {
                V[i][j] = A[i*N1 + j];
            }
        }

    }


    template<typename T>
    void VectorToArray(vector<T>& V, T* A, int Dims) 
    {

        for (int i = 0; i < Dims; i++) {
            A[i] = V[i];
        }

    }

} // Namespace