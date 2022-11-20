/*! \brief PathDraw
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   PathDraw.hpp
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

#ifndef I_PathDraw_H
#define I_PathDraw_H

/* --- Includes --- */
#include <stdint.h>

#include <iostream>
#include <vector>

#include "Components/EVA/Definitions.hpp"
#include "Components/EVA/EVA.hpp"

/* --- type --- */
struct T_PathDraw {
    char signature = 'X';
    bool change_request = false;
    std::vector<positionABS> bitmapData;
    std::vector<lineABS> pathData;
    unsigned long count = 0;
    bool operator!=(const T_PathDraw& pre) { return (count != pre.count) ? true : false; }
};

/* --- Interface --- */
class I_PathDraw : public I_EVA<T_PathDraw> {
   public:
    virtual ~I_PathDraw() {}

    /* the **howto access** */
    const T_PathDraw& O() override { return data; }
    void I(const T_PathDraw& outter) override {
        if (data != outter) {
            data = outter;
            data.change_request = true;
        }
    }
    // override in concrete class virtual bool P(bool) = 0;

   protected:
    T_PathDraw data = T_PathDraw();
};

/* --- Decleration --- */
class PathDraw : public I_PathDraw {
   public:
    PathDraw();
    virtual ~PathDraw(){/* delete the 'new's (if exists) directly here .. for more readiness */};

   protected:
    /* mandatory I_EVA */
    bool P(bool) override; /* collect all to be do in this function */

    /* optional I_PathDraw */

   private: /* - use of further components (the 'new's) - */
    static const uint8_t PIXEL_MAX_AWAY = 2;
positionABS trySearch;
    /* - copy-constructor - * /
    PicturePath(const PicturePath&) = default;
    PicturePath& operator=(const PicturePath&) = default;  */

    /* - Functions - */
    void simpleExchange();
    void countedExchange();
    void takeOne();
    void printOne();
    int searchRight(uint8_t trys);
    int searchDown(uint8_t trys);
    void aggregateToLine();
    lineDirection searchDirection(const positionABS& ,const lineDirection&);
     positionABS searchNextStart(const positionABS&);
};

/* get an easier access to derivate Input-Processing-Output Class */
#define PathDraw_Data_Create T_PathDraw PathDraw_Data_Reference = T_PathDraw()
#define PathDraw_New_Instance I_PathDraw* PathDraw_Object_Reference = new PathDraw()
#define PathDraw_Del_Instance delete PathDraw_Object_Reference
#define PathDraw_I(d) PathDraw_Object_Reference->I(d)
#define PathDraw_P(cr) PathDraw_Object_Reference->P(cr)
#define PathDraw_O data.PathDraw_Data_Reference = PathDraw_Object_Reference->O()
#define PathDraw_nq (PathDraw_Data_Reference != pre.PathDraw_Data_Reference)
#define PathDraw_condition (data.PathDraw_Data_Reference != outter.PathDraw_Data_Reference)
#define PathDraw_assign data.PathDraw_Data_Reference = outter.PathDraw_Data_Reference
#define PathDraw_forward                            \
    if (PathDraw_condition) {                       \
        PathDraw_assign;                            \
        PathDraw_I(outter.PathDraw_Data_Reference); \
    }
#define PathDraw_byte_in PathDraw_Data_Reference << T_PathDraw()
#define PathDraw_byte_out T_PathDraw() >> PathDraw_Data_Reference

#endif
