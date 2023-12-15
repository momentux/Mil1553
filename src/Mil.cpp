#include "Mil.h"

#include <winsock2.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "DeviceInterface.h"
#include "McxAPI.h"
#include "McxAPIReturnCodes.h"
#include "parse.h"
#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib
#pragma comment(lib, "McxAPI")

#define PORT 5505
#define DeviceId 0
#define nRtNo 0x20  // rt 5 -> 2^5//

#define ICD_6_1 0
#define ICD_6_2 1
#define ICD_6_3 2
#define ICD_6_4 3

// cmd createion RT<<11|Tx/Rx<<10|SA<<5|WC
#define cmd_6_1_tx 0x2E00  // 5-T-16-32
#define cmd_6_1_rx 0x18C0  // 3-R-6-32
#define cmd_6_2_tx 0x2E84  // 5-T-20-4
#define cmd_6_2_rx 0x1884  // 3-R-4-4
#define cmd_6_3_tx 0x2F60  // 5-T-27-32
#define cmd_6_3_rx 0x1920  // 3-R-9-32
#define cmd_6_4_tx 0x2C50  // 5-T-2-16
#define cmd_6_4_rx 0x1AB0  // 3-R-21-16

static UINT16 DB1 = 0;
static UINT16 DB2 = 1;
static UINT16 DB3 = 2;
static UINT16 DB4 = 3;
static UINT16 BusList1 = 0;

UINT16 datablock_6_1[32]{};
UINT16 datablock_6_2[4]{};
UINT16 datablock_6_3[32]{};
UINT16 datablock_6_4[16]{};
char errorCode[1000];
U8BIT transmitted[4];

INT16 InitDevice() {
    INT16 res = 0;
    UINT16 devicesDetected = 0;
    mcx_MapDevices(&devicesDetected);

    res = mcx_Initialize(DeviceId, MIL_STD_1553);
    if (res != STL_ERR_SUCCESS) {
        printf("Error Initializing Device\n");
        return res;
    }

    res = mcx_SetUserPort(DeviceId, MIL_STD_1553 | MultiRT);
    if (res < 0) {
        mcx_GetReturnCodeDescription(res, errorCode);
        printf("Error -> %s\n", errorCode);
        return -1;
    }

    res = CreateBusFrame();

    if (res < 0) {
        std::cerr << "Error Creating Frame/ Element/ DB \n"
                  << std::endl;
        mcx_GetReturnCodeDescription(res, errorCode);
        std::cerr << "Error -> " << errorCode << std::endl;
        return -1;
    }

    return res;
}

INT16 CreateBusFrame() {
    INT16 iResult = 0;
    unsigned short rxStt = 0x1820;
    unsigned short txStt = 0x2E00;
    UINT16 messageOptions = RT2RT_FORMAT;

    iResult += mcx_EnableRts(DeviceId, nRtNo);
    if (iResult < 0)
        return iResult;

    iResult = mcx_Create_BusList(DeviceId, BusList1);
    if (iResult < 0)
        return iResult;

    //////////////////////////////////////////////////////////////////////////
    // only for RT-RT
    iResult = mcx_Create_BusList_Element(DeviceId, ICD_6_1, cmd_6_1_rx, 0x80 | messageOptions, cmd_6_1_tx, rxStt, txStt);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_BusList_Element(DeviceId, ICD_6_2, cmd_6_2_rx, 0x80 | messageOptions, cmd_6_2_tx, rxStt, txStt);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_BusList_Element(DeviceId, ICD_6_3, cmd_6_3_rx, 0x80 | messageOptions, cmd_6_3_tx, rxStt, txStt);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_BusList_Element(DeviceId, ICD_6_4, cmd_6_4_rx, 0x80 | messageOptions, cmd_6_4_tx, rxStt, txStt);
    if (iResult < 0)
        return iResult;
    // For RT to BC
    // iResult = mcx_Create_BusList_Element1(DeviceId, ICD_6_5, cmd13, 0x80 /*Bus B*/);
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // To create element data block
    iResult = mcx_Create_Element_DataBlock(DeviceId, DB1, 0, datablock_6_1, 32);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_Element_DataBlock(DeviceId, DB2, 0, datablock_6_2, 4);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_Element_DataBlock(DeviceId, DB3, 0, datablock_6_3, 32);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_Element_DataBlock(DeviceId, DB4, 0, datablock_6_4, 16);
    if (iResult < 0)
        return iResult;
    /////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Mapping the created data block to element
    iResult = mcx_Map_DataBlock_To_Element(DeviceId, ICD_6_1, DB1);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Map_DataBlock_To_Element(DeviceId, ICD_6_2, DB2);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Map_DataBlock_To_Element(DeviceId, ICD_6_3, DB3);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Map_DataBlock_To_Element(DeviceId, ICD_6_4, DB4);
    if (iResult < 0)
        return iResult;
    /////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////
    // Mapping element to bus list
    iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, ICD_6_1);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, ICD_6_2);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, ICD_6_3);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, ICD_6_4);
    if (iResult < 0)
        return iResult;
    ////////////////////////////////////////////////////////////////////////////////

    iResult = mcx_Start(DeviceId, BusList1, 0);
    if (iResult < 0)
        return iResult;

    return 0;
}

