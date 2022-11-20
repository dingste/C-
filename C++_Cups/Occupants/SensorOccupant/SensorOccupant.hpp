/*! \brief SensorOccupant
 * 
 * Decleration as a component
 * also providing its Interface
 *
 * File:   SensorOccupant.hpp
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

#ifndef I_SensorOccupant_H
#define I_SensorOccupant_H

/* --- Includes --- */
#include "Components/MeasurementContinent/PhysicalSensorsState/TPhysicalSensorsState.hpp"
#include "Components/MeasurementContinent/TimeOccupant/TimeOccupant.hpp"
#include <algorithm>
#include <cstdint>
#include <limits>
#include <numeric>
#include <stdint.h>
#include <vector>

enum averageOver {
    VIA_COUNT,
    VIA_DURATION
};

/* --- Interface --- */
class I_SensorOccupant {
  public:
    virtual ~I_SensorOccupant() {
    }

    /* the **how** */
    virtual void     doZeroing(int32_t)        = 0;
    virtual void     pushLast(int32_t)         = 0;
    virtual int32_t  popAverage()              = 0;
    virtual int32_t  getMaxDynamic()           = 0;
    virtual int32_t  getMinDynamic()           = 0;
    virtual int32_t  getMaxStatic()            = 0;
    virtual int32_t  getMinStatic()            = 0;
    virtual uint32_t getAveragedDifferential() = 0;
};

/* --- Decleration --- */
class SensorOccupant : public I_SensorOccupant {
  public:
    explicit SensorOccupant(uint8_t amount);
    virtual ~SensorOccupant();

  protected:
    /* I_SensorOccupant */
    void     doZeroing(int32_t) override;
    void     pushLast(int32_t) override;
    int32_t  popAverage() override;
    int32_t  getMaxDynamic() override;
    int32_t  getMinDynamic() override;
    int32_t  getMaxStatic() override;
    int32_t  getMinStatic() override;
    uint32_t getAveragedDifferential() override;

  private:
    /* - use of Components */

    /* - Member - */
    int32_t              countOrTime        = 0;
    int32_t              average            = 0;
    int32_t              offset             = 0;
    int32_t              staticMax          = 0;
    int32_t              staticMin          = 0;
    std::vector<int32_t> valueSink          = std::vector<int32_t>();
    C_ZEROING_STATE      zeroingState       = C_ZEROING_STATE::UNKNOWN;
    int32_t              zeroingMaximumSpan = 0;

    /* really the equal number (2147483647 & 2147483646) in AC convention manner? verified? */
    static const int32_t ZEROING_IN_PROGRESS_VALUE = std::numeric_limits<int32_t>::max();       // convention with AC for signalling if the calibration is still in progress
    static const int32_t ZEROING_FAILED_VALUE      = std::numeric_limits<int32_t>::max() - 1;   // convention with AC for signalling if the calibration failed

    std::vector<int32_t> differences = std::vector<int32_t>();
    I_TimeOccupant*      durationForZeroing;

    /* - copy-constructor - * /
    SensorOccupant(const SensorOccupant&) = default;             
    SensorOccupant& operator=(const SensorOccupant&) = default;  */

    /* - Functions - */
    int32_t getOffsetCalculated();
};

#endif
