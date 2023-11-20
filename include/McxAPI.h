#ifndef McxAPIExport_INCLUDED
#define McxAPIExport_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


#define U64BIT											UINT64
#define S64BIT											INT64
#define S32BIT											INT32
#define U32BIT											UINT32
#define U16BIT											UINT16
#define S16BIT											INT16
#define S8BIT											char
#define U8BIT											UINT8

//#define sitalMaximum_DEVICES													64U/*32U temporary- 32 requires alloc*/			///< Maximum number of devices in the system.
//
//#define MAX_NUMBER_SUPPORTED_USB_DEVICES										127			// <QuickUSB_UserGuide.pdf> puts the limit of 127 (see the documentation for function QuickUsbFindModules).
//#define NUMBER_OF_DEVICE_MODULES												2			// Number of modules per device.
//#define NUMBER_OF_RS485_LINES_PER_MODULE										2			// Number of RS422 lines per module.
//#define SIZE_OF_RS485_TX_BUFFER													1008		// "RS422/485 UART" in the Sital Tester-1553 User Manual.	
//#define SIZE_OF_RS485_RX_BUFFER													1024		// "RS422/485 UART" in the Sital Tester-1553 User Manual.
//#define MAX_DEVICE_NAME_LENGTH													16			// Maximum length of device name restriction by the USB driver (not including the terminating zero character), see function QuickUsbFindModules in <QuickUSB_UserGuide.pdf>.
//#define MAX_DEVICE_DESCRIPTOR_LENGTH											128			// Maximum length of device descriptor restriction by the USB driver (not including the terminating zero character), see function QuickUsbGetStringDescriptor in <QuickUSB_UserGuide.pdf>.
//#define MAX_FRAMES_PER_MODULE													100			// Maximum number of frames that can be defined for a single device.
//#define MAX_MESSAGES_PER_MODULE													1024		// Maximum number of messages that can be defined for a single device.
//#define MAX_MESSAGES_PER_FRAME													64			// Maximum number of messages that can be defined for a frame.

// 64 is the max value restricted by the current size of the device Memory
// IMPORTANT - Changing this constant changes the image of the device memory, consult OferH before changing.
#define MAX_FRAME_TRANSMIT_TIME													10000		// Maximum number of milliseconds that a single transmission cycle of a frame may take.
#define SIZE_OF_TAILS_TABLE														32			// The size in words of the tails table.	
#define SIZE_OF_UUT_DATA_ENTRY													32			// The size in words of each data-to/from-UUT entry that's defined by the MIL-STD-1553 standard.
#define SIZE_OF_UUT_DATA_ENTRY_H009												15			// The size in words of each data-to/from-UUT entry that's defined by the H009 standard.	
#define TesterDll_MAX_TIME_BETWEEN_WORD_MONITOR_READING_REQUESTS				10000		// In order to make TesterDll maintain an up-to-date image of the word-monitor for some module of the Tester device, read requests must incessantly arrive.
///< This is the maximum time in milliseconds that may pass between two successive calls, so that TesterDll won't suspend the update of its image.
// still, even in case of suspension, update is resumed immediately when function TesterDll_Module_GetWordMonitor() is called for this module in the next time.
#define TesterDll_DEFAULT_SLEEP_TIME_ALONG_FRAME_TX								1			/*The default time interval in milliseconds for which the worker thread shall be suspended between iterations while monitoring frame tx or word-monitor reading.
	 When running a frame, suspension is made while waiting for the current cycle to end.
	 When reading word-monitor data, suspension is made while waiting for word-monitor updates.
	 WARNING: must be greater than zero!*/
#define TesterDll_DEFAULT_SLEEP_TIME_INCREMENT_WHILE_IDLE						10			// The default measure in milliseconds in which to increment the time interval for which the worker thread shall be suspended between iterations while having no frame tx nor word-monitor reading to monitor.
	// This gradual increment is used in order to shorten to minimum the inter-frame gap and quickly respond to next frame run requests in case the user is successively running different frames.
#define TesterDll_DEFAULT_INITIAL_SLEEP_TIME_WHILE_IDLE							100			// The default initial time interval in milliseconds for which the worker thread shall be suspended between iterations while having no frame tx nor word-monitor reading to monitor.
	// WARNING: must be greater than zero!
#define TesterDll_DEFAULT_MAX_SLEEP_TIME_WHILE_IDLE								1000		// The default maximum time interval in milliseconds for which the worker thread shall be suspended between iterations while having no frame tx nor word-monitor reading to monitor.
	// WARNING: must be greater than zero!
