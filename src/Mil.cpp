#include <winsock2.h>
#include <ws2tcpip.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "Mil.h"
#include "McxAPI.h"
#include "McxAPIReturnCodes.h"
#include "icd.h"
#include "parse.h"

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib
#pragma comment(lib, "McxAPI")

static UINT16 ICD_6_1 = 0;
static UINT16 ICD_6_2 = 1;
static UINT16 ICD_6_3 = 2;
static UINT16 ICD_6_4 = 3;
static UINT16 DB1 = 0;
static UINT16 DB2 = 1;
static UINT16 DB3 = 2;
static UINT16 DB4 = 3;

UINT16 DeviceId = 0;
char errorCode[1000];
static UINT16 BusList1 = 0;
INT16 deviceInitializationStatus = 0;

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server, si_other;
    int slen, recv_len;
    char buf[2048];  // Adjust buffer size as needed
    char clientAddr[INET_ADDRSTRLEN];

    slen = sizeof(si_other);

    // Initialize device
    deviceInitializationStatus = InitDevice();
    if (deviceInitializationStatus < 0) {
        mcx_GetReturnCodeDescription(deviceInitializationStatus, errorCode);
        std::cerr << "Error -> " << errorCode << std::endl;
        return -1;
    }

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Failed. Error Code : " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Create a socket
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Could not create socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error code : " << WSAGetLastError() << std::endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    bool isFirstLine = true;  // Flag to identify the first line

    // Keep listening for data
    while (true) {
        // Receive data
        recv_len = recvfrom(s, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&si_other, &slen);
        if (recv_len == SOCKET_ERROR) {
            std::cerr << "recvfrom() failed with error code : " << WSAGetLastError() << std::endl;
            break;
        }

        buf[recv_len] = '\0';  // Null-terminate the received data

        // Convert to string and trim trailing spaces
        std::string dataString(buf);
        dataString.erase(std::find_if(dataString.rbegin(), dataString.rend(), [](unsigned char ch) { return !std::isspace(ch); })
                             .base(),
                         dataString.end());

        // Print details of the client/peer and the data received
        if (InetNtopA(AF_INET, &si_other.sin_addr, clientAddr, INET_ADDRSTRLEN) != NULL) {
            if (isFirstLine) {
                std::cout << "Received packet from " << clientAddr << ":" << ntohs(si_other.sin_port) << std::endl;
                isFirstLine = false;
            } else {
                std::cout << "Processing data: " << dataString << std::endl;
                Process(dataString);
            }
        } else {
            std::cerr << "InetNtopA failed with error: " << WSAGetLastError() << std::endl;
        }
    }

    // Cleanup
    mcx_Free(DeviceId);
    closesocket(s);
    WSACleanup();

    return 0;
}

INT16 InitDevice() {
    INT16 res = 0;
    UINT16 devicesDetected = 0;
    mcx_MapDevices(&devicesDetected);
    for (UINT16 i = 0; i < devicesDetected; i++) {
        res = mcx_Initialize(DeviceId, MIL_STD_1553);
        if (res != STL_ERR_SUCCESS) {
            break;
        }
    }
    res = CreateBusFrame();
    return res;
}

