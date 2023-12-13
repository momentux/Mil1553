#include <basetsd.h>

#pragma once
struct ICD_6_1_data
{
    UINT16 imumodeword1 = 0;
    double velocitytimetag = 2;
    double northvelocity;    // velocities/v-north-fps
    double eastvelocity;     // velocities/v-east-fps
    double downvelocity;     // velocities/v-down-fps
    double platformazimuth;  // attitude/psi-deg
    double roll;             // attitude/phi-deg
    double pitch;            // attitude/theta-deg
    double trueheading;      // attitude/headint-true-rad
    double magnecticheading; // /orientation/heading-magnetic-deg
    double northacceleration = 0.0;
    double eastacceleration = 0.0;
    double verticalacceleration = 0.0;
    double cnexx = 0.0;
    double cnexy = 0.0;
    double cneyz = 0.0;
    double pplon;      // position/long-gc-deg
    double presentalt; // position/h-sl-meters
    double gcstreeringerror = 0.0;
    double pplat; // position/lat-gc-deg
    UINT16 imumodeword2 = 0;
    double rollrate;  // velocities/phidot-rad_sec
    double pitchrate; // velocities/thetadot-rad_sec
    double yawrate;   // velocities/psidot-rad_sec
};

struct ICD_6_2_data
{
    UINT16 inustatus = 0;
    UINT16 loop = (1 << 8) - 1;
    UINT16 imumodeword = 0;
    UINT16 srufailureindicators = (4 << 0) | (4 << 5) | (4 << 10);
};
struct ICD_6_3_data
{
    double pplat; // position/lat-gc-deg
    double pplon; // position/long-gc-deg
    UINT16 strmode = 1;
    double magneticheading; // /orientation/heading-magnetic-deg
    UINT16 aligntimeandstatus = (2 << 6) | 120;
    double winddirection;      // /environment/wind-from-heading-deg
    double windvelocity;       // /environment/windspeed-kts
    double presentgroundspeed; // /velocities/groundspeed
    UINT16 presenttruegroundtrack = 0;
    UINT16 horizontalpositionfom = 1;
    UINT16 verticalpositionfom = 1;
};
struct ICD_6_4_data
{
    UINT16 gpsstatus = (0b11) | (1 << 2) | (0b1010 << 12);
    UINT16 gpsvalidity = 0b11111;
    double satnorthspeedcomp = 0.0;  // velocities/v-north-fps
    double sateastspeedcomp = 0.0;   // velocities/v-east-fps
    double satvertspeedcomp = 0.0;   // velocities/v-down-fps
    double satellitelatitude = 0.0;  // position/long-gc-deg
    double satellitelongitude = 0.0; // position/lat-gc-deg
    int datesat[3];                  // /sim/time/real [utc is not good, set utc at system level]
    int timesat[3];                  // /sim/time/real
    UINT16 posdilutionofprecision = 0;
    UINT16 gpsfom = 0b1;
    UINT16 utctimetag; // /sim/time/steady-clock-sec || // simulation/frame
};

void prepare(ICD_6_1_data data, UINT16 buffer[32]);
void prepare(ICD_6_2_data data, UINT16 buffer[32]);
void prepare(ICD_6_3_data data, UINT16 buffer[32]);
void prepare(ICD_6_4_data data, UINT16 buffer[32]);