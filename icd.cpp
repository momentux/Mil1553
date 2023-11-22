#include "icd.h"
#include <iostream>
#include <basetsd.h>
#include <cstdint>

#pragma once

const double lsb1 = 0.064;             // velocity time tag
const double lsb2 = 0.00288209473473;  // 1.16272 * e^-6
const double lsb3 = 0.273480366721;    // 5.493 * e^-3
const double lsb4 = 0.4742218262;      // 9.525 * e^-3
const double lsb5 = 0.00042267334;     // 9.31 * e^-10
const double lsb6 = 1.2192;            // present alt
const double lsb7 = 0.273490324135;    // gcerror 5.4932 * e^-3
const double lsb8 = 0.002811814220082; // plat,plong 8.3819 * e^-8
const double lsb9 = 0.297368157277;    // roll,pitch,yaw 2.19727 * e^-2

void prepare(ICD_6_1_data data, UINT16 buffer[32])
{
    std::fill_n(buffer, 32, 0);
    UINT32 temp;

    buffer[0] = data.imumodeword1;
    buffer[1] = static_cast<UINT16>(data.velocitytimetag * lsb1);

    temp = static_cast<UINT32>(data.northvelocity * lsb2);
    buffer[2] = (temp >> 16) & 0xFFFF;       // Upper 16 bits
    buffer[3] = temp & 0xFFFF; 

    temp = static_cast<UINT32>(data.eastvelocity * lsb2);
    buffer[4] = (temp >> 16) & 0xFFFF;  
    buffer[5] = temp & 0xFFFF; 

    temp = static_cast<UINT32>(data.downvelocity * lsb2);
    buffer[6] = (temp >> 16) & 0xFFFF;  
    buffer[7] = temp & 0xFFFF; 

    buffer[8] = static_cast<UINT16>(data.platformazimuth * lsb3);
    buffer[9] = static_cast<UINT16>(data.roll * lsb3);
    buffer[10] = static_cast<UINT16>(data.pitch * lsb3);
    buffer[11] = static_cast<UINT16>(data.trueheading * lsb3);
    buffer[12] = static_cast<UINT16>(data.magnecticheading * lsb3);
    buffer[13] = static_cast<UINT16>(data.northacceleration * lsb4);
    buffer[14] = static_cast<UINT16>(data.eastacceleration * lsb4);
    buffer[15] = static_cast<UINT16>(data.verticalacceleration * lsb4);

    buffer[16] = static_cast<UINT16>(data.cnexx * lsb5);
    buffer[17] = static_cast<UINT16>(data.cnexx * lsb5);
    buffer[18] = static_cast<UINT16>(data.cnexy * lsb5);
    buffer[19] = static_cast<UINT16>(data.cnexy * lsb5);
    buffer[20] = static_cast<UINT16>(data.cneyz * lsb5);
    buffer[21] = static_cast<UINT16>(data.cneyz * lsb5);

    temp = static_cast<UINT32>(data.pplon * lsb8);
    buffer[22] = (temp >> 16) & 0xFFFF;
    buffer[23] = temp & 0xFFFF;

    buffer[24] = static_cast<UINT16>(data.presentalt * lsb6);
    buffer[25] = static_cast<UINT16>(data.gcstreeringerror * lsb7);

    temp = static_cast<UINT32>(data.pplat * lsb8);
    buffer[26] = (temp >> 16) & 0xFFFF;
    buffer[27] = temp & 0xFFFF;
    buffer[28] = data.imumodeword2;
    buffer[29] = static_cast<UINT16>(data.rollrate * lsb9);
    buffer[30] = static_cast<UINT16>(data.pitchrate * lsb9);
    buffer[31] = static_cast<UINT16>(data.yawrate * lsb9);
};

void doubleToUint16Buffer(ICD_6_2_data data,UINT16 buffer[32])
{
    std::fill_n(buffer, 32, 0);

    buffer[24] = static_cast<UINT16>(data.inustatus);
    buffer[25] = static_cast<UINT16>(data.loop);
    buffer[26] = data.imumodeword;
    buffer[27] = static_cast<UINT16>(data.srufailureindicators);
};

void doubleToUint16Buffer(ICD_6_3_data data, UINT16 buffer[32])
{
    std::fill_n(buffer, 32, 0);

    buffer[28] = static_cast<UINT32>(data.pplat * lsb8);
    buffer[29] = static_cast<UINT32>(data.pplon * lsb8);
    buffer[30] = static_cast<UINT16>(data.magneticheading * lsb3);
    buffer[31] = static_cast<UINT16>(data.aligntimeandstatus);
    buffer[32] = static_cast<UINT16>(data.winddirection * lsb7);
    buffer[33] = static_cast<UINT16>(data.windvelocity * 0.0625);
    buffer[34] = static_cast<UINT16>(data.presentgroundspeed * 0.0625);
    buffer[35] = static_cast<UINT16>(data.horizontalpositionfom);
    buffer[36] = static_cast<UINT16>(data.verticalpositionfom);
};

void doubleToUint16Buffer(ICD_6_4_data data, UINT16 buffer[32])
{
    std::fill_n(buffer, 32, 0);

    buffer[37] = static_cast<UINT16>(data.gpsstatus);
    buffer[38] = static_cast<UINT16>(data.gpsvalidity);
    buffer[39] = static_cast<UINT16>(data.satnorthspeedcomp);
    buffer[40] = static_cast<UINT16>(data.sateastspeedcomp);
    buffer[40] = static_cast<UINT16>(data.satvertspeedcomp);
    buffer[41] = static_cast<UINT32>(data.satellitelatitude);
    buffer[42] = static_cast<UINT32>(data.satellitelongitude);
    buffer[43] = static_cast<UINT16>(data.datasat);
    buffer[44] = static_cast<UINT16>(data.timesat);
    buffer[45] = static_cast<UINT16>(data.posdilutionofprecision);
    buffer[46] = static_cast<UINT16>(data.gpsfom);
    buffer[47] = static_cast<UINT16>(data.utctimetag);
};