#define TIME_BETWEEN_SUCCESSIVE_MESSAGE_COMPILATIONS							500			// The maximum time in milliseconds to pause the message-compilation process when there aren't enough new word-monitor entries for compiling the largest possible message.
#define MAX_ERROR_INJECTION_MESSAGE_INDEX										3			// The maximum index of message within a running frame where an error should be injected.
#define MAX_ERROR_INJECTION_WORD_INDEX											35			// The maximum index of word within the target message within a running frame where an error should be injected.
#define MIN_MESSAGE_LENGTH_ERROR_INJECTION_VALUE								-32			// The minimum error value for an injected message length error.
#define MAX_MESSAGE_LENGTH_ERROR_INJECTION_VALUE								+31			// The maximum error value for an injected message length error.
#define MAX_CONTIGUOUS_DATA_ERROR_INJECTION_VALUE								31			// The maximum error value for an injected contiguous data error.
#define MAX_RT_TO_RT_TIMEOUT_ERROR_INJECTION_VALUE								31			// The maximum error value for an injected RT-to-RT timeout error.
#define MAX_ZERO_CROSSING_ERROR_INJECTION_VALUE									39			// The maximum error value for an injected zero crossing error.
#define MIN_ZERO_CROSSING_ERROR_INJECTION_VALUE2								-8			// The minimum error value #2 for an injected zero crossing error.
#define MAX_ZERO_CROSSING_ERROR_INJECTION_VALUE2								+7			// The maximum error value #2 for an injected zero crossing error.
#define MIN_INTERVAL_BETWEEN_SUCCESSIVE_FPGA_RELOAD_TRIALS						5000		// The minimum interval (milliseconds) required between two successive FPGA reload trials (such trials are performed in case abrupt FPGA unload is detected).

// Device initialization: Modes
#define AccessMode_BC												0x0000U		// BC - Bus Controller. 
#define AccessMode_RT												0x0001U		// RT - Remote Terminal. 
#define AccessMode_TEST												0x0002U		// Test. 	
// UserCode Options
#define MIL_STD_1553_AND_PP194										0x0000			
#define H009														0x0001			
#define MultiRT														0x0002	
#define MIL_STD_1553												0x0004	
#define EBR_1553													0x0008
#define DIGIBUS_F16													0x0016

// Element Option
#define Protocol_PP194_Element_Option								0x0004

#define DataBlockMode_32_WORDS										0x0000U	//R/W
#define DataBlockMode_64_WORDS										0x0010U	//R/W
#define DataBlockMode_256_WORDS										0x0020U	//R/W
#define DataBlockMode_1K_WORDS										0x0030U	//R/W
#define DataBlockMode_4K_WORDS										0x0040U	//R/W
#define DataBlockMode_16K_WORDS										0x0050U	//R/W
#define DataBlockMode_RESERVED										0x0060U	//R/W
#define DataBlockMode_GLOBAL										0x0070U	//R/W

#define MAX_ELEMENTS_PER_BUSLIST												256		// User can allocate 256  elements of 4 words (total of 1024) in a buslist.

#define mcx_NO_ERROR												0x0000
#define mcx_PARITY_ERROR											0x1000
//#define mcx_WORD_LENGTH_ERROR										0x2000
#define mcx_BIPHASE_ERROR											0x3000
#define mcx_SYNC_ERROR												0x4000
//#define mcx_MESSAGE_LENGTH_ERROR									0x5000
#define mcx_ZERO_CROSSING_ERROR										0x8000
#define mcx_mRT_SWIFT_RESPONSE_ERROR								0xC000
#define mcx_NOISER_ERROR											0xF000

#define mcx_ERRINJ_DEFINITION										0x0044 
#define mcx_ERRINJ_PARAMETERS										0x0045

// WORD MONITOR Returned codes
#define mcx_wm_WRONG_CMD_SYNC					0x00000001
#define mcx_wm_INVALID_WORD						0x00000002
#define mcx_wm_NO_RESPONSE						0x00000004
#define mcx_wm_LOW_WORD_COUNT_ERROR				0x00000008
#define mcx_wm_HIGH_WORD_COUNT_ERROR			0x00000010
#define mcx_wm_BUS_SWITCHED_ERROR				0x00000040				// During message
#define mcx_wm_LOST_SYNC_ON_BAD_TIME_SYMBOL		0x00000080
#define mcx_wm_DATA_OVERRUN						0x00000100
#define mcx_wm_CONTIGUOUS_DATA					0x00000200
#define mcx_wm_NON_CONTIGUOUS_DATA				0x00000400
#define mcx_wm_NON_COMMON_MESSAGE_FORMAT		0x00000800				// Not a common 1553 message format
#define mcx_wm_NOT_SYNCED						0x00001000				// If bus is corrupted and thus not synced, hint the user not to take this message content too seriously

// WORD MONITOR Descriptors
#define mcx_wm_BUS_A							0x00010000
#define mcx_wm_BUS_B							0x00000000
#define mcx_wm_PP194							0x00020000

