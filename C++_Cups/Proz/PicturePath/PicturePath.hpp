/*! \brief PicturePath
 *
 * Decleration as a component
 * also providing its Interface
 *
 * File:   PicturePath.hpp
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

#ifndef I_PicturePath_H
#define I_PicturePath_H

/* --- Includes --- */
#include <stdint.h>

#include <vector>

#include "Components/EVA/EVA.hpp"
#include "Components/EVA/Definitions.hpp"

/* --- type --- */
struct T_PicturePath {
    bool eingabeWechsel = false;
    std::vector<positionABS> bitmapData;
    std::vector<positionABS> pathData;
    unsigned long count =0;
    bool operator!=(const T_PicturePath &pre) { return (count != pre.count) ? true : false; }
};

/* --- Interface --- */
class I_PicturePath : public I_EVA<T_PicturePath> {
   public:
    virtual ~I_PicturePath() {}

    /* the **how** */
    virtual bool P(bool) = 0;
    virtual const T_PicturePath &O() = 0;
    virtual void I(const T_PicturePath &) = 0;
};

/* --- Decleration --- */
class PicturePath : public I_PicturePath {
   public:
    PicturePath();
    virtual ~PicturePath();

   protected:
    /* I_EVA */
    bool P(bool) override;
    const T_PicturePath &O() override;
    void I(const T_PicturePath &) override;

    /* I_PicturePath */

   private:
    /* - use of Components */

    /* - Member - */
    T_PicturePath inner = T_PicturePath();
    static const uint8_t PIXEL_MAX_AWAY = 2;

    /* - copy-constructor - * /
    PicturePath(const PicturePath&) = default;
    PicturePath& operator=(const PicturePath&) = default;  */

    /* - Functions - */
    void takeOne();
    void printOne();
    int searchRight(uint8_t trys);
    int searchDown(uint8_t trys);
};

#endif
