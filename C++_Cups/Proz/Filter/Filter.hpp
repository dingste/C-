/*! \brief Filter
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   Filter.hpp
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

#ifndef I_Filter_H
#define I_Filter_H

/* --- Includes --- */
#include <stdint.h>

#include <vector>

#include "Components/EVA/Definitions.hpp"
#include "Components/EVA/EVA.hpp"

/* --- type --- */
struct T_Filter {
    bool eingabeWechsel = false;
    bool noise = false;
    std::vector<positionABS> flatcontent;
    bool operator!=(const T_Filter &pre) { return (noise != pre.noise) ? true : false; }
};

/* --- Interface --- */
class I_Filter : public I_EVA<T_Filter> {
   public:
    virtual ~I_Filter() {}

    const T_Filter &O() override {
        return data;
    }
    void I(const T_Filter &outter) override {
        if (data != outter) {
            data = outter;
            data.eingabeWechsel = true;
        }
    }

   protected:
    T_Filter data = T_Filter();
};

/* --- Decleration --- */
class Filter : public I_Filter {
   public:
    Filter();
    virtual ~Filter(){
        /* delete the 'new's directly here .. for more readiness */

    };

   protected:
    /* I_EVA */
    bool P(bool) override;

    /* I_Filter */

   private:
    /* - use of Components */

    /* - Member - * /
    T_Filter data = T_Filter();*/

    /* - copy-constructor - * /
    Filter(const Filter&) = default;
    Filter& operator=(const Filter&) = default;  */

    /* - Functions - */
    void drawWhiteNoise();
};

#define Filter_Data_Create T_Filter Filter_Data_Reference = T_Filter()
#define Filter_Instance I_Filter *Filter_Object_Reference = new Filter()
#define Filter_Delete delete Filter_Object_Reference
#define Filter_I(d) Filter_Object_Reference->I(d)
#define Filter_P(cr) Filter_Object_Reference->P(cr)
#define Filter_O data.Filter_Data_Reference = Filter_Object_Reference->O()
#define Filter_nq (Filter_Data_Reference != pre.Filter_Data_Reference)
#define Filter_condition (data.Filter_Data_Reference != outter.Filter_Data_Reference)
#define Filter_assign data.Filter_Data_Reference = outter.Filter_Data_Reference
#define Filter_forward                          \
    if (Filter_condition) {                     \
        Filter_assign;                          \
        Filter_I(outter.Filter_Data_Reference); \
    }
#endif
