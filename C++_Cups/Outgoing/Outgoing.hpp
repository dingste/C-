/*! \brief Outgoing
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   Outgoing.hpp
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

#ifndef I_Outgoing_H
#define I_Outgoing_H

/* --- Includes --- */
#include <stdint.h>

#include <iostream>

#include "Components/EVA/EVA.hpp"
#include "Display/Display.hpp"
#include "Drive/Drive.hpp"

/* --- type --- */
struct T_Outgoing {
    char signature = 'X';
    bool change_request = false;
    Drive_Data_Create;
    Display_Data_Create;
    bool operator!=(const T_Outgoing& pre) { return (Drive_nq || Display_nq) ? true : false; }
};

/* --- Interface --- */
class I_Outgoing : public I_EVA<T_Outgoing> {
   public:
    virtual ~I_Outgoing() {
        Drive_Del_Instance;
        Display_Del_Instance;
    }

    /* the **howto access** */
    const T_Outgoing& O() override { return data; }
    void I(const T_Outgoing& outter) override {
        if (data != outter) {
            data = outter;
            data.change_request = true;
            Display_forward;
            Drive_forward;
        }
    }
    // override in concrete class virtual bool P(bool) = 0;
    /*
        std::ostream& operator<<(std::ostream& out, const T_Outgoing& transmit) {
            out << transmit.signature << SERIALIZE_START
                << transmit.foo << SERIALIZE_DELIMITER
                << transmit.foo << SERIALIZE_END;
            return out;
        }

        std::istream& operator>>(std::istream& in, T_Outgoing& transmit) {
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
    T_Outgoing data = T_Outgoing();
    Drive_New_Instance;
    Display_New_Instance;
};

/* --- Decleration --- */
class Outgoing : public I_Outgoing {
   public:
    Outgoing();
    virtual ~Outgoing(){};

   protected:
    /* mandatory I_EVA */
    bool P(bool) override; /* collect all to be do in this function */

    /* optional I_Outgoing */

   private: /* - use of further components (the 'new's) - */
    /* - Member - */

    /* - declaration of own private processing functions - */
};

/* get an easier access to derivate Input-Processing-Output Class */
#define Outgoing_Data_Create T_Outgoing Outgoing_Data_Reference = T_Outgoing()
#define Outgoing_New_Instance I_Outgoing* Outgoing_Object_Reference = new Outgoing()
#define Outgoing_Del_Instance delete Outgoing_Object_Reference
#define Outgoing_I(d) Outgoing_Object_Reference->I(d)
#define Outgoing_P(cr) Outgoing_Object_Reference->P(cr)
#define Outgoing_O data.Outgoing_Data_Reference = Outgoing_Object_Reference->O()
#define Outgoing_nq (Outgoing_Data_Reference != pre.Outgoing_Data_Reference)
#define Outgoing_condition (data.Outgoing_Data_Reference != outter.Outgoing_Data_Reference)
#define Outgoing_assign data.Outgoing_Data_Reference = outter.Outgoing_Data_Reference
#define Outgoing_forward                            \
    if (Outgoing_condition) {                       \
        Outgoing_assign;                            \
        Outgoing_I(outter.Outgoing_Data_Reference); \
    }
#define Outgoing_byte_in Outgoing_Data_Reference << T_Outgoing()
#define Outgoing_byte_out T_Outgoing() >> Outgoing_Data_Reference

#endif
