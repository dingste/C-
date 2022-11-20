/*! \brief Ein
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   Ein.hpp
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

#ifndef I_Ein_H
#define I_Ein_H

/* --- Includes --- */
#include <stdint.h>

#include "Components/EVA/EVA.hpp"
#include "Components/Ein/Bitmap/Bitmap.hpp"
#include "Feeling/Feeling.hpp"

/* --- type --- */
struct T_Ein {
    bool eingabeWechsel = false;
    T_Bitmap bitmap = T_Bitmap();
    T_Feeling feeling = T_Feeling();
    bool operator!=(const T_Ein &pre) { return ((feeling != pre.feeling) || (bitmap != pre.bitmap)) ? true : false; }
};

/* --- Interface --- */
class I_Ein : public I_EVA<T_Ein> {
   public:
    virtual ~I_Ein() {}

    /* the **how** */
    virtual bool P(bool) = 0;
    virtual const T_Ein &O() = 0;
    virtual void I(const T_Ein &) = 0;
};

/* --- Decleration --- */
class Ein : public I_Ein {
   public:
    Ein();
    virtual ~Ein() {
        delete bmp_read;
        delete feeling;
    };

   protected:
    /* I_EVA */
    bool P(bool) override;
    const T_Ein &O() override;
    void I(const T_Ein &) override;

    /* I_Ein */

   private:
    /* - use of Components */
    I_Bitmap *bmp_read = new Bitmap();
    I_Feeling *feeling = new Feeling();

    /* - Member - */
    T_Ein inner = T_Ein();

    /* - copy-constructor - * /
    Ein(const Ein&) = default;
    Ein& operator=(const Ein&) = default;  */

    /* - Functions - */
};

#endif
