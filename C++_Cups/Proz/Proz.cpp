/*! \brief Proz
 *
 * Implementation of a component
 *
 * File:   Proz.cpp
 * Author: Dieter Steuten
 *
 */

/* --- Includes --- */
#include "Proz.hpp"

/* --- CPP regular --- */
Proz::Proz() {}

/* --- protected functionalities --- */
bool Proz::P(bool lauf) {
    if (data.eingabeWechsel && lauf) {
        Resize_P(lauf);
        PathDraw_P(lauf);
        face->P(lauf);
        Filter_P(lauf);
        return true;
    } else {
        return false;
    }
}

const T_Proz &Proz::O() {
    Resize_O;
    PathDraw_O;
    data.face = face->O();
    Filter_O;
    return data;
}

void Proz::I(const T_Proz &outter) {
    if (data != outter) {
        if (data.face != outter.face) {
            data.face = outter.face;
            face->I(outter.face);
        }
        Resize_forward;
        Filter_forward;
        PathDraw_forward;
        data.eingabeWechsel = true;
    }
}
