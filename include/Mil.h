#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <algorithm>
#include "McxAPI.h"
#include "McxAPIReturnCodes.h"
#include "icd.h"

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib
#pragma comment(lib, "McxAPI")

// Function declarations
INT16 InitDevice();
INT16 CreateBusFrame();
INT16 GetMessagesResults();
void ProcessReceivedData(const std::string dataString);
INT16 SendMessage_6_1(ICD_6_1_data data);
void Process(const std::string dataString);
INT16 SendMessage_6_1(ICD_6_1_data data);
INT16 SendMessage_6_2(ICD_6_2_data data);
INT16 SendMessage_6_3(ICD_6_3_data data);
INT16 SendMessage_6_4(ICD_6_4_data data);