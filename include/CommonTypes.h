
#ifndef COMMON_TYPES_H__
#define COMMON_TYPES_H__

// Check if other header was included that uses #defines instead of typedefs
//#ifndef U32BIT

#if defined(WIN32)

// WIN32 operating-system-specific definitions.

#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <conio.h>
#include <direct.h>
#include <crtdbg.h>
#include <process.h>
#include <setupapi.h>
#include <share.h>
#include <tchar.h>
#include <stdlib.h>
#include <assert.h>
//#include<stdio.h>
#include<winsock2.h>

//#include <inttypes.h>
#ifndef HAS_INT_TYPES

#ifdef HAS_C99
#include <stdint.h>
#endif

#endif

#include <stdint.h>
#include <sys/types.h>

typedef unsigned int    U32BIT;
typedef signed int      S32BIT;
typedef unsigned short  U16BIT;
typedef signed short    S16BIT;
typedef unsigned char   U8BIT;
//typedef signed char     S8BIT;

//#endif //U32BIT
#define Assert_NonOsDependent(expr)						( _ASSERT(expr) )

#define GetLastError_NonOsDependent						GetLastError

#define Sleep_NonOsDependent(dwMilliseconds)			( Sleep((DWORD)(dwMilliseconds)) ) // Uses units of milliseconds.

#define _DECL											WINAPI

#define _EXTERN

// Basic numeric types.
#define U64BIT											UINT64
#define S64BIT											INT64
#ifndef USE_DDC_LIBRARY
#define U32BIT											UINT32
#define S32BIT											INT32
#define U16BIT											UINT16
#define S16BIT											INT16
#define U8BIT											UINT8
#define BOOLEAN 										UINT8
#define S8BIT											char
//typedef char											S8BIT;
#endif // USE_DDC_LIBRARY
#define WORD											U16BIT
#define MAIN											_tmain
#define ARG_CHAR										TCHAR
#define STRCMP											_tcscmp
#define SPRINTF											_tprintf
#ifdef  _UNICODE
#define STRING											wstring
#define CERR											wcerr
#else // ! _UNICODE
#define STRING											string
#define CERR											cerr
#endif // _UNICODE

#define LHANDLE											PVOID
#define U64BIT_PTR										PUINT64
#define P_VOID											PVOID
#define P_S8BIT											INT8*
#define C_SECTION										CRITICAL_SECTION

// For Windows kernel mode BOOLEAN already typedef'ed in wdm.h, ntddk.h
#ifndef _DDK_DRIVER_
typedef unsigned char   BOOLEAN;
#endif

typedef unsigned __int64 U64BIT;
typedef signed __int64   S64BIT;

/* Typedef for API status/error values */
#ifndef _BSA_STATUS_DEFINED_
typedef S16BIT BSA_STATUS;
#	define _BSA_STATUS_DEFINED_
#endif /*_BSA_STATUS_DEFINED_*/

/* Same as above */
#ifndef _STLD_RETURN_DEFINED_
typedef S16BIT STLD_RETURN;
#	define _STLD_RETURN_DEFINED_
#endif /*_BSA_STATUS_DEFINED_*/

// WIN32 operating-system specific definitions.
#ifndef WINAPI
//#error WINAPI undefined. Include windows.h or something else before this.
#endif

#ifndef _MSC_VER
#error This is for Microsoft compiler (Visual C, SDK, WDK)
#endif

#define _DECL	WINAPI
//#define _EXTERN extern	


typedef signed short BSA_STATUS;


enum {
	BSA_ERR_SUCCESS = 0,
	BSA_ERR_UNKNOWN = -128,	//+ NEW
	BSA_ERR_NOT_SUPPORTED = -70,  // _UnsupportedFunction
	BSA_ERR_BAD_PARAMETER = -52,  // _InvalidArguments

	BSA_ERR_INVALID_ACCESS = -54,  // _DeviceBusy
	BSA_ERR_INVALID_REQUEST = -1,   // _InvalidRequest
	BSA_ERR_ALLOCATION_FAIL = -36,  // _FailToAllocMem

	BSA_ERR_DRIVER_OPEN = -13,  // _FailToOpenDevice
	BSA_ERR_INVALID_CARD = -11,  // _UninstalledDevice
	BSA_ERR_INVALID_CARDNUM = -78,  // _NoSuchDevice +
	BSA_ERR_INVALID_DEVNUM = -59,  // _DeviceIdOutOfRange
	BSA_ERR_INVALID_ADDRESS = -76,  // _FailToSetAddress
	BSA_ERR_INVALID_ADDRESS_MODE = -45, // _BadBitMode ??
	BSA_ERR_INVALID_BUFFER = -61,  // _NullPointer
	BSA_ERR_MSGSTRUCT = -37,  // _FailToCopyMem
	BSA_ERR_TOO_MANY_DEVS = -3,   // _TooManyDevicesFound
	BSA_ERR_RESOURCE_REQ = -16,  // _nDeviceStatusHi ??
	BSA_ERR_IOWRITE = -34,  // _FailToWriteDataToDevice
	BSA_ERR_IOREAD = -77,  // _FailToPerformIo
	BSA_ERR_MEM_MAP = -8,   // _FailToMapViewOfFile
	BSA_ERR_RESPTIME = -27,  // _FailToReadResp
};