void Process(const std::string dataString) {
    ICD_6_1_data data1;
    ICD_6_2_data data2;
    ICD_6_3_data data3;
    ICD_6_4_data data4;

    ParseFGMessage(dataString, data1, data2, data3, data4);

    INT16 iResult = 0;
    iResult = mcx_Get_Buslist_TransmittedElements(DeviceId, BusList1, transmitted);
    if (iResult < 0) {
        mcx_GetReturnCodeDescription(iResult, errorCode);
        printf("Error -> %s\n", errorCode);
        return;
    }

    if (transmitted[0]) {
        iResult = SendMessage_6_1(data1);
        if (iResult < 0) {
            mcx_GetReturnCodeDescription(iResult, errorCode);
            printf("Error -> %s\n", errorCode);
            return;
        }
    }
    if (transmitted[1]) {
        iResult = SendMessage_6_2(data2);
        if (iResult < 0) {
            mcx_GetReturnCodeDescription(iResult, errorCode);
            printf("Error -> %s\n", errorCode);
            return;
        }
    }
    if (transmitted[2]) {
        iResult = SendMessage_6_3(data3);
        if (iResult < 0) {
            mcx_GetReturnCodeDescription(iResult, errorCode);
            printf("Error -> %s\n", errorCode);
            return;
        }
    }
    if (transmitted[3]) {
        iResult = SendMessage_6_4(data4);
        if (iResult < 0) {
            mcx_GetReturnCodeDescription(iResult, errorCode);
            printf("Error -> %s\n", errorCode);
            return;
        }
    }
    Sleep(1);
}

INT16 SendMessage_6_1(ICD_6_1_data data) {
    INT16 results = 0;
    prepare(data, datablock_6_1);
    hexPrint(datablock_6_1, 32);
    results = mcx_Element_UpdateData(DeviceId, BusList1, ICD_6_1);
    return results;
}

INT16 SendMessage_6_2(ICD_6_2_data data) {
    INT16 results = 0;
    prepare(data, datablock_6_2);
    hexPrint(datablock_6_2, 4);
    results = mcx_Element_UpdateData(DeviceId, BusList1, ICD_6_2);
    return results;
}

INT16 SendMessage_6_3(ICD_6_3_data data) {
    INT16 results = 0;
    prepare(data, datablock_6_3);
    hexPrint(datablock_6_3, 32);
    results = mcx_Element_UpdateData(DeviceId, BusList1, ICD_6_3);
    return results;
}

INT16 SendMessage_6_4(ICD_6_4_data data) {
    INT16 results = 0;
    prepare(data, datablock_6_4);
    hexPrint(datablock_6_4, 16);
    results = mcx_Element_UpdateData(DeviceId, BusList1, ICD_6_4);
    return results;
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

static inline void hexPrint(UINT16 buffer[], int length) {
    std::cout << "[";
    for (int i = 0; i < length; ++i) {
        std::cout << std::hex << buffer[i];
        if (i < length - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    Byte buffer[1024];
    Int32 size;
    Int32 cnt;

    UDPLanInterface sockObj(0, PORT, (Byte *)"127.0.0.1", RX_MODE);
    // Initialize device
    InitDevice();

    while (1) {
        // Process(
        //     "0.756 ,640.9234 ,-904.1187 ,13.43551 ,305.4992 ,0.008158886 ,-1.043156 ,5.331967 ,306.6131 ,77.68379 "
        //     ",3047.88  ,12.86905 ,-3.593511e-05 ,-0.03492117 ,0.0007221791 ,309.9201 ,19.68432 ,656.619  ,2023 ,12   "
        //     ",13  ,  22 ,58   ,40   ,378");
        if ((cnt = sockObj.RecvPack(buffer, &size)) > 0) {
            std::string dataString(buffer);
            buffer[cnt] = '\0';
            rtrim(dataString);
            std::cout << "Processing data: " << dataString << std::endl;
            Process(dataString);
        }
    }

    mcx_Free(DeviceId);
    return 0;
}