// SIMULATOR ELEMENT | MESSAGE FINDINGS
#define mcx_MessageFindings_INVALID_WORD									0x0001 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_1553_INVALID_WORD								0x0001 // With MIL-STD-1553 messages: bit turned off in case of positive findings.
#define mcx_MessageFindings_PP194_MANCHESTER_OR_PARITY_ERROR				0x0001 // With PP-194 messages: bit turned off in case of positive findings and on in case the RIU responded with Manchester or parity error.
#define mcx_MessageFindings_INCORRECT_SYNC_TYPE								0x0002 // Wit turned off in case of positive findings.
#define mcx_MessageFindings_1553_INCORRECT_SYNC_TYPE						0x0002 // With MIL-STD-1553 messages: bit turned off in case of positive findings.
#define mcx_MessageFindings_PP194_STATUS_PHASE_ERROR						0x0002 // With PP-194 messages: bit turned off in case of positive findings and on in case of RIU status phase error.
#define mcx_MessageFindings_WORD_COUNT_ERROR								0x0004 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_1553_WORD_COUNT_ERROR							0x0004 // With MIL-STD-1553 messages: bit turned off in case of positive findings.
#define mcx_MessageFindings_PP194_DATA_PHASE_ERROR							0x0004 // With PP-194 messages: bit turned off in case of positive findings and on in case of RIU data phase error.
#define mcx_MessageFindings_BAD_RT_ADDRESS									0x0008 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_GOOD_DATABLOCK_RECEIVED							0x0010 // Bit turned off in case there are errors in the received data block.
#define mcx_MessageFindings_1553_GOOD_DATABLOCK_RECEIVED					0x0010 // With MIL-STD-1553 messages: bit turned off in case there are errors in the received data block.
#define mcx_MessageFindings_PP194_BOTH_PHASES_SUCCEEDED						0x0010 // With PP-194 messages: bit turned off in case of negative findings and on in case both phases ended with no error.
#define mcx_MessageFindings_MESSAGE_RETRIES_NUM								0x0060 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_UNMASKED_STATUSBIT_SET							0x0080 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_LOOPBACK_FAILED									0x0100 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_RESPONSE_TIMEOUT								0x0200 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_1553_RESPONSE_TIMEOUT							0x0200 // With MIL-STD-1553 messages: bit turned off in case of positive findings.
#define mcx_MessageFindings_PP194_NO_PROPER_RESPONSE						0x0200 // With PP-194 messages: bit turned off in case of positive findings and on in case the RIU didn't respond properly.
#define mcx_MessageFindings_FORMAT_ERRORS									0x0400 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_STATUS_SET										0x0800 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_MESSAGE_ERROR									0x1000 // Bit turned off in case of positive findings, otherwise check bits 10, 9, 8, 3, 2, 1, 0 to discover the exact cause of error.
#define mcx_MessageFindings_TX_BUS											0x2000 // Bit turned off in case message has been transmitted on bus A, and vice versa.
#define mcx_MessageFindings_START_OF_MESSAGE								0x4000 // Bit turned off in case of positive findings.
#define mcx_MessageFindings_END_OF_MESSAGE									0x8000 // Bit turned ON  in case of positive findings.
//#define mcx_MessageFindings_SuccessfulTx									0x8000 // The findings in case of successful message transmission, NOT taking in account the TX-bus bit which doesn't indicate errors.
#define mcx_MessageFindings_UNSET											0xFFFF  // Initialization value, before actual findings recorded (note that since some possible errors contradict one another, the actual message findings can never be 0xFFFF).
		
// MIL-STD-1553 and PP194 Message Types
#define UnParsed					0
#define BC2RT						10						
#define RT2BC						20
#define RT2RT						30
#define BC2BCST						40
#define RT2BCST						50
#define BCST2RT_Invalid				60
#define BCST2BC_Invalid				70

#define BC2RT_Mode_No_Data			11
#define BC2RT_Mode_With_Data		12
#define RT2BC_Mode_No_Data			21				
#define RT2BC_Mode_With_Data		22				
#define RT2RT_Mode_No_Data			31			
#define RT2RT_Mode_With_Data		32				
#define BC2BCST_Mode_No_Data		41
#define BC2BCST_Mode_With_Data		42
#define RT2BCST_Mode_No_Data		51
#define RT2BCST_Mode_With_Data		52
#define BCST2RT_Mode_No_Data		61
#define BCST2BCST_Mode_No_Data		62
#define BCST2BC_Mode_No_Data		71

//#define INVALID_BCST2BC			-10
#define INVALID_RT2RT				-11

//#define PP194						194
#define BC2RT_194					19401						
#define RT2BC_194					19402

// Message Options 
#define TX_BUS_A					0x80
#define TX_BUS_B					0x0
#define RT2RT_FORMAT				0x1
#define PP194_FORMAT				0x4