typedef struct EthDataStruct
{
	UINT16 deviceId;
	unsigned int address;
	UINT16 type;
	WORD* buffer;
	DWORD buffLen;

} ;

// Open the file whose path is given in given mode, and properly set given pointer to point it.
// Return the result of the operation in the pointed error variable: 0  in case of success; otherwise, in WIN32 return the error returned by fopen_s, and in Unix return -1.
#define OPEN_FILE(/* FILE** */fppFile, /* const char* */szpFilePath, /* const char* */ szpMode, /* errno_t* */ errp) \
														{ (*(errp)) = ( fopen_s ((fppFile), (szpFilePath), (szpMode)) ); }

// Load the library whose name is given.
// Return the HMODULE of the loaded library, or null in case of failure.
#define LOAD_LIBRARY(/* const char* */ szLibraryName) \
														( LoadLibraryA (szLibraryName) )

#define PRINT_LAST_ERROR() \
														{ printf ("%u", GetLastError ()); }
#pragma warning(disable:4996) // Disables all the C4996 Compiler Warnings.

#elif defined(VX_WORKS)

// VxWorks operating-systems-specific definitions.
#include <vxWorks.h>
#include <taskLib.h>
#include <time.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

#include "stdint.h"
#include "stdlib.h"
//#include "stdio.h"
#include "unistd.h"
#include "bootLib.h"

IMPORT void sysUsDelay(UINT delay);

//static inline void ctime_s (char* cp, unsigned u, time_t const* t)	{ strncpy (cp, ctime(t), u); }

#define GetLastError_NonOsDependent()					errno

#define Assert_NonOsDependent(expr)						{ assert(expr); }

#define Sleep_NonOsDependent(dMilliseconds)				{ taskDelay((dMilliseconds) * 4); } // Function taskDelay uses units of ticks, where each tick equals 250 microseconds.

#define _DECL

#define _EXTERN

#if not defined (errno_t)
typedef int errno_t;
#endif // not defined (errno_t)

typedef void *HMODULE;

// Basic numeric types.
#define U64BIT											uint64_t
#define S64BIT											int64_t
#ifndef USE_DDC_LIBRARY
#define U32BIT											unsigned int
#define S32BIT											signed int
#define U16BIT											unsigned short
#define S16BIT											signed short
#define U8BIT											uint8_t
#define S8BIT											char
#define BOOLEAN											unsigned char
#endif // USE_DDC_LIBRARY
#define BOOL											int
#define DWORD											uint32_t
#define WORD											uint16_t

#define MAIN											main
#define ARG_CHAR										char
#define TCHAR											char
#define STRING											char*
#define TEXT(str)										(str)
#define STRCMP											strcmp
#define SPRINTF											sprintf
#define CERR											cerr
#define LHANDLE											void*
#define P_VOID											void*
#define P_S8BIT											char*
#define U64BIT_PTR										uint64_t*
#define va_list											char*

/* Same as above */
#ifndef _STLD_RETURN_DEFINED_
typedef S16BIT STLD_RETURN;
#	define _STLD_RETURN_DEFINED_
#endif /*_BSA_STATUS_DEFINED_*/

// Open the file whose path is given in given mode, and properly set given pointer to point it.
// Return the result of the operation in the pointed error variable: 0  in case of success; otherwise, in WIN32 return the error returned by fopen_s, and in Unix return -1.
#define OPEN_FILE(/* FILE** */fppFile, /* const char* */szpFilePath, /* const char* */ szpMode, /* errno_t* */ errp) \
														{ \
															(*(fppFile)) = fopen ((szpFilePath), (szpMode)); \
															err = ( (*(fppFile)) ? 0 : -1 ); \
														}

// Load the library whose name is given.
// Return the HMODULE of the loaded library, or null in case of failure.
#define LOAD_LIBRARY(/* const char* */ szLibraryName) \
														(dlopen ( (szLibraryName), (RTLD_NOW | RTLD_LOCAL) ) )

#define PRINT_LAST_ERROR() \
														{ printf ("%s", dlerror ()); }

