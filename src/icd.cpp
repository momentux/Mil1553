#include <iostream>
#include <cstdint>
#include "icd.h"

#pragma once

const double fpsTomps = 0.3048;
const double fpsTokts = 0.592484;
const double radToDeg = 57.2957795131;
const double lsb1 = 0.064;             // velocity time tag
const double lsb2 = 0.0000011672;  // 1.16272 * e^-6
const double lsb3 = 0.0025493;    // 5.493 * e^-3
const double lsb4 = 0.009525;      // 9.525 * e^-3
const double lsb5 = 0.000000000931;     // 9.31 * e^-10
const double lsb6 = 1.2192;            // present alt
const double lsb7 = 0.0054932;    // gcerror 5.4932 * e^-3
const double lsb8 = 0.000000083819; // plat,plong 8.3819 * e^-8
const double lsb9 = 0.0219727;    // roll,pitch,yaw 2.19727 * e^-2
const double lsb10 = 0.0625;           //  wind velocity
const double lsb11 = 0.03125;          // sat speed
const double lsb12 = 2;          // sat lat long


void prepare(ICD_6_1_data data, UINT16 buffer[32])
{
    std::fill_n(buffer, 32, 0);
    UINT32 temp;

    buffer[0] = data.imumodeword1;
    buffer[1] = static_cast<UINT16>(data.velocitytimetag / lsb1);

    temp = static_cast<UINT32>(data.northvelocity * fpsTomps / lsb2);
    buffer[2] = (temp >> 16) & 0xFFFF; // Upper 16 bits
    buffer[3] = temp & 0xFFFF;

    temp = static_cast<UINT32>(data.eastvelocity * fpsTomps / lsb2);
    buffer[4] = (temp >> 16) & 0xFFFF;
    buffer[5] = temp & 0xFFFF;

    temp = static_cast<UINT32>(data.downvelocity * fpsTomps / lsb2);
    buffer[6] = (temp >> 16) & 0xFFFF;
    buffer[7] = temp & 0xFFFF;

    buffer[8] = static_cast<UINT16>(data.platformazimuth / lsb3);
    buffer[9] = static_cast<UINT16>(data.roll / lsb3);
    buffer[10] = static_cast<UINT16>(data.pitch / lsb3);
    buffer[11] = static_cast<UINT16>(data.trueheading * radToDeg / lsb3);
    buffer[12] = static_cast<UINT16>(data.magnecticheading / lsb3);
    buffer[13] = static_cast<UINT16>(data.northacceleration / lsb4);
    buffer[14] = static_cast<UINT16>(data.eastacceleration / lsb4);
    buffer[15] = static_cast<UINT16>(data.verticalacceleration / lsb4);

    buffer[16] = static_cast<UINT16>(data.cnexx / lsb5);
    buffer[17] = static_cast<UINT16>(data.cnexx / lsb5);
    buffer[18] = static_cast<UINT16>(data.cnexy / lsb5);
    buffer[19] = static_cast<UINT16>(data.cnexy / lsb5);
    buffer[20] = static_cast<UINT16>(data.cneyz / lsb5);
    buffer[21] = static_cast<UINT16>(data.cneyz / lsb5);

    temp = static_cast<UINT32>(data.pplon / lsb8);
    buffer[22] = (temp >> 16) & 0xFFFF;
    buffer[23] = temp & 0xFFFF;

    buffer[24] = static_cast<UINT16>(data.presentalt / lsb6);
    buffer[25] = static_cast<UINT16>(data.gcstreeringerror / lsb7);

    temp = static_cast<UINT32>(data.pplat / lsb8);
    buffer[26] = (temp >> 16) & 0xFFFF;
    buffer[27] = temp & 0xFFFF;
    buffer[28] = data.imumodeword2;
    buffer[29] = static_cast<UINT16>(data.rollrate * radToDeg / lsb9);
    buffer[30] = static_cast<UINT16>(data.pitchrate * radToDeg / lsb9);
    buffer[31] = static_cast<UINT16>(data.yawrate * radToDeg / lsb9);
};

void prepare(ICD_6_2_data data, UINT16 buffer[32])
{
    std::fill_n(buffer, 32, 0);

    buffer[0] = data.inustatus;
    buffer[1] = data.loop;
    buffer[2] = data.imumodeword;
    buffer[3] = data.srufailureindicators;
};

void prepare(ICD_6_3_data data, UINT16 buffer[32])
{
    std::fill_n(buffer, 32, 0);
    UINT32 temp;

    temp = static_cast<UINT32>(data.pplat / lsb8);
    buffer[5] = (temp >> 16) & 0xFFFF;
    buffer[6] = temp & 0xFFFF;

    temp = static_cast<UINT32>(data.pplon / lsb8);
    buffer[7] = (temp >> 16) & 0xFFFF;
    buffer[8] = temp & 0xFFFF;

    buffer[16] = data.strmode;
    buffer[17] = static_cast<UINT16>(data.magneticheading / lsb3);
    buffer[18] = data.aligntimeandstatus;
    buffer[19] = static_cast<UINT16>(data.winddirection / lsb7);
    buffer[20] = static_cast<UINT16>(data.windvelocity / lsb10) << 3;
    buffer[21] = static_cast<UINT16>(data.presentgroundspeed / lsb10);
    buffer[22] = data.presenttruegroundtrack;
    buffer[22] = data.horizontalpositionfom;
    buffer[23] = data.verticalpositionfom;
};

void prepare(ICD_6_4_data data, UINT16 buffer[32])
{
    std::fill_n(buffer, 32, 0);
    UINT32 temp;

    buffer[0] = data.gpsstatus;
    buffer[1] = data.gpsvalidity;

    buffer[2] = static_cast<UINT16>(data.satnorthspeedcomp * fpsTokts / lsb11);
    buffer[3] = static_cast<UINT16>(data.sateastspeedcomp * fpsTokts / lsb11);
    buffer[4] = static_cast<UINT16>(data.satvertspeedcomp * fpsTokts / lsb11);

    temp = static_cast<UINT32>(data.satellitelatitude / lsb8);
    buffer[5] = (temp >> 16) & 0xFFFF;
    buffer[6] = temp & 0xFFFF;

    temp = static_cast<UINT32>(data.satellitelongitude / lsb8);
    buffer[7] = (temp >> 16) & 0xFFFF;
    buffer[8] = temp & 0xFFFF;

    buffer[9] = static_cast<UINT16>(data.satellitelatitude / lsb12);

    buffer[10] = (data.datesat[0] & 0x7F) | ((data.datesat[1] & 0x0F) << 7) | ((data.datesat[2] & 0x1F) << 11);
    buffer[11] = (data.timesat[0] & 0x1F) | ((data.timesat[1] & 0x3F) << 5);
    buffer[12] = data.timesat[2] & 0x3F;
    buffer[13] = data.posdilutionofprecision;
    buffer[14] = data.gpsfom;
    buffer[15] = (data.utctimetag % 50) << 8 | ((data.utctimetag / 50) % 50) ;
};
