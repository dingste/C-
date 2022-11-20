/*! \brief Filter
 *
 * Implementation of a component
 *
 * File:   Filter.cpp
 * Author: Dieter Steuten
 *
 */

/* --- Includes --- */
#include "Filter.hpp"

#include <random>

/* --- CPP regular --- */
Filter::Filter() {}
// switch to header: Filter::~Filter() {}

/* --- protected functionalities --- */
bool Filter::P(bool lauf) {
    if (data.eingabeWechsel && lauf) {
        drawWhiteNoise();
        return true;
    }
    return false;
}

void Filter::drawWhiteNoise() {
    auto it = data.flatcontent.begin();
    for (; it != data.flatcontent.end();) {
        if (std::rand() < (RAND_MAX / 2)) {
            it = data.flatcontent.erase(it);
        } else {
            ++it;
        }
    }
}