//Arinc429
//typedef struct mcxA429ChannelInformation
//{
//    /// The size in bytes of this structure.
//    /// Caller must set this field to sizeof(stla429ChannelInformationStructure).
//    /// This is to prevent buffer overwrite when compilers are incompatible or definitions change.
//    U32BIT  dwStructureSize;
//    U32BIT dwUserTag;        // Arbitrary user provided value
//    union {
//        struct /*characteristics*/ {
//           U32BIT channelIsAvailable : 1;    // true = available for use
//           U32BIT channelRunning : 1;        // true = running, false = not running
//           U32BIT channelFailure : 1;        // true = failure detected
//           U32BIT channelIsTX : 1;           // true = configured as TX, false = as RX
//           U32BIT channelIsHighSpeed : 1;    // true = configured for high speed, else low speed
//           U32BIT channelSupportsTX : 1;     // true = can be configured as TX
//           U32BIT channelSupportsRX : 1;     // true = can be configured as RX
//           U32BIT channelSupportsHighSpeed : 1;  // true = can be configured for high speed
//           U32BIT channelSupportsLowSpeed : 1;   // true = can be configured for low speed
//        };
//        U32BIT  dwFlags; // above struct as integer
//    };
//    U32BIT  dwTransferSize;   // Size of transfer buffer required for bulk RX
//    U32BIT  dwCardNumber;     // Card number on which channel is located
//    U32BIT  dwReserved1;      // Padding
//} mcx_A429ChannelInfo;

typedef struct mcxMsgStruct
{
	U16BIT cmd;			// command to be send or recieve
	U16BIT cmd2;		// 2nd command in case of RT to RT, should be transmite command.
	U16BIT* data;		// data of the command
	U16BIT dataSize;	// data size
	U16BIT* BSW;		// bit status word
	U16BIT* rtStatus;	// return status from RT
	U16BIT* rtStatus2;	// return status from 2nd RT in case of RT to RT
	bool emulateRt;		// emulate rt flag
}mcx_MsgStruct;


// Following bits are same for TX and RX modes:
#define MCX_A429_CFG_HIGH_RATE          0x0001  ///< Data rate: 100 KHz
#define MCX_A429_CFG_LOW_RATE           0x0000  ///< Data rate: 12.5 KHz
#define MCX_A429_CFG_MASK_RATE          0x0001
#define MCX_A429_CFG_PARITY_NONE        0x0000  ///< Data parity: none. MSB can be used as data.
#define MCX_A429_CFG_PARITY_EVEN        0x0002  ///< Data parity: even
#define MCX_A429_CFG_PARITY_ODD         0x0006  ///< Data parity: odd
#define MCX_A429_CFG_MASK_PARITY        0x0006  //   Mask for parity bits
// NOTE - the following 32 bits constants are relevant for PCI (PMC Tester). 
#define MCX_A429_NUMBER_OF_WORDS_MASK   0x00FF0000  //   Number of words in FIFO mask - Bits 16-23
#define MCX_A429_FIFO_FULL		        0x01000000  //   FIFO full
#define MCX_A429_FIFO_EMPTY		        0x02000000  //   FIFO empty
#define MCX_A429_RX_LABEL_TABLE_READY	0x04000000  //   Labels table ready

// Following bits apply only for RX mode:
#define MCX_A429_CFG_RX_LABEL_MATCH     0x0008  ///< enable label matching
#define MCX_A429_CFG_MASK_RX_LABELS     0x0008
#define MCX_A429_CFG_RX_DECODER_ENABLE  0x0010
#define MCX_A429_CFG_RX_DECODER_DISABLE 0x0000
#define MCX_A429_CFG_MASK_RX_DECODER    0x0070

#define MCX_A429_CARD_DISABLE_INTERNAL_LOOPBACK          0x00000000  // sets the card to disable internal loopback, external Arinc429 Tx Rx data is accepted
#define MCX_A429_CARD_ENABLE_INTERNAL_LOOPBACK           0x00000001  // sets the card to enable internal loopback, external Arinc429 Tx Rx data is not accepted

// Cyber attack types, for elaboration, view documentation 
#define mcx_No_Attack					0x0000			// no Cyber-attack mode
#define mcx_Attack_Mode1				0x0001			// Time delayed attack mode with 65 ms steps of delay
#define mcx_Attack_Mode2				0x0002			// Time delayed attack mode with 100 us steps of delay
#define mcx_Attack_Mode3				0x0003			// Trigger Message delay mode

// Request types for Server and Client
#define MCX_CLIENT						0x0000			
#define MCX_SERVER						0x0001			

