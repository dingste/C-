/*! \brief Resize
 *
 * Implementation of a component
 *
 * File:   Resize.cpp
 * Author: Dieter Steuten
 *
 */

#include "Resize.hpp"
#include <iostream>

Resize::Resize() {}

/* --- protected functionality --- */
bool Resize::P(bool run) {
    if (data.change_request && run) {
        /* put the processing function calls here */
        doResize();
        return true;
    }
    return false;
}

/* private processing functions */
void Resize::doResize() {
    std::vector<positionABS> transponded;
    positionABS aPoint = positionABS();
    positionABS ratio =  {(int) (data.targetSize.X / data.sourceSize.X), (int) (data.targetSize.Y / data.sourceSize.Y)};
    for (auto it = data.transpondVector.begin(); it != data.transpondVector.end(); ++it) {
        for (int scalePoint_X = 0; scalePoint_X < ratio.X; scalePoint_X++) {
            for (int scalePoint_Y = 0; scalePoint_Y < ratio.Y; scalePoint_Y++) {
                aPoint = {((*it).X * ratio.X + scalePoint_X), ((*it).Y * ratio.Y + scalePoint_Y)};
                transponded.push_back(aPoint);
            }
        }
    }

    data.transpondVector = (transponded);
    data.change_request = false;
}