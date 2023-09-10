#include "pch.h"

#include "Core.h"
#include <vector>


namespace core {


    FVector2f InitVector2f(int N1, int N2)
    {
        FVector2f vec(N1, vector<float>(N2, 0.0f));
        return vec;

    }


}