// Device Functions
extern S16BIT mcx_SetDriverBaseAddress(U16BIT deviceId, U32BIT MemoryBase, U32BIT RegisterBase);
extern S16BIT mcx_GetDriverBaseAddress(U16BIT deviceId, U32BIT* MemoryBase, U32BIT* RegisterBase);
extern S16BIT mcx_Initialize (U16BIT deviceId, U16BIT protocol);
extern S16BIT mcx_ReloadHW(U16BIT deviceId, U16BIT protocol);
extern S16BIT mcx_Read(U16BIT deviceId, U16BIT address, WORD bufferSize, WORD* buffer);
extern S16BIT mcx_Write(U16BIT deviceId, U16BIT address, WORD bufferSize, WORD* buffer);
extern S16BIT mcx_Create_BusList (U16BIT deviceId, U16BIT busList);
extern S16BIT mcx_Create_BusList_Element (U16BIT deviceId, U16BIT element, U16BIT command, U16BIT options, U16BIT Command2, U16BIT StatusWord1, U16BIT StatusWord2);
extern S16BIT mcx_Create_BusList_Element1 (U16BIT deviceId, U16BIT element, U16BIT command, U16BIT options);
extern S16BIT mcx_Create_Element_DataBlock (U16BIT deviceId, U16BIT dataBlock, U16BIT dataBlockMode, U16BIT* buffer, U16BIT bufferSize);
extern S16BIT mcx_Map_DataBlock_To_Element (U16BIT deviceId, U16BIT element, U16BIT dataBlock);
extern S16BIT mcx_Map_Element_To_BusList (U16BIT deviceId, U16BIT busList, U16BIT element);
extern S16BIT mcx_Start (U16BIT deviceId, U16BIT busList, U16BIT numberOfIterations);
extern S16BIT mcx_EnableRts (U16BIT deviceId, U32BIT rtsVector); 
extern S16BIT mcx_GetDescriptors(U16BIT deviceId, S8BIT* deviceName, S8BIT* deviceManufacturer, S8BIT* deviceFirmware, S8BIT* deviceSerial);
extern S16BIT mcx_DevicePassiveTimeStarted(U16BIT deviceId, U16BIT* isFirstPassive);
extern S16BIT mcx_Stop (U16BIT deviceId);
extern S16BIT mcx_Stop2 (U16BIT deviceId);
extern S16BIT mcx_EnableRius(U16BIT deviceId, U16BIT riusVector);
extern S16BIT mcx_Get_Element_Results(U16BIT deviceId, U16BIT busList, U16BIT elementIndex, U16BIT* blockStatusWord, WORD* buffer, U16BIT bufferSize, U16BIT* status1, U16BIT* status2, U16BIT* tag);
extern S16BIT mcx_Element_DataBlock_Read (U16BIT deviceId, U16BIT wDataBlock, U16BIT* buffer, U16BIT bufferSize); 
extern S16BIT mcx_SetFpgaFileDirectory (U16BIT deviceId, S8BIT* fpgaFileDir);
extern S16BIT mcx_SetFrameTime(U16BIT deviceId, U32BIT microSeconds);
extern S16BIT mcx_MapDevices(U16BIT* numberOfDevices);
extern S16BIT mcx_GetDevices(U16BIT deviceId, void* DevRoot);
extern S16BIT mcx_GetNumberOfDevices();
extern S16BIT mcx_GetIsArinc429(U16BIT deviceId);
extern S16BIT mcx_Free (U16BIT deviceId);
extern S16BIT mcx_FreeBusList (U16BIT deviceId, U16BIT busList);
extern S16BIT mcx_Get_Element_Results_PP194(U16BIT deviceId, U16BIT busList, U16BIT elementIndex, U16BIT* blockStatusWord, U16BIT* buffer, U16BIT bufferSize, U16BIT* status1, U16BIT* status2, U16BIT* tag);
extern S16BIT mcx_Set_Error(U16BIT deviceId, U16BIT errorType, U16BIT messageNumber, U16BIT wordNumber, S32BIT injectionParameters, S16BIT zXDistortion);
extern S16BIT mcx_SetUserPort (U16BIT deviceId, U16BIT userPort);
extern S16BIT mcx_GetUserPort (U16BIT deviceId, U16BIT* userPort);
extern S16BIT mcx_GetCurrentFrameNumber(U16BIT deviceId, U16BIT* currFrameNumber);
extern S16BIT mcx_Element_SetGap(U16BIT deviceId, U16BIT elementId, U16BIT gap);

extern S16BIT mcx_Start_RateMode (U16BIT deviceId, U16BIT busList, U16BIT numberOfIterations);
extern S16BIT mcx_Element_SetRate(U16BIT deviceId, U16BIT elementId, U16BIT rate, U16BIT skew, U16BIT elementSpacing);

extern S16BIT mcx_SetRTsResponseDelay(U16BIT deviceId, U16BIT rtResponseHalfUs, U16BIT respondAnyway); 

