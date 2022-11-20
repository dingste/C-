/*! \brief TimeOccupant
 * 
 * Implementation of a component
 *
 * File:   TimeOccupant.cpp
 * Author: Dieter Steuten at <d.steuten@elk.de>
 *
 */

/* --- Includes --- */
#include "TimeOccupant.hpp"
#ifdef BAREMETAL
    #if defined(GATEWAY) || defined(CONTROL)
extern TIM_HandleTypeDef htim1;
        #define HAL_TIMER
    #endif
#else
    #include <chrono>
#endif

/* --- CPP regular --- */
TimeOccupant::TimeOccupant() {
    referenceTime = 0;
    countDownTime = 0;
#ifdef HAL_TIMER
    if (HAL_TIM_Base_GetState(&htim1) == HAL_TIM_STATE_READY) {
        HAL_TIM_Base_Start(&htim1);
    }
#endif
}
TimeOccupant::~TimeOccupant() {
    referenceTime = 0;
    countDownTime = 0;
#ifdef HAL_TIMER
    HAL_TIM_Base_Stop(&htim1);
#endif
}

/* --- protected functionalities --- */
int32_t TimeOccupant::onDuration() {
#ifdef BAREMETAL
    return ((uint32_t) HAL_GetTick() - referenceTime);   // in milliseconds
#else
    std::chrono::time_point<std::chrono::system_clock> now      = std::chrono::system_clock::now();
    auto                                               duration = now.time_since_epoch();
    auto                                               millis   = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return (millis - referenceTime);
#endif
}

bool TimeOccupant::onPassiveWait(int32_t ms_wait) {
    if (onDuration() >= ms_wait) {
        return true;
    } else {
        return false;
    }
}

int32_t TimeOccupant::onDeltaReference(int32_t compare) {
    return (compare - referenceTime);
}

void TimeOccupant::setReference() {
#ifdef BAREMETAL
    referenceTime = HAL_GetTick();
#else
    std::chrono::time_point<std::chrono::system_clock> now      = std::chrono::system_clock::now();
    auto                                               duration = now.time_since_epoch();
    auto                                               millis   = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    referenceTime                                               = millis;
#endif
}

bool TimeOccupant::onDutyCycle(int32_t cycleTime) {
    if (onPassiveWait(cycleTime)) {
#ifdef BAREMETAL
        referenceTime = (int32_t) HAL_GetTick() + cycleTime;
#else
        std::chrono::time_point<std::chrono::system_clock> now      = std::chrono::system_clock::now();
        auto                                               duration = now.time_since_epoch();
        auto                                               millis   = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        referenceTime                                               = millis + cycleTime;
#endif
        return true;
    }
    return false;
}

void TimeOccupant::onActiveWaitMilliseconds(uint32_t ms_wait) {
    DELAY(ms_wait);
}

void TimeOccupant::onActiveWaitMicroseconds(uint32_t microsecondsToWait) {
#ifdef HAL_TIMER
    if (HAL_TIM_Base_GetState(&htim1) == HAL_TIM_STATE_BUSY) {
        __HAL_TIM_SET_COUNTER(&htim1, 0);   // set the counter value a 0
        while (__HAL_TIM_GET_COUNTER(&htim1) < microsecondsToWait)
            ;   // wait for the counter to reach the us input in the parameter
    }
#endif
uint32_t voidLoop =0;
        while (voidLoop < microsecondsToWait){voidLoop++;}
            
}
void TimeOccupant::startCountDown(uint32_t _countDownTime) {
    countDownTime = _countDownTime;
    setReference();
}

int32_t TimeOccupant::onRemainingTime() {
    return countDownTime - onDuration();
}

bool TimeOccupant::onCountdownExceeded() {
    return (onRemainingTime() <= 0);
}
