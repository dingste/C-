/*! \brief SensorOccupant
 * 
 * Implementation of a component
 *
 * File:   SensorOccupant.cpp
 * Author: Dieter Steuten at <d.steuten@elk.de>
 *
 */

/* --- Includes --- */
#include "SensorOccupant.hpp"
#include <cstdint>

/* --- CPP regular --- */
SensorOccupant::SensorOccupant(uint8_t amount) {
    countOrTime = amount;
    valueSink.reserve(amount);
    durationForZeroing = new TimeOccupant();
}

SensorOccupant::~SensorOccupant() {
}

/* --- protected functionalities --- */

void SensorOccupant::doZeroing(int32_t maximumSpan) {
    if (zeroingState != C_ZEROING_STATE::IN_PROGRESS) {
        durationForZeroing->setReference();
        zeroingState       = C_ZEROING_STATE::IN_PROGRESS;
        zeroingMaximumSpan = maximumSpan;
        valueSink.clear();
    }
}

void SensorOccupant::pushLast(int32_t newValue) {
    //take one out and put something new in
    valueSink.reserve(countOrTime);
    differences.reserve(countOrTime);
    if (valueSink.size() > (unsigned long) countOrTime) {
        valueSink.erase(valueSink.begin());
        if (zeroingState == C_ZEROING_STATE::IN_PROGRESS) {
            int32_t measurementDynamic = getMaxDynamic() - getMinDynamic();
            if (measurementDynamic > zeroingMaximumSpan) {
                zeroingState = C_ZEROING_STATE::FAILED;
            } else {
                zeroingState = C_ZEROING_STATE::SUCCESSFUL;

                offset -= popAverage();
            }
        }
    }

    valueSink.push_back(newValue + offset);
}

int32_t SensorOccupant::popAverage() {
    int32_t zeroValue = 0;
    if (valueSink.size() > 0) {
        average = std::accumulate(valueSink.begin(), valueSink.end(), zeroValue) / static_cast<int32_t>(valueSink.size());
    } else {
        average = 0;
    }

    int32_t returnValue = 0;
    switch (zeroingState) {
        case C_ZEROING_STATE::UNKNOWN:
            returnValue = average;
            break;
        case C_ZEROING_STATE::SUCCESSFUL:
            returnValue = average;
            break;
        case C_ZEROING_STATE::IN_PROGRESS:
            if (durationForZeroing->onPassiveWait(10000)) {
                zeroingState = C_ZEROING_STATE::FAILED;
                returnValue  = ZEROING_FAILED_VALUE;
            } else {
                returnValue = ZEROING_IN_PROGRESS_VALUE;
            }
            break;
        case C_ZEROING_STATE::FAILED:
            returnValue = ZEROING_FAILED_VALUE;
            break;
    }

    return returnValue;
}

int32_t SensorOccupant::getMaxDynamic() {
    if (valueSink.size() > 0) {
        return *max_element(valueSink.begin(), valueSink.end());
    } else {
        return 0;
    }
}
int32_t SensorOccupant::getMinDynamic() {
    if (valueSink.size() > 0) {
        return *min_element(valueSink.begin(), valueSink.end());
    } else {
        return 0;
    }
}
int32_t SensorOccupant::getMaxStatic() {
    int32_t dyn = getMaxDynamic();
    if (staticMax == 0 || dyn > staticMax) {
        staticMax = dyn;
    }
    return staticMax;
}
int32_t SensorOccupant::getMinStatic() {
    int32_t dyn = getMinDynamic();
    if (staticMax == 0 || dyn < staticMin) {
        staticMin = dyn;
    }
    return staticMin;
}
int32_t SensorOccupant::getOffsetCalculated() {
    return std::abs((int32_t) (getMinDynamic() - getMaxDynamic())) / 2;   // this abs() is used from clang?!
}

uint32_t SensorOccupant::getAveragedDifferential() {
    differences = valueSink;   //.clear();

    if (valueSink.size() > 2) {
        std::adjacent_difference(valueSink.begin(), valueSink.end(), differences.begin());
        if (differences.size() > 0) {
            differences.erase(differences.begin());
        }
        valueSink.pop_back();
    }
    uint32_t accumulatedAbsoluteDifferences = 0;
    for (auto element : differences) {
        accumulatedAbsoluteDifferences += std::abs(element);
    }

    uint32_t averagedDifferences = 0;
    if (differences.size() > 0) {
        averagedDifferences = accumulatedAbsoluteDifferences / differences.size();
    }
    return averagedDifferences;
}
