/*! \brief NAME
 * 
 * Implementation of a component
 *
 * File:   NAME.cpp
 * Author: Dieter Steuten
 *
 */

#include "NAME.hpp"
NAME::NAME() {}

/* --- protected functionality --- */
bool NAME::P(bool run){
    if (data.change_request && run){
        //derivate _P(run)
        return true;
    }
    return false;
}

/* private processing functions */
