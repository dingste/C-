/*! \brief Drive
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   Drive.hpp
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

#ifndef I_Drive_H
#define I_Drive_H

/* --- Includes --- */
#include <stdint.h>

#include <complex>
#include <iostream>
#include <vector>

#include "Components/EVA/Definitions.hpp"
#include "Components/EVA/EVA.hpp"
#include "Components/Occupants/TimeOccupant/TimeOccupant.hpp"

struct Complex_Polar {
    int sum = 0.0;
    int deg = 0;
    Complex_Polar &from(const int &re, const int &im) {
        std::complex<double> z(re, im);
        sum = (int)std::abs(z);
        deg = (int)(std::arg(z) * 180 / 3.1415);
        return *this;  //{sum, deg};
    };
};

struct Wheel {
    int pin = 0;
    enum _direction { up,
                      down,
                      stop } direction = stop;
    uint8_t force = 0;
    bool operator!=(const Wheel &pre) { return (direction != pre.direction || force != pre.force || pin != pre.pin) ? true : false; }
};

/* --- type --- */
struct T_Drive {
    char signature = 'X';
    bool change_request = false;
    Wheel up_left = Wheel();
    Wheel up_right = Wheel();
    Wheel down_left = Wheel();
    Wheel down_right = Wheel();
    std::vector<lineABS> pathData;
    unsigned int count = 0;
    enum _driving { start,
                    stop,
                    continous } driving = stop;
    bool operator!=(const T_Drive &pre) { return (driving != pre.driving || up_left != pre.up_left || up_right != pre.up_right || down_left != pre.down_left || down_right != pre.down_right) ? true : false; }
};

/* --- Interface --- */
class I_Drive : public I_EVA<T_Drive> {
   public:
    virtual ~I_Drive() {}

    /* the **howto access** */
    const T_Drive &O() override { return data; }
    void I(const T_Drive &outter) override {
        if (data != outter) {
            data = outter;
            data.change_request = true;
        }
    }
    // override in concrete class virtual bool P(bool) = 0;
    /*
     std::ostream& operator<<(std::ostream& out, const T_Drive& transmit) {
     out << transmit.signature << SERIALIZE_START
         << transmit.foo << SERIALIZE_DELIMITER
         << transmit.foo  << SERIALIZE_END;
     return out;
     }

     std::istream& operator>>(std::istream& in, T_Drive& transmit) {
     char singlechar;

     in >> singlechar;
     transmit.signature = (char) singlechar;
     in >> singlechar;
     if (singlechar == SERIALIZE_START) {
         in >> transmit.foo;
         in >> singlechar;
         if (singlechar == SERIALIZE_DELIMITER) {
             in >> transmit.foo;
             in >> singlechar;
             if (singlechar != SERIALIZE_END) {
                 //deserializationAssert();
                 //in.clear();
             }
         }
     }
     return in;
     }
     */
   protected:
    T_Drive data = T_Drive();
};

/* --- Decleration --- */
class Drive : public I_Drive {
   public:
    Drive();
    virtual ~Drive(){/* delete the 'new's (if exists) directly here .. for more readiness */};

   protected:
    /* mandatory I_EVA */
    bool P(bool) override; /* collect all to be do in this function */

    /* optional I_Drive */

   private: /* - use of further components (the 'new's) - */
    /* - Member - */
    Complex_Polar lineConvert = Complex_Polar();
    I_TimeOccupant *duration = new TimeOccupant();

    /* - declaration of own private processing functions - */
    const Complex_Polar &convert();
    bool drive(const Complex_Polar &);
    void left_side(float duty);
    void right_side(float duty);
};

/* get an easier access to derivate Input-Processing-Output Class */
#define Drive_Data_Create T_Drive Drive_Data_Reference = T_Drive()
#define Drive_New_Instance I_Drive *Drive_Object_Reference = new Drive()
#define Drive_Del_Instance delete Drive_Object_Reference
#define Drive_I(d) Drive_Object_Reference->I(d)
#define Drive_P(cr) Drive_Object_Reference->P(cr)
#define Drive_O data.Drive_Data_Reference = Drive_Object_Reference->O()
#define Drive_nq (Drive_Data_Reference != pre.Drive_Data_Reference)
#define Drive_condition (data.Drive_Data_Reference != outter.Drive_Data_Reference)
#define Drive_assign data.Drive_Data_Reference = outter.Drive_Data_Reference
#define Drive_forward Drive_I(outter.Drive_Data_Reference); /* \
     if (Drive_condition) {                                    \
         Drive_assign;                                         \
         Drive_I(outter.Drive_Data_Reference);                 \
     }*/
#define Drive_byte_in Drive_Data_Reference << T_Drive()
#define Drive_byte_out T_Drive() >> Drive_Data_Reference

#endif
