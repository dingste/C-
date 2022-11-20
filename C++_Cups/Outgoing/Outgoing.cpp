/*! \brief Outgoing
 *
 * Implementation of a component
 *
 * File:   Outgoing.cpp
 * Author: Dieter Steuten
 *
 */

#include "Outgoing.hpp"
Outgoing::Outgoing() {}

/* --- protected functionality --- */
bool Outgoing::P(bool run) {
    if (data.change_request && run) {
        /* put the processing function calls here */
        Drive_P(run);
    //    Display_P(run);
        return true;
    }
    return false;
}

/* private processing functions */
