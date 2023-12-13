#include "DeviceInterface.h"
#include "StdAfx.h"

UDPLanInterface::UDPLanInterface() {}

UDPLanInterface::UDPLanInterface(Int32 aSendPort, Int32 aRecvPort, Byte *IP, Byte aMode) {
  Byte Ip_Addr[20];
  Int32 sendSockSize = 1000000;
  Int32 recevSockSize = 1000000;

  WSADATA wsaData;
  int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0) {
    printf("WSAStartup failed with error: %d\n", iResult);
  }

  if (aMode == TX_MODE || aMode == RX_TX_MODE) {
    /*************Tx Variables Init **********/
    strcpy_s(Ip_Addr, IP);

    TxSockAddr.sin_family = AF_INET;
    TxSockAddr.sin_port = htons(aSendPort);
    TxSockAddr.sin_addr.s_addr = INADDR_ANY; // inet_addr(Ip_Addr);

    TxSockAddrLen = sizeof(TxSockAddr);

    TxSockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (TxSockfd < 0) {
      printf("Cannot Create Socket");
    } else {
      printf("Socket Created for send port no.: %d for IP:", aSendPort);
    }

    setsockopt(TxSockfd, SOL_SOCKET, SO_SNDBUF, (char *)(&sendSockSize), sizeof(sendSockSize));
  }

  if (aMode == RX_MODE || aMode == RX_TX_MODE) {
    /*************Rx Variables Init **********/
    RxSockAddr.sin_family = AF_INET;
    RxSockAddr.sin_port = htons(aRecvPort);
    RxSockAddr.sin_addr.s_addr = INADDR_ANY;
    RxSockAddrLen = sizeof(RxSockAddr);

    if ((RxSockfd = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR) {
      printf("Cannot Create Socket");
    }

    setsockopt(RxSockfd, SOL_SOCKET, SO_RCVBUF, (char *)(&recevSockSize), sizeof(recevSockSize));

    if (bind(RxSockfd, (struct sockaddr *)&RxSockAddr, RxSockAddrLen) < 0) {
      printf("Error in bind");
    } else {
      printf("Socket bound for Rx port no.: %d", aRecvPort);
    }
  }
}

UDPLanInterface::~UDPLanInterface() {
#if VXWORKS7_BUILD
  close(TxSockfd);
  close(RxSockfd);
#else
  closesocket(TxSockfd);
  closesocket(RxSockfd);
#endif
}

//********************************************************************************
// # Function Name    - SendPack
// # Input Variable   - Byte *buffer, uInt16 size
// # Output Variable  - count
//********************************************************************************
void inline UDPLanInterface::SendPack(Byte *buffer, Int32 size) {
  Int32 count;

  if ((count = sendto(TxSockfd, buffer, size, 0, (struct sockaddr *)&TxSockAddr, TxSockAddrLen)) == ERROR) {
    perror("Error in Sending Data");
    // printf("%s\n ",inet_ntoa(TxSockAddr.sin_addr));
  }
}

//********************************************************************************
// # Function Name  - RecvPack
// # Input Variable - Byte *buffer, uInt16 *size
// # Output Variable  - count
//********************************************************************************
Int32 inline UDPLanInterface::RecvPack(Byte *buffer, Int32 *size) {
  Int32 count;

  if ((count = recvfrom(RxSockfd, buffer, MAX_MSG_SIZE, 0, (struct sockaddr *)&RxSockAddr, &RxSockAddrLen)) == ERROR) {
    perror("Lanif: Err Data Recp");
    return ERROR;
  }
  *size = count;
  return count;
}
