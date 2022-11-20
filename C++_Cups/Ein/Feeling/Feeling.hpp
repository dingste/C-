/*! \brief Feeling
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   Feeling.hpp
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

#ifndef I_Feeling_H
#define I_Feeling_H

/* --- Includes --- */
#include <stdint.h>

#include "Components/EVA/EVA.hpp"

enum C_Feelings {
    none,
    happy,
    angry,
    laugh,
    sad,
    sleep_,
    currious,
    blink
};

/* --- type --- */
struct T_Feeling {
    bool eingabeWechsel = false;
    C_Feelings feeling_id = C_Feelings::none;
    bool operator!=(const T_Feeling &pre) { return (feeling_id != pre.feeling_id) ? true : false; }
};

/* --- Interface --- */
class I_Feeling : public I_EVA<T_Feeling> {
   public:
    virtual ~I_Feeling() {}

    /* the **how** */
    virtual bool P(bool) = 0;
    virtual const T_Feeling &O() = 0;
    virtual void I(const T_Feeling &) = 0;
};

/* --- Decleration --- */
class Feeling : public I_Feeling {
   public:
    Feeling();
    virtual ~Feeling();

   protected:
    /* I_EVA */
    bool P(bool) override;
    const T_Feeling &O() override;
    void I(const T_Feeling &) override;

    /* I_Feeling */

   private:
    /* - use of Components */

    /* - Member - */
    T_Feeling inner = T_Feeling();

    /* - copy-constructor - * /
    Feeling(const Feeling&) = default;
    Feeling& operator=(const Feeling&) = default;  */

    /* - Functions - */
};

#endif
