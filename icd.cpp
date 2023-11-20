#include "icd.h"
#include <iostream>
#include <basetsd.h>

#pragma once
void doubleToUint16Buffer(double value, UINT16 buffer[32]) {
    const double scaleFactor = 100.0;
    UINT16 scaledValue = static_cast<UINT16>(value * scaleFactor);
    std::fill_n(buffer, 32, 0);
    buffer[0] = scaledValue;
}