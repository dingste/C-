/*! \brief Display
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   Display.hpp
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

#ifndef I_Display_H
#define I_Display_H

/* --- Includes --- */
#include <stdint.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Components/EVA/Definitions.hpp"
#include "Components/EVA/EVA.hpp"

/* --- type --- */
struct T_Display {
    char signature = 'X';
    bool change_request = false;
    int hoehe_y = 0;
    int breite_x = 0;
    std::vector<positionABS> flatcontent;
    std::vector<lineABS> linecontent;
    bool operator!=(const T_Display &pre) {
        bool eq = equal(begin(flatcontent), end(flatcontent),
                        begin(pre.flatcontent), end(pre.flatcontent),
                        [](const positionABS &w1, const positionABS &w2) { return (w1 != w2); });
        bool eq2 = equal(begin(linecontent), end(linecontent),
                         begin(pre.linecontent), end(pre.linecontent),
                         [](const lineABS &w1, const lineABS &w2) { return ((w1.line_start != w2.line_start)); });
        return (eq || eq2) ? true : false;
    }
};

/* --- Interface --- */
class I_Display : public I_EVA<T_Display> {
   public:
    virtual ~I_Display() {}

    /* the **howto access** */
    const T_Display &O() override { return data; }
    void I(const T_Display &outter) override {
        if (data != outter) {
            data = outter;
            data.change_request = true;
        }
    }
    // override in concrete class virtual bool P(bool) = 0;
/*
    std::ostream &operator<<(std::ostream &out, const T_Display &transmit) {
        out << transmit.signature << SERIALIZE_START
            << transmit.foo << SERIALIZE_DELIMITER
            << transmit.foo << SERIALIZE_END;
        return out;
    }

    std::istream &operator>>(std::istream &in, T_Display &transmit) {
        char singlechar;

        in >> singlechar;
        transmit.signature = (char)singlechar;
        in >> singlechar;
        if (singlechar == SERIALIZE_START) {
            in >> transmit.foo;
            in >> singlechar;
            if (singlechar == SERIALIZE_DELIMITER) {
                in >> transmit.foo;
                in >> singlechar;
                if (singlechar != SERIALIZE_END) {
                    // deserializationAssert();
                    // in.clear();
                }
            }
        }
        return in;
    }
*/
   protected:
    T_Display data = T_Display();
};

/* --- Decleration --- */
class Display : public I_Display {
   public:
    Display();
    virtual ~Display(){/* delete the 'new's (if exists) directly here .. for more readiness */};

   protected:
    /* mandatory I_EVA */
    bool P(bool) override; /* collect all to be do in this function */

    /* optional I_Display */

   private: /* - use of further components (the 'new's) - */
            /* - Member - */

    /* - declaration of own private processing functions - */
    bool popVectorEmpty();
};

/* get an easier access to derivate Input-Processing-Output Class */
#define Display_Data_Create T_Display Display_Data_Reference = T_Display()
#define Display_New_Instance I_Display *Display_Object_Reference = new Display()
#define Display_Del_Instance delete Display_Object_Reference
#define Display_I(d) Display_Object_Reference->I(d)
#define Display_P(cr) Display_Object_Reference->P(cr)
#define Display_O data.Display_Data_Reference = Display_Object_Reference->O()
#define Display_nq (Display_Data_Reference != pre.Display_Data_Reference)
#define Display_condition (data.Display_Data_Reference != outter.Display_Data_Reference)
#define Display_assign data.Display_Data_Reference = outter.Display_Data_Reference
#define Display_forward                           \
    if (Display_condition) {                      \
        Display_assign;                           \
        Display_I(outter.Display_Data_Reference); \
    }
#define Display_byte_in Display_Data_Reference << T_Display()
#define Display_byte_out T_Display() >> Display_Data_Reference

#endif
