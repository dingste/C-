/*! \brief EVA
 * 
 * Decleration as a component
 * also providing its Interface
 *
 * File:   EVA.hpp
 * Author: Dieter Steuten
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

#ifndef I_EVA_H
#define I_EVA_H

/* --- Includes --- */
#include <stdint.h>

/* --- Interface --- */
template<typename T>
class I_EVA
{
public:
    virtual ~I_EVA() {}

    /* the **how** */
    virtual bool P(bool) = 0;
    virtual const T& O() = 0;
    virtual void I(const T&) = 0;
};

#endif
