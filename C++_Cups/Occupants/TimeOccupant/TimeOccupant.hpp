/*! \brief TimeOccupant
 * 
 * Decleration as a component
 * also providing its Interface
 *
 * File:   TimeOccupant.hpp
 * Author: Dieter Steuten at <d.steuten@elk.de>
 *
 */

/// ```plantuml format="svg"
/// ```
///
/// #### Description
///
///
/// #### Technical Requirements
///
/// | ID  | Description                                                                    |
/// | --- | ------------------------------------------------------------------------------ |
/// | STR-xx  |                |
///
///
/// #### Functional Requirements
///
/// | ID  | Description                                                             |
/// | --- | ----------------------------------------------------------------------- |
/// | SFR-xx  |  |
///

#ifndef I_TimeOccupant_H
#define I_TimeOccupant_H

/* --- Includes --- */
#include <stdint.h>

/* --- for fast as macro for different scopes --- */
#ifdef BAREMETAL
    #define DELAY(duration_ms) \
        HAL_Delay(duration_ms);
#else
    #define DELAY(duration_ms)                                \
        for (long unsigned int i = 0; i < duration_ms; ++i) { \
            ;                                                 \
        }
    //no thread here std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));

#endif

/* --- Interface --- */
class I_TimeOccupant {
  public:
    virtual ~I_TimeOccupant() {
    }

    /* the **how** */
    virtual bool    onPassiveWait(int32_t)                                = 0;
    virtual bool    onDutyCycle(int32_t)                                  = 0;
    virtual int32_t onDeltaReference(int32_t)                             = 0;
    virtual void    setReference()                                        = 0;
    virtual void    onActiveWaitMilliseconds(uint32_t)     = 0;   //means blocking wait
    virtual void    onActiveWaitMicroseconds(uint32_t)     = 0;   //means blocking wait
    virtual int32_t onDuration()                                          = 0;
    virtual void    startCountDown(uint32_t countDownTime)                = 0;
    virtual bool    onCountdownExceeded()                                 = 0;
    virtual int32_t onRemainingTime()                                     = 0;
};

/* --- Decleration --- */
class TimeOccupant : public I_TimeOccupant {
  public:
    TimeOccupant();
    virtual ~TimeOccupant();

  protected:
    /* I_TimeOccupant */
    bool    onPassiveWait(int32_t) override;
    void    onActiveWaitMilliseconds(uint32_t) override;
    void    onActiveWaitMicroseconds(uint32_t)  override;
    bool    onDutyCycle(int32_t) override;
    int32_t onDeltaReference(int32_t) override;
    void    setReference() override;
    int32_t onDuration() override;
    void    startCountDown(uint32_t _countDownTime) override;
    bool    onCountdownExceeded() override;
    int32_t onRemainingTime() override;

  private:
    /* - use of Components */

    /* - Member - */
    int32_t referenceTime;
    int32_t countDownTime;

    /* - copy-constructor - * /
    TimeOccupant(const TimeOccupant&) = default;             
    TimeOccupant& operator=(const TimeOccupant&) = default;  */

    /* - Functions - */
};

#endif
