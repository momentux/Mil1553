#include <basetsd.h>

#pragma once
struct ICD_6_1_data {
    double value1 = 0.0;
    double value2 = 0.0;
    double value3 = 0.0;
    double value4 = 0.0;
    double value5 = 0.0;
};

void doubleToUint16Buffer(double value, UINT16 buffer[32]);