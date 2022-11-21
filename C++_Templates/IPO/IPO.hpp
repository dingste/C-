/*! \brief IPO
 * 
 * Decleration as a component
 * also providing its Interface
 *
 * File:   IPO.hpp
 * Author: Dieter Steuten
 *
 */

/// ```plantuml format="svg"
/// ```
///
/// #### Description
///
///
///

#ifndef I_IPO_H
#define I_IPO_H

/* --- Includes --- */
#include <stdint.h>

/* --- Interface --- */
template<typename T>
class I_IPO {
public:
    virtual ~I_IPO() {}

    /* the **how** */
    virtual bool P(bool) = 0;
    virtual const T& O() = 0;
    virtual void I(const T&) = 0;
};

#endif
