// vector_make_helpers.cpp

#include "vectortypes.h"

int2 make_int2(int a, int b)
{
    int2 i2(a,b);
    i2.x = a;
    i2.y = b;
    return i2;
}

float2 make_float2(float a, float b)
{
    float2 f2 = {a,b};
    return f2;
}

float3 make_float3(float a, float b, float c)
{
    float3 f3 = {a,b,c};
    return f3;
}
