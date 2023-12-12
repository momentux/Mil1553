#include <sstream>
#include <stdexcept>
#include <string>
#include "icd.h"
#include <iostream>


bool parseDouble(const std::string& cell, double& value) {
    try {
        value = std::stod(cell);
        return true;
    } catch (const std::invalid_argument& e) {
        // Handle invalid argument exception
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return false;
    } catch (const std::out_of_range& e) {
        // Handle out-of-range exception
        std::cerr << "Out of range: " << e.what() << std::endl;
        return false;
    }
}

bool parseInt(const std::string& cell, int& value) {
    try {
        value = std::stoi(cell);
        return true;
    } catch (const std::invalid_argument& e) {
        // Handle invalid argument exception
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return false;
    } catch (const std::out_of_range& e) {
        // Handle out-of-range exception
        std::cerr << "Out of range: " << e.what() << std::endl;
        return false;
    }
}

int ParseFGMessage(const std::string& dataString, ICD_6_1_data& data1, ICD_6_2_data& data2, ICD_6_3_data& data3, ICD_6_4_data& data4) {
    std::istringstream lineStream(dataString);
    std::string cell;
    int fieldCount = 0;
    const int expectedFieldCount = 24;  // Adjust this based on actual data structure

    while (std::getline(lineStream, cell, ',')) {
        switch (fieldCount) {
            case 0:
                if (!parseDouble(cell, data1.velocitytimetag)) return -1;
                break;
            case 1:
                if (!parseDouble(cell, data1.northvelocity)) return -1;
                data4.satnorthspeedcomp = data1.northvelocity;
                break;
            case 2:
                if (!parseDouble(cell, data1.eastvelocity)) return -1;
                data4.sateastspeedcomp = data1.eastvelocity;
                break;
            case 3:
                if (!parseDouble(cell, data1.downvelocity)) return -1;
                data4.satvertspeedcomp = data1.downvelocity;
                break;
            case 4:
                if (!parseDouble(cell, data1.platformazimuth)) return -1;
                break;
            case 5:
                if (!parseDouble(cell, data1.roll)) return -1;
                break;
            case 6:
                if (!parseDouble(cell, data1.pitch)) return -1;
                break;
            case 7:
                if (!parseDouble(cell, data1.trueheading)) return -1;
                break;
            case 8:
                if (!parseDouble(cell, data1.magnecticheading)) return -1;
                data3.magneticheading = data1.magnecticheading;
                break;
            case 9:
                if (!parseDouble(cell, data1.pplon)) return -1;
                data3.pplon = data1.pplon;
                break;
            case 10:
                if (!parseDouble(cell, data1.presentalt)) return -1;
                break;
            case 11:
                if (!parseDouble(cell, data1.pplat)) return -1;
                data3.pplat = data1.pplat;
                break;
            case 12:
                if (!parseDouble(cell, data1.rollrate)) return -1;
                break;
            case 13:
                if (!parseDouble(cell, data1.pitchrate)) return -1;
                break;
            case 14:
                if (!parseDouble(cell, data1.yawrate)) return -1;
                break;
            case 15:
                if (!parseDouble(cell, data3.winddirection)) return -1;
                break;
            case 16:
                if (!parseDouble(cell, data3.windvelocity)) return -1;
                break;
            case 17:
                if (!parseDouble(cell, data3.presentgroundspeed)) return -1;
                break;
            case 18:
                if (!parseInt(cell, data4.datesat[0])) return -1;
                break;
            case 19:
                if (!parseInt(cell, data4.datesat[1])) return -1;
                break;
            case 20:
                if (!parseInt(cell, data4.datesat[2])) return -1;
                break;
            case 21:
                if (!parseInt(cell, data4.timesat[0])) return -1;
                break;
            case 22:
                if (!parseInt(cell, data4.timesat[1])) return -1;
                break;
            case 23:
                if (!parseInt(cell, data4.timesat[2])) return -1;
                break;
            default:
                break;
        }
        fieldCount++;
    }

    if (fieldCount > 0 && fieldCount < expectedFieldCount ) {
        // Not enough values
        return -1;
    }

    return 0;  // Success
}