// Set given pointer of given program to the function in given module whose name is given.
#if defined (__GNUC__) && (defined(__i386) || defined(__amd64__))
#define GET_FUNCTION_ADDRESS(/* const char[] string */szProgram, /* const HMODULE */hmLibrary, /* const char* */szFuncName, /* void** */vppFuncAddress) \
														{ \
															(*(vppFuncAddress)) = (dlsym ((hmLibrary), (szFuncName))); \
															if ( ! (*(vppFuncAddress)) ) \
															{ \
																printf ("%s.LoadFunction.Tried: name - %s\n", (szProgram), (szFuncName)); \
																/* Also QNX6/x86, GNU C++ 4.3.3:  S16BIT function(void) is decorated as "_Z<strlen(name)><name>v". */ \
																int iNameLength = strlen (szFuncName); \
																char szNameBuffer[8 + strlen (szFuncName)]; \
																sprintf (szNameBuffer, "_Z%u%sv", iNameLength, (szFuncName)); \
																(*(vppFuncAddress)) = dlsym ((hmLibrary), szNameBuffer); \
																if ( ! (*(vppFuncAddress)) ) \
																{ \
																	printf ("%s.LoadFunction.Tried: name - %s\n", (szProgram), szNameBuffer); \
																	sprintf (szNameBuffer, "_Z%u%si", iNameLength, (szFuncName)); /* With one integer parameter the decoration becomes: "_Z<strlen(name)><name>i". */ \
																	(*(vppFuncAddress)) = dlsym ((hmLibrary), szNameBuffer); \
																	if ( ! (*(vppFuncAddress)) ) \
																	{ \
																		printf ("%s.LoadFunction.Tried: name - %s\n", (szProgram), szNameBuffer); \
																	} \
																} \
															} \
														}
#else // not ( defined (__GNUC__) && (defined(__i386) || defined(__amd64__)) )
#define GET_FUNCTION_ADDRESS(/* const char[] string */szProgram, /* const HMODULE */hmLibrary, /* const char* */szFuncName, /* void** */vppFuncAddress) \
														{ \
															(*(vppFuncAddress)) = (dlsym ((hmLibrary), (szFuncName))); \
														}
#endif // defined (__GNUC__) && (defined(__i386) || defined(__amd64__))

// Min, max aren't normally defined for c++ (should be templates).
#if ( (!defined(min)) && (!defined(MIN_REDEFINED)) )
#define min(_a,_b)										((_a) <= (_b) ? (_a):(_b))
#define MIN_REDEFINED
#endif // min

#if ( (!defined(max)) && (!defined(MAX_REDEFINED)) )
#define max(_a,_b)										((_a) >= (_b) ? (_a):(_b))
#define MAX_REDEFINED
#endif // max

struct timezone
{
	int tz_minuteswest; // Minutes west of GMT.
	int tz_dsttime; // Nonzero if DST is ever in effect.
};

struct timeval
{
	long tv_sec; // Seconds part of time stamp.
	long tv_usec; // Microseconds part of time stamp.
};



#elif defined(LINUX_DMA) || defined(PETA_PCI) || defined(UBUN_PCI)
#ifdef __cplusplus
extern "C" {
#endif

	// POSIX operating-systems-specific definitions.
#include <sys/time.h>
#include <time.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

	//static inline void ctime_s (char* cp, unsigned u, time_t const* t)	{ strncpy (cp, ctime(t), u); }

#define GetLastError_NonOsDependent()					errno

#define Assert_NonOsDependent(expr)						{ assert(expr); }

#define Sleep_NonOsDependent(dMilliseconds)				{ usleep(1000 * (dMilliseconds)); } // Uses units of microseconds.

#define _DECL

#define _EXTERN

#if !defined (errno_t)
	typedef int errno_t;
#endif // not defined (errno_t)

	typedef void *HMODULE;
	typedef void *PVOID;

	// Basic numeric types.
#include <stdint.h>
#define U64BIT											uint64_t
#define S64BIT											int64_t
#ifndef USE_DDC_LIBRARY
#define U32BIT											uint32_t
#define S32BIT											int32_t
#define U16BIT											uint16_t
#define S16BIT											int16_t
#define U8BIT											uint8_t
#define S8BIT											char
#define BOOLEAN											unsigned char
#endif // USE_DDC_LIBRARY
#define BOOL											int
#define DWORD											uint32_t
#define WORD											uint16_t

#define LHANDLE											PVOID
#define U64BIT_PTR										PUINT64
#define P_VOID											PVOID
#define P_S8BIT											INT8*


#define MAIN											main
#define ARG_CHAR										char
#define TCHAR											char
#define STRING											string
#define TEXT(str)										(str)
#define STRCMP											strcmp
#define SPRINTF											sprintf
#define CERR											cerr

#define PAUSE_BEFORE_EXIT								{ char caTemp[2]; printf ("\n(Press any key to exit.)\n"); fgets (caTemp, sizeof(caTemp), stdin); }

#define PAUSE_FOR_INSTRUCTIONS							{ \
															char caTemp[2]; \
															printf ("\n(Press Esc to abort, or any other key to continue.)\n"); \
															fgets (caTemp, sizeof(caTemp), stdin); \
															if (char_ESC == caTemp[0])	iOperationalCommandIndex = s_iOperationalCommandsCount; /* Force the command loop to end. */ \
														}

