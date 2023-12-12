#ifndef LTYPES_H
#define LTYPES_H

#include <iostream>


//#include "iostream.h"
/*
variable Name:- 
_____________
1. meaningful names with vowels omitted
2. preceded by the characters representing its type
3. radar parameters preceded by 'Rdr'
4. RVP paraemters preceded by 'Rvp'
5. openGL variables - preceded by 'gl'
6. widgets - preceded by 'wdg'

1. 'enm' - enumerator type
2. 'i' - integer variable
3. 'a' - array
4. 'g' - global variable
5. 'c' - character variable
6. 'f' - float variable
7. 'lp' - long pointer
8. 's' - string variable
9. 'u' - unsigned variable eg:'uI'-unsigned integer
10.'t' - structure variable
11.'n' - counter variable
12.'at' - array structure variable
13.'e' - for enum variables

Function names:-
______________
1. preceded by 'do'
2. 'ehOn' for event handlers
3. 'clbk' for callbacks
4. 'Send' for interface transmission events

Thread names:-
____________
1. preceded by 'task'
*/
#include <stdio.h>

#define PVI_TO_OAC_INS_INT_MSG_ID			10001
#define PVI_TO_OAC_INS_CONFIG_MSG_ID	    10002
#define PVI_TO_OAC_BTN_PRESS_MSG_ID			10003
#define PVI_TO_OAC_T4_CRSR_RATES_MSG_ID		10004

#define PVI_TO_OAC_ACMDASH_MSG_ID			10005
#define PVI_TO_OAC_MISSILE_PARAM_MSG_ID		10006
#define PVI_TO_OAC_MISSILE_ASGN_MSG_ID		10007
#define PVI_TO_OAC_MISSILE_FIRE_MSG_ID		10008
#define PVI_TO_OAC_MISSILE_HIT_MSG_ID		10013
#define PVI_TO_OAC_MISSILE_CLR_MSG_ID		10014

#define PVI_TO_OAC_REFPOINT_MSG_ID			10010
#define PVI_TO_OAC_PATCH_INFO_MSG_ID		10011
#define PVI_TO_OAC_MP_INFO_MSG_ID			10012


#define TEST_CPP_STUB 1

#define MAX_MSG_SIZE 65536

typedef int Int32;
typedef int int32;
typedef unsigned int uInt32;
typedef long lInt32;
typedef unsigned long ulInt32;
typedef short sInt16;
typedef unsigned short UINT16;
typedef unsigned short uInt16;
typedef float float32;
typedef float Float32;
typedef double dFloat64;
typedef unsigned char uByte;
typedef signed char sByte;
typedef char Byte;
typedef unsigned long long ulInt64;
typedef char Bool;

#if !VXWORKS7_BUILD
typedef int TASK_ID;
typedef int STATUS;
#endif

typedef enum
{
	FAILURE_FROM_RVP = -1,
	RVP_ZERO,
	SUCCESS_FROM_RVP
}RVP_STATUS;

#if !VXWORKS7_BUILD
typedef enum
{
  RVP_FALSE, 
  RVP_TRUE
}BoolBit;
typedef short tHANDLE;
typedef struct ClkTime
{
  int Hour;
  int Min;
  int Second;
  long MilliSec;
  long MicroSec;
}ClkTime ;
typedef struct
{
    float32   m[4][4];
} ESMatrix;
#endif

struct OWSToOACheader
{
	uInt32 uiMsgId;
	uInt32 uiCrntTmH;
	uInt32 uiCrntTmL;
	uInt32 uiMsgLngth;
	uInt32 uiSrc;
	uInt32 uiDstn;
	uInt32 uiWrdCnt;
};

struct sButtonPressInfo
{
	OWSToOACheader tHdr;
	uInt32 iKeyPress;
};

struct sCursorDataPviToOac
{
	OWSToOACheader tHdr;
	sInt16	siCrsrLeftRightRt;
	sInt16	siCrsrUpDownRt;	
};


#endif
