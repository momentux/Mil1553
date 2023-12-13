#ifndef MIL_H
#define MIL_H

#include "stdafx.h"
#include "icd.h"

// Function declarations
INT16 InitDevice();
INT16 CreateBusFrame();
void Process(const std::string dataString);
INT16 SendMessage_6_1(ICD_6_1_data data);
INT16 SendMessage_6_2(ICD_6_2_data data);
INT16 SendMessage_6_3(ICD_6_3_data data);
INT16 SendMessage_6_4(ICD_6_4_data data);

#endif // MIL_H