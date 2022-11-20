/*! \brief Ein
 *
 * Implementation of a component
 *
 * File:   Ein.cpp
 * Author: Dieter Steuten
 *
 */

/* --- Includes --- */
#include "Ein.hpp"

/* --- CPP regular --- */
Ein::Ein() {}

/* --- protected functionalities --- */
bool Ein::P(bool lauf) {
    if (inner.eingabeWechsel && lauf) {
        return (bmp_read->P(lauf) || feeling->P(lauf));
    }
    return false;
}

const T_Ein &Ein::O() {
    inner.bitmap = bmp_read->O();
    inner.feeling = feeling->O();
    return inner;
}

void Ein::I(const T_Ein &irgendwas) {
    if (inner != irgendwas) {
        if (inner.bitmap != irgendwas.bitmap)
            bmp_read->I(irgendwas.bitmap);
        if (inner.feeling != irgendwas.feeling)
            feeling->I(irgendwas.feeling);
        inner = irgendwas;
        inner.eingabeWechsel = true;
    }
}
