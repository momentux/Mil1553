#include "Mil.h"

#include "DeviceInterface.h"
#include "ltypes.h"
#include "parse.h"
#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib
#pragma comment(lib, "McxAPI")

#define PORT 8888
#define UINT16 DeviceId 0
#define UINT16 BusList1 0
#define INT RT_NO = 0x20;  // rt 5 -> 2^5//

#define UINT16 ICD_6_1 0
#define UINT16 ICD_6_2 1
#define UINT16 ICD_6_3 2
#define UINT16 ICD_6_4 3

char errorCode[1000];
static UINT16 buffer_6_1[64];
static UINT16 buffer_6_2[64];
static UINT16 buffer_6_3[64];
static UINT16 buffer_6_4[64];

// cmd createion RT<<11|Tx/Rx<<10|SA<<5|WC
// UINT16 cmd1 = 0x2E00; // 5-T-16-32
// UINT16 cmd1r = 0x18C0;// 3-R-6-32

UINT16 cmd_6_1_tx = 0x2E1F;  // 5-T-16-32
UINT16 cmd_6_1_rx = 0x1DF0;  // 3-R-6-32

UINT16 cmd_6_2_tx = 0x2E83;  // 5-T-20-4
UINT16 cmd_6_2_rx = 0x1883;  // 3-R-4-4

UINT16 cmd_6_3_tx = 0x2F7F;  // 5-T-27-32
UINT16 cmd_6_3_rx = 0x193F;  // 3-R-9-32

UINT16 cmd_6_4_tx = 0x2C4F;  // 5-T-2-16
UINT16 cmd_6_4_rx = 0x199F;  // 3-R-21-16

int main() {
    Byte buffer[512];
    Int32 size;
    Int32 cnt;

    UDPLanInterface sockObj(0, PORT, (Byte *)"127.0.0.1", RX_MODE);

    // Initialize MIL 1553B device
    InitDevice();

    while (1) {
        if ((cnt = sockObj.RecvPack(buffer, &size)) > 0) {
            buffer[cnt] = '\0';
            std::string dataString(buffer);
            rtrim(dataString);
            std::cout << "Processing data: " << dataString << std::endl;
            Process(dataString);
        }
    }

    mcx_Free(DeviceId);
    return 0;
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
}

INT16 InitDevice() {
    INT16 res = 0;
    UINT16 devicesDetected = 0;
    mcx_MapDevices(&devicesDetected);

    // initialize the deviceID 0
    res = mcx_Initialize(DeviceId, MIL_STD_1553);
    if (res != STL_ERR_SUCCESS) {
        printf("Error Initializing Device\n");
        return res;
    }

    // map port, not sure if this is really needed
    res = mcx_SetUserPort(DeviceId, MIL_STD_1553 | MultiRT);
    if (res < 0) {
        mcx_GetReturnCodeDescription(res, errorCode);
        printf("Error -> %s\n", errorCode);
        return -1;
    }

    res = CreateBusFrame();

    if (res < 0) {
        std::cerr << "Error Creating Frame/ Element/ DB \n" << std::endl;
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

    UINT16 stat = 0;
    UINT32 RtList = 0;

    UINT16 blockStatus = 0;
    iResult += mcx_EnableRts(DeviceId, nRtNo);
    if (iResult < 0) return iResult;

    mcx_Get_EnabledRts(DeviceId, &RtList);

    for (UINT16 i = 0x0000; i < 32; i++) {
        buffer_6_1[i] = 0xFFFF;
        buffer_6_2[i] = 0xFFFF;
        buffer_6_3[i] = 0xFFFF;
        buffer_6_4[i] = 0xFFFF;
        datablock_6_5[i] = 0xFFFF;
    };
    iResult = mcx_Create_BusList(DeviceId, BusList1);
    if (iResult < 0) return iResult;

    // only for RT-RT
    iResult = mcx_Create_BusList_Element(DeviceId, ICD_6_1, cmd_6_1_tx,
                                         0x80 | RT2RT_FORMAT, cmd_6_1_rx, rxStt,
                                         txStt);
    if (iResult < 0) return iResult;
    iResult = mcx_Create_BusList_Element(
        DeviceId, ICD_6_2, cmd_6_2_tx, 0x80 | RT2RT_FORMAT, cmd_6_2_rx, rxStt,
        txStt);  ///*Bus A*/ , 0x0000, rxStt, txStt);
    if (iResult < 0) return iResult;
    iResult = mcx_Create_BusList_Element(
        DeviceId, ICD_6_3, cmd_6_3_tx, 0x80 | RT2RT_FORMAT, cmd_6_3_rx, rxStt,
        txStt);  ///*Bus A*/, 0x0000, rxStt, txStt);
    if (iResult < 0) return iResult;
    iResult = mcx_Create_BusList_Element(
        DeviceId, ICD_6_4, cmd_6_4_tx, 0x80 | RT2RT_FORMAT, cmd_6_4_rx, rxStt,
        txStt);  ///*Bus A*/, 0x0000, rxStt, txStt);
    if (iResult < 0) return iResult;

    // For RT to BC
    // iResult = mcx_Create_BusList_Element1(DeviceId, ICD_6_5, cmd13, 0x80
    // /*Bus B*/);

    //////////////////////////////////////////////////////////////////////////
    // To create element data block
    iResult =
        mcx_Create_Element_DataBlock(DeviceId, ICD_6_1, 0, buffer_6_1, 64);
    if (iResult < 0) return iResult;
    iResult =
        mcx_Create_Element_DataBlock(DeviceId, ICD_6_2, 0, buffer_6_2, 64);
    if (iResult < 0) return iResult;
    iResult =
        mcx_Create_Element_DataBlock(DeviceId, ICD_6_3, 0, buffer_6_3, 64);
    if (iResult < 0) return iResult;
    iResult =
        mcx_Create_Element_DataBlock(DeviceId, ICD_6_4, 0, buffer_6_4, 64);
    if (iResult < 0) return iResult;

    /////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Mapping the created data block to element
    iResult = mcx_Map_DataBlock_To_Element(DeviceId, ICD_6_1, ICD_6_1);
    if (iResult < 0) return iResult;
    iResult = mcx_Map_DataBlock_To_Element(DeviceId, ICD_6_2, ICD_6_2);
    if (iResult < 0) return iResult;
    iResult = mcx_Map_DataBlock_To_Element(DeviceId, ICD_6_3, ICD_6_3);
    if (iResult < 0) return iResult;
    iResult = mcx_Map_DataBlock_To_Element(DeviceId, ICD_6_4, ICD_6_4);
    if (iResult < 0) return iResult;

    /////////////////////////////////////////////////////////////////////////////

    // Mapping element to bus list
    iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, ICD_6_1);
    if (iResult < 0) return iResult;
    iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, ICD_6_2);
    if (iResult < 0) return iResult;
    iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, ICD_6_3);
    if (iResult < 0) return iResult;
    iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, ICD_6_4);
    if (iResult < 0) return iResult;

    // to add new
    ////////////////////////////////////////////////////////////////////////////////

    iResult = mcx_Start(DeviceId, BusList1, 0);
    if (iResult < 0) return iResult;

    // Waiting for the frame to end
    // Sleep(20);
}