extern S16BIT mcx_Send_AsynchMsg1(U16BIT deviceId, U16BIT command, U16BIT options, U16BIT statusWord, U16BIT* buffer, U16BIT bufferSize);
extern S16BIT mcx_Send_AsynchMsg2(U16BIT deviceId, U16BIT command, U16BIT options, U16BIT statusWord, U16BIT* buffer, U16BIT bufferSize);
extern S16BIT mcx_Get_Asynch1_Results(U16BIT deviceId, U16BIT* blockStatusWord, WORD* buffer, U16BIT bufferSize, U16BIT* status, U16BIT* tag);
extern S16BIT mcx_Get_Asynch2_Results(U16BIT deviceId, U16BIT* blockStatusWord, WORD* buffer, U16BIT bufferSize, U16BIT* status, U16BIT* tag);

extern S16BIT mcx_wm_GetNextSymbol(U16BIT deviceId, U32BIT* swPointer, WORD* descriptor, WORD* data, WORD* bufferSize);
extern S16BIT mcx_wm_GetNextMsg_H009(U16BIT deviceId, U32BIT* swPointer, WORD* command, WORD* isCommandValid, WORD* data, WORD* bufferSize, U32BIT* BSW, U64BIT* tTag);
extern S16BIT mcx_wm_GetNextMsg_1553_194(U16BIT deviceId, S16BIT* msgType , U32BIT* swPointer, WORD* rxCommand, WORD* txCommand, WORD* data, WORD* bufferSize, WORD* rxStatus, WORD* txStatus, U32BIT* BSW, U64BIT* tTag);
extern S16BIT mcx_wm_collectMonitor(U16BIT deviceId);

extern S16BIT mcx_wm_GetRT_ResponseTime(U16BIT deviceId, U16BIT rt,S32BIT* responseOnBusA, S32BIT* responseOnBusB);

extern S16BIT mcx_SetCyberAttack(U16BIT deviceId, U16BIT cyberAttackType, U16BIT triggerCommand);

extern S16BIT mcx_pTDR_GetRawData(U16BIT deviceId, U16BIT* buffer, U16BIT bufferSize);
extern S16BIT mcx_pTDR_Enable(U16BIT deviceId, U16BIT enable, U16BIT options);
extern S16BIT mcx_Restart (U16BIT deviceId, U16BIT busList);
extern S16BIT mcx_BusList_UpdateData (U16BIT deviceId, U16BIT busList, S32BIT* updatedFrame);
extern S16BIT mcx_GetSimulatorErrorsDescription(U32BIT bsw, S8BIT* errorsDescription, U16BIT protocol);
extern S16BIT mcx_Get_Version (U16BIT deviceId, U16BIT* version);
extern S16BIT mcx_Get_EnabledRts (U16BIT deviceId, U32BIT* rtsVector);
extern S16BIT mcx_Close (U16BIT deviceId);
extern S16BIT mcx_Element_DataBlock_Write (U16BIT deviceId, U16BIT element, U16BIT wDataBlock, U16BIT* buffer, U16BIT bufferSize);
extern S16BIT mcx_Element_DataBlock_Read (U16BIT deviceId, U16BIT wDataBlock, U16BIT* buffer, U16BIT bufferSize); 
extern S16BIT mcx_Delete_BusList (U16BIT deviceId, U16BIT busList);
extern S16BIT mcx_Delete_BusList_Element (U16BIT deviceId, U16BIT element);
extern S16BIT mcx_Delete_Element_DataBlock (U16BIT deviceId, U16BIT dataBlock);
extern S16BIT mcx_UnMap_DataBlock_From_Element (U16BIT deviceId, U16BIT element, U16BIT dataBlock);
extern S16BIT mcx_UnMap_Element_From_BusList (U16BIT deviceId, U16BIT busList, U16BIT element);
extern S16BIT mcx_Grip2_GetTemperature(U16BIT deviceId, S16BIT* temperature);
extern S16BIT mcx_GetReturnCodeDescription(S16BIT errorCode, S8BIT* errorCodeDescription);
extern S16BIT mcx_GetMonitorErrorsDescription(U32BIT bsw, S8BIT* errorsDescription);
extern S16BIT mcx_GetTemperature(U16BIT deviceId, S16BIT* temperature);

extern S16BIT mcx_GetLicenseDescription(U16BIT deviceId, S8BIT* description);

extern S16BIT mcx_Eth_SetupIpType(U16BIT requestType);
extern S16BIT mcx_Eth_SetServerIPsList(U16BIT serversNumber, S8BIT* ips);

extern S16BIT mcx_SetConfigurationRegisters(U16BIT deviceId, U16BIT configRegisters, U16BIT configRegisters2);
extern S16BIT mcx_GetConfigurationRegisters(U16BIT deviceId, U16BIT* configRegisters, U16BIT* configRegisters2);

