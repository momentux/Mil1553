#include <basetsd.h>

#pragma once
struct ICD_6_1_data
{
    UNIT16 imumodeword1 = 0;
    double velocitytimetag = 2;
    double northvelocity;    // fdm/jsbsim/velocities/v-north-fps
    double eastvelocity;     // fdm/jsbsim/velocities/v-east-fps
    double downvelocity;     // fdm/jsbsim/velocities/v-down-fps
    double platformazimuth;  // fdm/jsbsim/attitude/psi-deg
    double roll;             // fdm/jsbsim/attitude/phi-deg
    double pitch;            // fdm/jsbsim/attitude/theta-deg
    double trueheading;      // fdm/jsbsim/attitude/headint-true-rad
    double magnecticheading; // orientation/heading-magnetic-deg
    double northacceleration = 0.0;
    double eastacceleration = 0.0;
    double verticalacceleration = 0.0;
    double cnexx = 0.0;
    double cnexy = 0.0;
    double cneyz = 0.0;
    double presentpositionlongitudeword; // fdm/jsbsim/position/long-gc-deg
    double presentalt;                   // fdm/jsbsim/position/h-sl-meters
    double gcstreeringerror = 0.0;
    double presentpositionlatitudeword; // fdm/jsbsim/position/lat-gc-deg
    UINT16 imumodeword2 = 0;
    double rollrateword;  // fdm/jsbsim/velocities/phidot-rad_sec
    double pitchrateword; // fdm/jsbsim/velocities/thetadot-rad_sec
    double yawrateword;   // fdm/jsbsim/velocities/psidot-rad_sec
};

struct ICD_6_2_data
{
    double inustatus = 0.0;
    double loop = 0.0;
    UINT16 imumodeword2 = 0;
    double srufailureindicators = 0.0;
};
struct ICD_6_3_data
{
    double pplat = 0.0;
    double pplon = 0.0;
    double strmode = 0.0;
    double magneticheading = 0.0;
    double aligntimeandstatus = 0.0;
    double winddirection = 0.0;
    double windvelocity = 0.0;
    double presentgroundspeed = 0.0;
    double presenttruegroundtrack = 0.0;
    double horizontalpositionfom = 0.0;
    double verticalpositionfom = 0.0;
};
struct ICD_6_4_data
{
    double gpsstatus = 0.0;
    double gpsvalidity = 0.0;
    double satnorthspeedcomp = 0.0;
    double sateastspeedcomp = 0.0;
    double satvertspeedcomp = 0.0;
    double satellitelatitude = 0.0;
    double satellitelongitude = 0.0;
    double datasat = 0.0;
    double timesat = 0.0;
    double posdilutionofprecision = 0.0;
    double gpsfom = 0.0;
    double utctimetag = 0.0;
};

void prepare(ICD_6_1_data data, UINT16 buffer[32]);
void prepare(ICD_6_2_data data, UINT16 buffer[32]);
void prepare(ICD_6_3_data data, UINT16 buffer[32]);
void prepare(ICD_6_4_data data, UINT16 buffer[32]);