void Process(const std::string dataString) {
    ICD_6_1_data data1;
    ICD_6_2_data data2;
    ICD_6_3_data data3;
    ICD_6_4_data data4;

    ParseFGMessage(dataString, data1, data2, data3, data4);

    INT16 iResult = 0;
    iResult = SendMessage_6_1(data1);
    if (iResult < 0) {
        mcx_GetReturnCodeDescription(iResult, errorCode);
        printf("Error -> %s\n", errorCode);
        return;
    }
    Sleep(2);

    iResult = SendMessage_6_2(data2);
    if (iResult < 0) {
        mcx_GetReturnCodeDescription(iResult, errorCode);
        printf("Error -> %s\n", errorCode);
        return;
    }
    Sleep(2);

    iResult = SendMessage_6_3(data3);
    if (iResult < 0) {
        mcx_GetReturnCodeDescription(iResult, errorCode);
        printf("Error -> %s\n", errorCode);
        return;
    }
    Sleep(2);

    iResult = SendMessage_6_4(data4);
    if (iResult < 0) {
        mcx_GetReturnCodeDescription(iResult, errorCode);
        printf("Error -> %s\n", errorCode);
        return;
    }
    Sleep(2);
}

INT16 SendMessage_6_1(ICD_6_1_data data) {
    INT16 results = 0;
    std::cout << "Sending data: " << data.velocitytimetag << std::endl;
    prepare(data, buffer_6_1);
    // result = mcx_Element_DataBlock_Write(DeviceId, ICD_6_2, ICD_6_2,
    // buff_I21, 32);
    results = mcx_Element_UpdateData(DeviceId, BusList1, ICD_6_1);
    return results;
}

INT16 SendMessage_6_2(ICD_6_2_data data) {
    INT16 results = 0;
    prepare(data, buffer_6_2);
    results = mcx_Element_UpdateData(DeviceId, BusList1, ICD_6_2);
    return results;
}

INT16 SendMessage_6_3(ICD_6_3_data data) {
    INT16 results = 0;
    prepare(data, buffer_6_3);
    results = mcx_Element_UpdateData(DeviceId, BusList1, ICD_6_3);
    return results;
}

INT16 SendMessage_6_4(ICD_6_4_data data) {
    INT16 results = 0;
    prepare(data, buffer_6_4);
    results = mcx_Element_UpdateData(DeviceId, BusList1, ICD_6_4);
    return results;
}

INT16 GetMessagesResults() {
    INT16 results = 0;
    UINT16 blockStatus = 0;
    UINT16 buffer[32];
    UINT16 status1 = 0;
    UINT16 status2 = 0;
    UINT16 tTag = 0;

    for (int i = 0; i < 4; i++) {
        results =
            mcx_Get_Element_Results(DeviceId, BusList1, i, &blockStatus, buffer,
                                    32, &status1, &status2, &tTag);
        if (results < 0) return results;
        printf("BSW %X STS1 %X STS2 %X ", blockStatus, status1, status1);
        for (int j = 0; j < 32; j++) {
            printf("%4X ", buffer[j]);
        }
        printf("\n\n");
    }
    return results;
}