extern S16BIT mcx_SetupRS422 (U16BIT deviceId, U16BIT line, U16BIT bitsCount, U16BIT parity, U16BIT stopBits, U16BIT rateDivider);
extern S16BIT mcx_SendRS422 (U16BIT deviceId, U16BIT line, U16BIT length, WORD* buffer);
extern S16BIT mcx_RS485_Setup (U16BIT moduleId, U16BIT line, U16BIT bitsCount, U16BIT parity, U16BIT stopBits, U16BIT rateDivider, U16BIT rxTxMode, U16BIT* offset);
extern S16BIT mcx_RS485_Put (U16BIT moduleId, U16BIT line, U16BIT length, WORD* buffer);
extern S16BIT mcx_RS485_Get (U16BIT moduleId, U16BIT line, U16BIT* offset, U16BIT length, WORD* buffer);
extern S16BIT mcx_RS485_GetNumberOfReceivedWords (U16BIT moduleId, U16BIT line, U16BIT offset, U16BIT* length);
extern S16BIT mcx_RS485_GetStatus (U16BIT moduleId, U16BIT * line0, U16BIT * line1);

//extern S16BIT mcx_A429_Channel_GetCount(U32BIT* numOfChannels);
//extern S16BIT mcx_A429_Channel_Open(U16BIT channel, mcx_A429ChannelInfo* channelInfo);
//extern S16BIT mcx_A429_Setup(U16BIT device);
//extern S16BIT mcx_A429_Channel_GetInformation(U16BIT channel, mcx_A429ChannelInfo* channelInfo);
//extern S16BIT mcx_A429_Channel_Close(U16BIT channel);
//extern S16BIT mcx_A429_Channel_SetConfigRegister(U16BIT channel, U32BIT chanFlags);
//extern S16BIT mcx_A429_Channel_GetConfigRegister(U16BIT channel, U32BIT* chanFlags);
//extern S16BIT mcx_A429_Channel_GetStatusRegister(U16BIT channel, U32BIT* chanStats);
//extern S16BIT mcx_A429_Receive (U16BIT channel, U32BIT bufferSize, U32BIT* buffer, U32BIT* numberOfReceivedWords);
//extern S16BIT mcx_A429_Send (U16BIT channel, U32BIT bufferSize, U32BIT* buffer, U32BIT* numberOfWrittenWords);
//extern S16BIT mcx_A429_GetRxWordsPending(U16BIT channel, U32BIT* numberOfWords);
//extern S16BIT mcx_A429_Channel_Reset(U16BIT channel, U32BIT chanFlags);
//extern S16BIT mcx_A429_Card_SetConfiguration(U32BIT cardFlags);

extern S16BIT mcx_GetPciProductIds(S32BIT* pIds, S16BIT* numberOfCardsFound);
extern S16BIT mcx_GetPciMake(S16BIT card, S16BIT* make);

//extern S16BIT mcx_A429_Pci_Channel_GetCount(U16BIT card, U32BIT* numOfChannels);
//extern S16BIT mcx_A429_Pci_Tx_Rx_Channel_Count(U16BIT card, U32BIT* numOfTxChannels, U32BIT* numOfRxChannels);
//extern S16BIT mcx_A429_Pci_Channel_Open(U16BIT card, U16BIT channel, mcx_A429ChannelInfo* channelInfo);
//extern S16BIT mcx_A429_Pci_Channel_GetInformation(U16BIT card, U16BIT channel, mcx_A429ChannelInfo* channelInfo);
//extern S16BIT mcx_A429_Pci_Channel_Close(U16BIT card, U16BIT channel);
//extern S16BIT mcx_A429_Pci_Channel_SetConfigRegister(U16BIT card, U16BIT channel, U32BIT chanFlags, bool manage = false, U32BIT manFreq = 0);
//extern S16BIT mcx_A429_Pci_Channel_GetConfigRegister(U16BIT card, U16BIT channel, U32BIT* chanFlags);
//extern S16BIT mcx_A429_Pci_Channel_GetStatusRegister(U16BIT card, U16BIT channel, U32BIT* chanStats);
//extern S16BIT mcx_A429_Pci_Receive (U16BIT card, U16BIT channel, U32BIT bufferSize, U32BIT* buffer, U32BIT* numberOfReceivedWords);
//extern S16BIT mcx_A429_Pci_Send (U16BIT card, U16BIT channel, U32BIT bufferSize, U32BIT* buffer, U32BIT* numberOfWrittenWords);
//extern S16BIT mcx_A429_Pci_GetRxWordsPending(U16BIT card, U16BIT channel, U32BIT* numberOfWords);
//extern S16BIT mcx_A429_Pci_Channel_Reset(U16BIT card, U16BIT channel, U32BIT chanFlags);
//extern S16BIT mcx_A429_Pci_Card_SetConfiguration(U16BIT card, U32BIT cardFlags);