#define PAUSE_BEFORE_MOVING_ON							{ char caTemp[2]; printf ("\n(Press any key to exit.)\n"); fgets (caTemp, sizeof(caTemp), stdin); }

	// Open the file whose path is given in given mode, and properly set given pointer to point it.
	// Return the result of the operation in the pointed error variable: 0  in case of success; otherwise, in WIN32 return the error returned by fopen_s, and in Unix return -1.
#define OPEN_FILE(/* FILE** */fppFile, /* const char* */szpFilePath, /* const char* */ szpMode, /* errno_t* */ errp) \
														{ \
															(*(fppFile)) = fopen ((szpFilePath), (szpMode)); \
															err = ( (*(fppFile)) ? 0 : -1 ); \
														}

	// Load the library whose name is given.
	// Return the HMODULE of the loaded library, or null in case of failure.
#define LOAD_LIBRARY(/* const char* */ szLibraryName) \
														(dlopen ( (szLibraryName), (RTLD_NOW | RTLD_LOCAL) ) )

#define PRINT_LAST_ERROR() \
														{ printf ("%s", dlerror ()); }

	// Set given pointer of given program to the function in given module whose name is given.
#if defined (__GNUC__) && (defined(__i386) || defined(__amd64__))
#define GET_FUNCTION_ADDRESS(/* const char[] string */szProgram, /* const HMODULE */hmLibrary, /* const char* */szFuncName, /* void** */vppFuncAddress) \
														{ \
															(*(vppFuncAddress)) = (dlsym ((hmLibrary), (szFuncName))); \
															if ( ! (*(vppFuncAddress)) ) \
															{ \
																printf ("%s.LoadFunction.Tried: name - %s\n", (szProgram), (szFuncName)); \
																/* Also QNX6/x86, GNU C++ 4.3.3:  S16BIT function(void) is decorated as "_Z<strlen(name)><name>v". */ \
																int iNameLength = strlen (szFuncName); \
																char szNameBuffer[8 + strlen (szFuncName)]; \
																sprintf (szNameBuffer, "_Z%u%sv", iNameLength, (szFuncName)); \
																(*(vppFuncAddress)) = dlsym ((hmLibrary), szNameBuffer); \
																if ( ! (*(vppFuncAddress)) ) \
																{ \
																	printf ("%s.LoadFunction.Tried: name - %s\n", (szProgram), szNameBuffer); \
																	sprintf (szNameBuffer, "_Z%u%si", iNameLength, (szFuncName)); /* With one integer parameter the decoration becomes: "_Z<strlen(name)><name>i". */ \
																	(*(vppFuncAddress)) = dlsym ((hmLibrary), szNameBuffer); \
																	if ( ! (*(vppFuncAddress)) ) \
																	{ \
																		printf ("%s.LoadFunction.Tried: name - %s\n", (szProgram), szNameBuffer); \
																	} \
																} \
															} \
														}
#else // not ( defined (__GNUC__) && (defined(__i386) || defined(__amd64__)) )
#define GET_FUNCTION_ADDRESS(/* const char[] string */szProgram, /* const HMODULE */hmLibrary, /* const char* */szFuncName, /* void** */vppFuncAddress) \
														{ \
															(*(vppFuncAddress)) = (dlsym ((hmLibrary), (szFuncName))); \
														}
#endif // defined (__GNUC__) && (defined(__i386) || defined(__amd64__))

	// Min, max aren't normally defined for c++ (should be templates).
#if ( (!defined(min)) && (!defined(MIN_REDEFINED)) )
#define min(_a,_b)										((_a) <= (_b) ? (_a):(_b))
#define MIN_REDEFINED
#endif // min

#if ( (!defined(max)) && (!defined(MAX_REDEFINED)) )
#define max(_a,_b)										((_a) >= (_b) ? (_a):(_b))
#define MAX_REDEFINED
#endif // max

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

/* Same as above */
#ifndef _STLD_RETURN_DEFINED_
typedef S16BIT STLD_RETURN;
#	define _STLD_RETURN_DEFINED_
#endif /*_BSA_STATUS_DEFINED_*/


#ifdef __cplusplus
}
#endif

#endif // LINUX_DMA


#endif // BRM_TYPES_H__
