/*! \brief Proz
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   Proz.hpp
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

#ifndef I_Proz_H
#define I_Proz_H

/* --- Includes --- */
#include <stdint.h>

#include "Components/EVA/EVA.hpp"
#include "Components/Proz/Face/Face.hpp"
#include "Components/Proz/Filter/Filter.hpp"
#include "Components/Proz/PathDraw/PathDraw.hpp"
#include "Components/Proz/Resize/Resize.hpp"

/* --- type --- */
struct T_Proz {
    bool eingabeWechsel = false;
    T_Face face = T_Face();
    Resize_Data_Create;
    Filter_Data_Create;
    PathDraw_Data_Create;
    bool operator!=(const T_Proz &pre) { return ((face != pre.face)|| Resize_nq || PathDraw_nq || Filter_nq) ? true : false; }
};

/* --- Interface --- */
class I_Proz : public I_EVA<T_Proz> {
   public:
    virtual ~I_Proz() {}

    /* the **how** */
    virtual bool P(bool) = 0;
    virtual const T_Proz &O() = 0;
    virtual void I(const T_Proz &) = 0;
};

/* --- Decleration --- */
class Proz : public I_Proz {
   public:
    Proz();
    virtual ~Proz() {
        delete face;
        Resize_Del_Instance;
        Filter_Delete;
        PathDraw_Del_Instance;
    };

   protected:
    /* I_EVA */
    bool P(bool) override;
    const T_Proz &O() override;
    void I(const T_Proz &) override;

    /* I_Proz */

   private:
    /* - use of Components */

    /* - Member - */
    T_Proz data = T_Proz();

    I_Face *face = new Face();
    Resize_New_Instance;
    PathDraw_New_Instance;
    Filter_Instance;
    /* - copy-constructor - * /
    Proz(const Proz&) = default;
    Proz& operator=(const Proz&) = default;  */

    /* - Functions - */
};

#endif
