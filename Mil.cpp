// Mil.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/****************************************
Create and transmit 1553 messages.
Wait 1 ms to be sure that frame ended
Get message results from BC stack

* In order to read messages from Monitor stack, refer to Monitor code example
****************************************/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include "McxAPI.h"
#include "McxAPIReturnCodes.h"


#pragma comment(lib, "McxAPI")

INT16 iResult = 0;
UINT16 DeviceId = 0;
char errorCode[1000];
static UINT16 BusList1 = 0;
static UINT16 Element1 = 0;
static UINT16 Element2 = 1;
static UINT16 Element3 = 2;
static UINT16 DB1 = 0;
static UINT16 DB2 = 1;
static UINT16 datablock32[64];


INT16 InitDevice();
INT16 CreateFrame(bool simulateRts);
INT16 GetMessagesResults();

int main()
{
	iResult = InitDevice();
	if (iResult < 0) {
		mcx_GetReturnCodeDescription(iResult, errorCode);
		printf("Error -> %s\n", errorCode);
		return -1;
	}

	bool simulateRts = true;
	iResult = CreateFrame(simulateRts);
	if (iResult < 0) {
		mcx_GetReturnCodeDescription(iResult, errorCode);
		printf("Error -> %s\n", errorCode);
		return -1;
	}

	iResult = GetMessagesResults();
	if (iResult < 0) {
		mcx_GetReturnCodeDescription(iResult, errorCode);
		printf("Error -> %s\n", errorCode);
		return -1;
	}

	mcx_Free(DeviceId);
	printf("\n\n");
	printf("\n\n");

	// Get response from external device/unit or NoResponse in block status word
	simulateRts = false;
	iResult = CreateFrame(simulateRts);
	if (iResult < 0) {
		mcx_GetReturnCodeDescription(iResult, errorCode);
		printf("Error -> %s\n", errorCode);
		return -1;
	}

	iResult = GetMessagesResults();
	if (iResult < 0) {
		mcx_GetReturnCodeDescription(iResult, errorCode);
		printf("Error -> %s\n", errorCode);
		return -1;
	}

	printf("Ok, we are done, click Enter...");
	getchar();
	mcx_Free(DeviceId);

	return 0;
}


INT16 InitDevice() {
	INT16 res;
	UINT16  devicesDetected = 0;
	mcx_MapDevices(&devicesDetected);
	for (UINT16 i = 0; i < devicesDetected; i++)
	{
		res = mcx_Initialize(DeviceId, MIL_STD_1553);
		if (res != STL_ERR_SUCCESS)
			break;
	}
	return res;
}

INT16 CreateFrame(bool simulateRts) {
	UINT16 messageOptions = 0;
	UINT16 cmd1 = 0x3020; // BC2RT6 32WC
	UINT16 cmd2 = 0xA420; // RT202BC 32WC;
	UINT16 cmd3_0 = 0xF020; // RT11toRT30 32WC
	UINT16 cmd3_1 = 0x5C20; // RT11toRT30 32WC
	unsigned short rxStt = 0x800;
	unsigned short txStt = 0;

	if (simulateRts) {
		iResult += mcx_EnableRts(DeviceId, 0x7FFFFFFF); // Enable all RTs but not Live RT
		if (iResult < 0) return iResult;
	}
	else {
		iResult += mcx_EnableRts(DeviceId, 0);
		if (iResult < 0) return iResult;
	}
	for (UINT16 i = 0x0000; i < 32; i++)
	{
		datablock32[i] = i + 30;
	}

	if (iResult < 0) return iResult;
	iResult = mcx_Create_BusList(DeviceId, BusList1);
	if (iResult < 0) return iResult;
	iResult = mcx_Create_BusList_Element(DeviceId, Element1, cmd1, 0x80 /*Bus A*/ | messageOptions, 0x0000, rxStt, txStt);
	if (iResult < 0) return iResult;
	iResult = mcx_Create_BusList_Element(DeviceId, Element2, cmd2, 0 /*Bus B*/ | messageOptions, 0x0000, rxStt, txStt);
	if (iResult < 0) return iResult;
	messageOptions = RT2RT_FORMAT;
	iResult = mcx_Create_BusList_Element(DeviceId, Element3, cmd3_0, 0x80 /*Bus B*/ | messageOptions, cmd3_1, rxStt, txStt);
	if (iResult < 0) return iResult;
	iResult = mcx_Create_Element_DataBlock(DeviceId, DB1, 0, datablock32, 64);
	if (iResult < 0) return iResult;
	iResult = mcx_Map_DataBlock_To_Element(DeviceId, Element1, DB1);
	if (iResult < 0) return iResult;
	iResult = mcx_Map_DataBlock_To_Element(DeviceId, Element2, DB1);
	if (iResult < 0) return iResult;
	iResult = mcx_Map_DataBlock_To_Element(DeviceId, Element3, DB1);
	if (iResult < 0) return iResult;
	iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, Element1);
	if (iResult < 0) return iResult;
	iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, Element2);
	if (iResult < 0) return iResult;
	iResult = mcx_Map_Element_To_BusList(DeviceId, BusList1, Element3);
	if (iResult < 0) return iResult;

	iResult = mcx_Start(DeviceId, BusList1, 1);
	if (iResult < 0) return iResult;

	// Waiting for the frame to end
	Sleep(1);
	return iResult;
}

INT16 GetMessagesResults() {
	INT16 results = 0;
	UINT16 blockStatus = 0;
	UINT16 buffer[32];
	UINT16 status1 = 0;
	UINT16 status2 = 0;
	UINT16 tTag = 0;

	for (int i = 0; i < 3; i++) {
		results = mcx_Get_Element_Results(DeviceId, BusList1, i, &blockStatus, buffer, 32, &status1, &status2, &tTag);
		if (results < 0)
			return results;
		printf("BSW %X STS1 %X STS2 %X ", blockStatus, status1, status1);
		for (int j = 0; j < 32; j++) {
			printf("%4X ", buffer[j]);
		}
		printf("\n\n");
	}
	return results;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
