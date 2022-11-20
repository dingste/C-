/*! \brief Face
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   Face.hpp
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

#ifndef I_Face_H
#define I_Face_H

/* --- Includes --- */
#include <stdint.h>

#include <map>
#include <vector>

#include "Components/EVA/Definitions.hpp"
#include "Components/EVA/EVA.hpp"
#include "Components/Ein/Feeling/Feeling.hpp"

struct bruch {
    int Z;
    int N;
};
struct punkt {
    bruch X;
    bruch Y;
};
struct rechteck {
    punkt startXY;
    punkt endXY;
};
struct laengen {
    int breite;
    int hoehe;
};

/* --- type --- */
struct T_Face {
    bool eingabeWechsel = false;
    C_Feelings feeling_face = C_Feelings::none;
    int hoehe = 0;
    int breite = 0;
    std::vector<positionABS> flatcontent;
    bool operator!=(const T_Face& pre) { return (feeling_face != pre.feeling_face) ? true : false; }
};

/* --- Interface --- */
class I_Face : public I_EVA<T_Face> {
   public:
    virtual ~I_Face() {}

    /* the **how** */
    virtual bool P(bool) = 0;
    virtual const T_Face& O() = 0;
    virtual void I(const T_Face&) = 0;
};

/* --- Decleration --- */
class Face : public I_Face {
   public:
    Face();
    virtual ~Face(){};

   protected:
    /* I_EVA */
    bool P(bool) override;
    const T_Face& O() override;
    void I(const T_Face&) override;

    /* I_Face */

   private:
    /* - use of Components */

    /* - Member - */
    T_Face inner = T_Face();
    bool fill = false;
    bool noisy = false;
    struct faceArea {
        rechteck auge_links{{{1, 10}, {1, 10}}, {{4, 10}, {4, 10}}};
        rechteck auge_rechts{{{6, 10}, {1, 10}}, {{9, 10}, {4, 10}}};
        rechteck mund_links{{{1, 10}, {7, 10}}, {{3, 10}, {9, 10}}};
        rechteck mund_mitte{{{3, 10}, {7, 10}}, {{7, 10}, {9, 10}}};
        rechteck mund_rechts{{{7, 10}, {7, 10}}, {{9, 10}, {9, 10}}};
    } _areas;

    struct faceAugen {
        rechteck _0{{{0, 3}, {3, 3}}, {{3, 3}, {3, 3}}};
        rechteck strichunten{{{0, 3}, {0, 3}}, {{2, 3}, {2, 3}}};
        rechteck linkshoch{{{0, 3}, {1, 3}}, {{2, 3}, {2, 3}}};
        rechteck linksunten{{{1, 3}, {1, 3}}, {{2, 3}, {3, 3}}};
        rechteck rechtsunten{{{1, 3}, {1, 3}}, {{3, 3}, {3, 3}}};
        rechteck rechtshoch{{{1, 3}, {0, 3}}, {{3, 3}, {2, 3}}};
        rechteck rechtsvoll{{{1, 3}, {0, 3}}, {{3, 3}, {3, 3}}};
        rechteck linksvoll{{{0, 3}, {0, 3}}, {{2, 3}, {3, 3}}};
    } _eyes;

    struct faceMund {
        rechteck oben{{{0, 3}, {0, 3}}, {{3, 3}, {0, 3}}};    // oben
        rechteck unten{{{0, 3}, {3, 3}}, {{3, 3}, {3, 3}}};   // unten
        rechteck mittig{{{0, 3}, {2, 3}}, {{3, 3}, {2, 3}}};  // mittig
        rechteck voll{{{0, 3}, {0, 3}}, {{3, 3}, {3, 3}}};    // voll
        rechteck leer{{{0, 3}, {0, 3}}, {{0, 3}, {0, 3}}};    // leer
        rechteck diagru{{{0, 3}, {0, 3}}, {{3, 3}, {3, 3}}};  // diag runter
        rechteck diagra{{{0, 3}, {3, 3}}, {{3, 3}, {0, 3}}};  // diag rauf
    } _mouth;

    /*

    00 1 2 3
    00
    1
    2
    3

    */

    struct face {
        rechteck Alinks;
        rechteck Arechts;
        rechteck Mlinks;
        rechteck Mmitte;
        rechteck Mrechts;
    };

    std::map<C_Feelings, face> faces{
        {C_Feelings::none, {_eyes.strichunten, _eyes.strichunten, _mouth.leer, _mouth.leer, _mouth.leer}},
        {C_Feelings::happy, {_eyes.rechtsvoll, _eyes.linksvoll, _mouth.diagru, _mouth.unten, _mouth.diagra}},
        {C_Feelings::blink, {_eyes.linkshoch, _eyes.strichunten, _mouth.diagru, _mouth.leer, _mouth.leer}},
        {C_Feelings::currious, {_eyes.rechtsunten, _eyes.linksunten, _mouth.leer, _mouth.unten, _mouth.diagra}},
        {C_Feelings::angry, {_eyes.strichunten, _eyes.strichunten, _mouth.diagra, _mouth.voll, _mouth.diagru}},
        {C_Feelings::laugh, {_eyes.strichunten, _eyes.strichunten, _mouth.diagru, _mouth.voll, _mouth.diagra}},
        {C_Feelings::sleep_, {_eyes.strichunten, _eyes.strichunten, _mouth.leer, _mouth.voll, _mouth.leer}},
        {C_Feelings::sad, {_eyes.rechtsvoll, _eyes.linksvoll, _mouth.diagra, _mouth.oben, _mouth.diagru}}};

    enum filledTo {
        left,
        right,
        all
    };

    /* - copy-constructor - * /
    Face(const Face&) = default;
    Face& operator=(const Face&) = default;  */

    /* - Functions - */
    positionABS getPositions(const laengen& disp, const punkt& rect);
    laengen getLengths(const laengen& disp, const rechteck& rect);
    void drawDiagIntoVector(const int&, const int&, const int&, const int&, Face::filledTo);
    void drawFaceForVector(const laengen& disp, const face& currentFace);
    void drawRectangleIntoVector(const int&, const int&, const int&, const int&);

};

#endif