INT16 CreateBusFrame() {
    INT16 iResult = 0;

    static UINT16 datablock32[64];

    UINT16 messageOptions = RT2RT_FORMAT;
    UINT16 cmd1 = 0x3020;  // BC2RT6 32WC
    UINT16 cmd2 = 0xA420; // RT202BC 32WC;
    UINT16 cmd3 = 0xF020;  // RT11toRT30 32WC
    UINT16 cmd4 = 0x5C20;  // RT11toRT30 32WC

    unsigned short rxStt = 0x800;
    unsigned short txStt = 0;

    iResult += mcx_EnableRts(DeviceId, 0);
    if (iResult < 0)
        return iResult;

    for (UINT16 i = 0x0000; i < 32; i++) {
        datablock32[i] = i + 30;
    }

    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_BusList(DeviceId, BusList1);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_BusList_Element(DeviceId, ICD_6_1, cmd1, 0x80 /*Bus A*/ | messageOptions, 0x0000, rxStt, txStt);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_BusList_Element(DeviceId, ICD_6_2, cmd2, 0x80 /*Bus A*/ | messageOptions, 0x0000, rxStt, txStt);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_BusList_Element(DeviceId, ICD_6_3, cmd3, 0x80 /*Bus A*/ | messageOptions, 0x0000, rxStt, txStt);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_BusList_Element(DeviceId, ICD_6_4, cmd4, 0x80 /*Bus A*/ | messageOptions, 0x0000, rxStt, txStt);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_Element_DataBlock(DeviceId, DB1, 0, datablock32, 64);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_Element_DataBlock(DeviceId, DB2, 0, datablock32, 64);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_Element_DataBlock(DeviceId, DB3, 0, datablock32, 64);
    if (iResult < 0)
        return iResult;
    iResult = mcx_Create_Element_DataBlock(DeviceId, DB4, 0, datablock32, 64);
    if (iResult < 0)
        return iResult;
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

    iResult = mcx_Start(DeviceId, BusList1, 1);
    if (iResult < 0)
        return iResult;

    // Waiting for the frame to end
    Sleep(1);
    return iResult;
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

    iResult = SendMessage_6_2(data2);
    if (iResult < 0) {
        mcx_GetReturnCodeDescription(iResult, errorCode);
        printf("Error -> %s\n", errorCode);
        return;
    }

    iResult = SendMessage_6_3(data3);
    if (iResult < 0) {
        mcx_GetReturnCodeDescription(iResult, errorCode);
        printf("Error -> %s\n", errorCode);
        return;
    }

    iResult = SendMessage_6_4(data4);
    if (iResult < 0) {
        mcx_GetReturnCodeDescription(iResult, errorCode);
        printf("Error -> %s\n", errorCode);
        return;
    }

    for (int i = 0; i < 4; i++) {
        iResult = GetMessagesResults();
        if (iResult < 0) {
            mcx_GetReturnCodeDescription(iResult, errorCode);
            printf("Error -> %s\n", errorCode);
            return;
        }
    }
}

INT16 SendMessage_6_1(ICD_6_1_data data) {
    INT16 results = 0;
    UINT16 buffer[32];
    std::cout << "Sending data: " << data.velocitytimetag << std::endl;
    prepare(data, buffer);
    results = mcx_Element_DataBlock_Write(DeviceId, ICD_6_1, DB1, buffer, 32);
    return results;
}

INT16 SendMessage_6_2(ICD_6_2_data data) {
    INT16 results = 0;
    UINT16 buffer[32];
    std::cout << "Sending data: " << data.loop << std::endl;
    prepare(data, buffer);
    results = mcx_Element_DataBlock_Write(DeviceId, ICD_6_1, DB1, buffer, 32);
    return results;
}

INT16 SendMessage_6_3(ICD_6_3_data data) {
    INT16 results = 0;
    UINT16 buffer[32];
    std::cout << "Sending data: " << data.strmode << std::endl;
    prepare(data, buffer);
    results = mcx_Element_DataBlock_Write(DeviceId, ICD_6_1, DB1, buffer, 32);
    return results;
}

INT16 SendMessage_6_4(ICD_6_4_data data) {
    INT16 results = 0;
    UINT16 buffer[32];
    std::cout << "Sending data: " << data.utctimetag << std::endl;
    prepare(data, buffer);
    results = mcx_Element_DataBlock_Write(DeviceId, ICD_6_1, DB1, buffer, 32);
    return results;
}

INT16 GetMessagesResults() {
    INT16 results = 0;
    UINT16 blockStatus = 0;
    UINT16 buffer[32];
    UINT16 status1 = 0;
    UINT16 status2 = 0;
    UINT16 tTag = 0;

    results = mcx_Get_Element_Results(DeviceId, BusList1, i, &blockStatus, buffer, 32, &status1, &status2, &tTag);
    if (results < 0)
        return results;
    printf("BSW %X STS1 %X STS2 %X ", blockStatus, status1, status1);
    for (int j = 0; j < 32; j++) {
        printf("%4X ", buffer[j]);
    }
    printf("\n\n");
    return results;
}