/*! \brief Drive
 *
 * Implementation of a component
 *
 * File:   Drive.cpp
 * Author: Dieter Steuten
 *
 */

#include "Drive.hpp"
Drive::Drive() {}

/* --- protected functionality --- */
bool Drive::P(bool run) {
    if (/*data.change_request &&*/ run) {
        while (data.count <= data.pathData.size()) {
            drive(convert());
            data.count++;
        }
        return true;
    }
    return false;
}

/* private processing functions */
const Complex_Polar& Drive::convert() {
    if (data.count < data.pathData.size() && !data.pathData.empty()) {
        lineABS lineToConvert = data.pathData.at(data.count);
        return (lineConvert.from((lineToConvert.line_end.X - lineToConvert.line_start.X), (lineToConvert.line_end.Y - lineToConvert.line_start.Y)));
    }
    return lineConvert;
}

bool Drive::drive(const Complex_Polar& driveTrail) {
    int calc;
    if (driveTrail.deg >= 0) {
        calc = ((driveTrail.deg / 90) - 1);
    } else {
        calc = ((driveTrail.deg / 90) + 1);
    }

    left_side(driveTrail.sum * calc);
    right_side(driveTrail.sum * calc * (-1));
duration->onActiveWaitMilliseconds(driveTrail.sum * calc * 10);
    return true;
}

void Drive::left_side(float duty) {
    if (duty != 0) {
        float d = duty / 1;
        data.up_left.force = d;
        data.down_left.force = d;
        std::cout << " Left:" << d;
    }
}

void Drive::right_side(float duty) {
    if (duty != 0) {
        float d = duty / 1;
        data.up_right.force = d;
        data.down_right.force = d;
        std::cout << " Right:" << d << std::endl;
    }
}