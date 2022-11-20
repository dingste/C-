/*! \brief Resize
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   Resize.hpp
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

#ifndef I_Resize_H
#define I_Resize_H

/* --- Includes --- */
#include <stdint.h>

#include <iostream>
#include <vector>

#include "Components/EVA/Definitions.hpp"
#include "Components/EVA/EVA.hpp"

/* --- type --- */
struct T_Resize {
    char signature = 'X';
    bool change_request = false;
    std::vector<positionABS> transpondVector;
    positionABS sourceSize = {0, 0};
    positionABS targetSize = {0, 0};
    bool operator!=(const T_Resize &pre) { return (targetSize != pre.targetSize) ? true : false; }
};

/* --- Interface --- */
class I_Resize : public I_EVA<T_Resize> {
   public:
    virtual ~I_Resize() {}

    /* the **howto access** */
    const T_Resize &O() override { return data; }
    void I(const T_Resize &outter) override {
            data = outter;
            data.change_request = true;
    }
    // override in concrete class virtual bool P(bool) = 0;

   protected:
    T_Resize data = T_Resize();
};

/* --- Decleration --- */
class Resize : public I_Resize {
   public:
    Resize();
    virtual ~Resize(){/* delete the 'new's (if exists) directly here .. for more readiness */};

   protected:
    /* mandatory I_EVA */
    bool P(bool) override; /* collect all to be do in this function */

    /* optional I_Resize */
   private: /* - use of further components (the 'new's) - */
    /* - Member - */

    /* - declaration of own private processing functions - */
    void doResize() ;
};

/* get an easier access to derivate Input-Processing-Output Class */
#define Resize_Data_Create T_Resize Resize_Data_Reference = T_Resize()
#define Resize_New_Instance I_Resize *Resize_Object_Reference = new Resize()
#define Resize_Del_Instance delete Resize_Object_Reference
#define Resize_I(d) Resize_Object_Reference->I(d)
#define Resize_P(cr) Resize_Object_Reference->P(cr)
#define Resize_O data.Resize_Data_Reference = Resize_Object_Reference->O()
#define Resize_nq (Resize_Data_Reference != pre.Resize_Data_Reference)
#define Resize_condition (data.Resize_Data_Reference != outter.Resize_Data_Reference)
#define Resize_assign data.Resize_Data_Reference = outter.Resize_Data_Reference
#define Resize_forward                          \
    if (Resize_condition) {                     \
        Resize_assign;                          \
        Resize_I(outter.Resize_Data_Reference); \
    }
#define Resize_byte_in Resize_Data_Reference << T_Resize()
#define Resize_byte_out T_Resize() >> Resize_Data_Reference

#endif
