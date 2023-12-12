#ifndef _DEV_IF_
#define _DEV_IF_

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>

#include "ltypes.h"

#define RX_MODE 0
#define TX_MODE 1
#define RX_TX_MODE 2

class DevIf {
   public:
    DevIf(){};

    virtual ~DevIf(){};
    virtual void SendPack(Byte *buffer, Int32 size) = 0;
    virtual Int32 RecvPack(Byte *buffer, Int32 *size) = 0;
};

class UDPLanInterface : public DevIf {
   private:
    struct sockaddr_in TxSockAddr, RxSockAddr;
    Int32 RxSockAddrLen, TxSockAddrLen;
    Int32 TxSockfd, RxSockfd;
    Byte DstIPAddr[20];
    Int32 debug;

   public:
    UDPLanInterface();

    UDPLanInterface(Int32 aSendPort, Int32 aRecvPort, Byte *IP, Byte aMode);
    virtual ~UDPLanInterface();

    virtual void inline SendPack(Byte *buffer, Int32 size);
    virtual Int32 inline RecvPack(Byte *buffer, Int32 *size);
};

#endif
