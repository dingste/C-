/*! \brief Feeling
 * 
 * Implementation of a component
 *
 * File:   Feeling.cpp
 * Author: Dieter Steuten
 *
 */

/* --- Includes --- */
#include "Feeling.hpp"

/* --- CPP regular --- */
Feeling::Feeling() {}
Feeling::~Feeling() {}

/* --- protected functionalities --- */
bool Feeling::P(bool lauf){
    if (inner.eingabeWechsel && lauf){
        return true;
    }else{
        return false;
    }
}

const T_Feeling &Feeling::O(){
    return inner;
}

void Feeling::I(const T_Feeling &irgendwas){
    if (inner != irgendwas)    {
        inner.feeling_id = irgendwas.feeling_id;
        inner.eingabeWechsel = true;
    }
}