// Not verified functions
extern S16BIT mcx_wm_Stop_H009(U16BIT deviceId);
//extern S16BIT mcx_Get_DataBlock_NumberOfWordsToRead (U16BIT element, U16BIT dataBlock, U16BIT* numWordsToRead);
//extern S16BIT mcx_Get_DataBlock_NumberOfWordsToWrite (U16BIT element, U16BIT dataBlock, U16BIT* numWordsToWrite);

extern S16BIT mcx_SetIntEnable (U16BIT deviceId, U16BIT interrupsEnabled); 
extern S16BIT mcx_GetIntVector (U16BIT deviceId, U16BIT* interruptsStatuses);
extern S16BIT mcx_SetTime (U16BIT deviceId, U64BIT time, USHORT reg14 = 0, USHORT reg15 = 0, USHORT reg16 = 0, USHORT REG17 = 0);
extern S16BIT mcx_GetTime (U16BIT deviceId, U64BIT* time);
extern S16BIT mcx_SetTimeResolution (U16BIT deviceId, U16BIT timeResolution); 
extern S16BIT mcx_GetTimeResolution (U16BIT deviceId, U16BIT* timeResolution);
extern S16BIT mcx_Element_EnableIrq (U16BIT deviceId, U16BIT busList, U16BIT element);
extern S16BIT mcx_Element_ElementGetIrq (U16BIT deviceId, U16BIT busList, U16BIT element, U16BIT* interruptStatusRegisterValue);

// Service Functions
extern S16BIT mcx_Transmit_1553_Message (U16BIT deviceId, U16BIT command, U16BIT* blockStatusWord, WORD* buffer, U16BIT* actualWordCount, U16BIT* status, U16BIT* tTag, U16BIT* options);
extern S16BIT mcx_Transmit_1553_Messages(U16BIT deviceId, U16BIT command, U16BIT* blockStatusWord, WORD* buffer, U16BIT numberOfShots, U16BIT* status, U16BIT* options);
extern S16BIT mcx_Send_Data_To_RT (U16BIT deviceId, U16BIT rt, U16BIT subAddress, U16BIT wordCount, WORD* buffer, U16BIT* blockStatusWord, U16BIT* status, U16BIT* tTag, U16BIT* options);
extern S16BIT mcx_Get_Data_From_RT (U16BIT deviceId, U16BIT rt, U16BIT subAddress, U16BIT wordCount, WORD* buffer, U16BIT* blockStatusWord, U16BIT* status, U16BIT* tTag, U16BIT* options);

extern S16BIT mcx_Read_Debug(U16BIT deviceId, U16BIT address, WORD bufferSize, WORD* buffer);
extern S16BIT mcx_Write_Debug(U16BIT deviceId, U16BIT address, WORD bufferSize, WORD* buffer);

extern S16BIT mcx_TestExternalLoopback_DevicetoDevice(U16BIT device0, U16BIT device1, U16BIT* resultD0A, U16BIT* resultD0B, U16BIT* resultD1A, U16BIT* resultD1B, BOOLEAN* badDataFound);

extern S16BIT mcx_wm_DumpMonitor_RawData (U16BIT deviceId, S8BIT* fileFullName, U32BIT lengthToDump, U16BIT options);
extern S16BIT mcx_wm_DumpMonitor_Cancel (U16BIT deviceId);

extern S16BIT mcx_Element_UpdateData(U16BIT deviceId, U16BIT busList, U16BIT element);
extern S16BIT mcx_Element_UpdateStatuses(U16BIT deviceId, U16BIT element, U16BIT rxStatus, U16BIT txStatus);
extern S16BIT mcx_Get_Buslist_TransmittedElements(U16BIT deviceId, U16BIT busList, U8BIT * elementsTransmitted);

extern S16BIT mcx_Read_17(U16BIT deviceId, U16BIT address, WORD bufferSize, WORD* buffer);
extern S16BIT mcx_GetApiDebugData (U16BIT deviceId, U32BIT* wordsPending, U32BIT* maxWordsPending);

extern S16BIT mcx_LoadMcxHw(char* path, int deviceIndex);
extern S16BIT mcx_TransmitSingleMessageOnce(U16BIT deviceId, U16BIT cmd, U16BIT* buffer, U16BIT size, U16BIT* BSW, U16BIT* rtStatus, bool emulateRt=false, bool busA=true, U16BIT gap=0);
extern S16BIT mcx_Transmitframe(U16BIT deviceId, U16BIT NumOfTimes,bool Bus, mcx_MsgStruct *cmdStruct);


#ifdef __cplusplus
}
#endif

#endif // McxAPIExport_INCLUDED