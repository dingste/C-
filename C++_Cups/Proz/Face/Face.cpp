/*! \brief Face
 *
 * Implementation of a component
 *
 * File:   Face.cpp
 * Author: Dieter Steuten
 *
 */

/* --- Includes --- */
#include "Face.hpp"

#include <bits/std_abs.h>

#include <iostream>


/* --- CPP regular --- */
Face::Face() {}

/* --- protected functionalities --- */
bool Face::P(bool lauf) {
    if (inner.eingabeWechsel && lauf) {
        drawFaceForVector({inner.hoehe, inner.breite}, faces[inner.feeling_face]);
        fill = ((inner.feeling_face == C_Feelings::laugh) ||
                (inner.feeling_face == C_Feelings::sad))
                   ? true
                   : false;
        return true;
    } else {
        return false;
    }
}

const T_Face& Face::O() {
    return inner;
}

void Face::I(const T_Face& irgendwas) {
    if (inner != irgendwas) {
        inner.feeling_face = irgendwas.feeling_face;
        inner.hoehe = irgendwas.hoehe;
        inner.breite = irgendwas.breite;
        inner.eingabeWechsel = true;
    } 
}

positionABS Face::getPositions(const laengen& disp, const punkt& rect) {
    return {(disp.breite * rect.X.Z / rect.X.N), (disp.hoehe * rect.Y.Z / rect.Y.N)};
};

laengen Face::getLengths(const laengen& disp, const rechteck& rect) {
    return {(disp.breite * (rect.endXY.X.Z - rect.startXY.X.Z) / rect.endXY.X.N), (disp.hoehe * (rect.endXY.Y.Z - rect.startXY.Y.Z) / rect.endXY.Y.N)};
};

void Face::drawFaceForVector(const laengen& disp, const face& currentFace) {
    inner.flatcontent.clear();

    // auge links
    drawRectangleIntoVector(
        getPositions(disp, _areas.auge_links.startXY).X + getPositions(getLengths(disp, _areas.auge_links), currentFace.Alinks.startXY).X,
        getPositions(disp, _areas.auge_links.startXY).Y + getPositions(getLengths(disp, _areas.auge_links), currentFace.Alinks.startXY).Y,
        getLengths(getLengths(disp, _areas.auge_links), currentFace.Alinks).breite,
        getLengths(getLengths(disp, _areas.auge_links), currentFace.Alinks).hoehe);

    // auge rechts
    drawRectangleIntoVector(
        getPositions(disp, _areas.auge_rechts.startXY).X + getPositions(getLengths(disp, _areas.auge_rechts), currentFace.Arechts.startXY).X,
        getPositions(disp, _areas.auge_rechts.startXY).Y + getPositions(getLengths(disp, _areas.auge_rechts), currentFace.Arechts.startXY).Y,
        getLengths(getLengths(disp, _areas.auge_rechts), currentFace.Arechts).breite,
        getLengths(getLengths(disp, _areas.auge_rechts), currentFace.Arechts).hoehe);

    // mundwinkel links
    drawDiagIntoVector(
        getPositions(disp, _areas.mund_links.startXY).X + getPositions(getLengths(disp, _areas.mund_links), currentFace.Mlinks.startXY).X,
        getPositions(disp, _areas.mund_links.startXY).Y + getPositions(getLengths(disp, _areas.mund_links), currentFace.Mlinks.startXY).Y,
        getLengths(getLengths(disp, _areas.mund_links), currentFace.Mlinks).breite,
        getLengths(getLengths(disp, _areas.mund_links), currentFace.Mlinks).hoehe, Face::filledTo::right);

    // mund mitte
    drawDiagIntoVector(
        getPositions(disp, _areas.mund_mitte.startXY).X + getPositions(getLengths(disp, _areas.mund_mitte), currentFace.Mmitte.startXY).X,
        getPositions(disp, _areas.mund_mitte.startXY).Y + getPositions(getLengths(disp, _areas.mund_mitte), currentFace.Mmitte.startXY).Y,
        getLengths(getLengths(disp, _areas.mund_mitte), currentFace.Mmitte).breite,
        getLengths(getLengths(disp, _areas.mund_mitte), currentFace.Mmitte).hoehe, Face::filledTo::all);

    // mundwinkel rechts
    drawDiagIntoVector(
        getPositions(disp, _areas.mund_rechts.startXY).X + getPositions(getLengths(disp, _areas.mund_rechts), currentFace.Mrechts.startXY).X,
        getPositions(disp, _areas.mund_rechts.startXY).Y + getPositions(getLengths(disp, _areas.mund_rechts), currentFace.Mrechts.startXY).Y,
        getLengths(getLengths(disp, _areas.mund_rechts), currentFace.Mrechts).breite,
        getLengths(getLengths(disp, _areas.mund_rechts), currentFace.Mrechts).hoehe, Face::filledTo::left);

    noisy = false;
}

void Face::drawRectangleIntoVector(const int& _x, const int& _y, const int& _b, const int& _h) {
    positionABS apoint;
    for (int x_b = _x; x_b <= (_x + _b); x_b++) {
        for (int y_h = _y; y_h <= (_y + _h); y_h++) {
            apoint = {x_b, y_h};
            inner.flatcontent.push_back(apoint);
        }
    }
}

void Face::drawDiagIntoVector(const int& _x, const int& _y, const int& _b, const int& _h, Face::filledTo direction) {
    // f(y)= x * m + c

    if (direction == Face::all) {
        if (fill)
            drawRectangleIntoVector(_x, _y, _b, _h);
        else
            drawRectangleIntoVector(_x, _y + _h, _b, 1);
        return;
    }

    bool revert = false;
    if ((_h <= 0) || (_b <= 0)) {
        revert = true;
    }

    for (int bb = 0; bb < _b; bb++) {
        if (revert) {
            drawRectangleIntoVector(_x + bb, _y - bb, 1, 1);
            if (fill) {
                drawRectangleIntoVector(_x + bb, _y - bb, 1, bb);
            }
        } else {
            drawRectangleIntoVector(_x + bb, _y + bb, 1, 1);
            if (fill) {
                drawRectangleIntoVector(_x, _y + bb, bb, 1);
            }
        }
    }
}

