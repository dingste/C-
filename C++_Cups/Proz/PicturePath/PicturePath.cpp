/*! \brief PicturePath
 *
 * Implementation of a component
 *
 * File:   PicturePath.cpp
 * Author: Dieter Steuten
 *
 */

/* --- Includes --- */
#include "PicturePath.hpp"
//#include <graphics.h>

//#include <GL/gl.h>
//#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>



/* --- CPP regular --- */
PicturePath::PicturePath() {
}

PicturePath::~PicturePath() {
}

/* --- protected functionalities --- */
bool PicturePath::P(bool lauf) {
    if (inner.eingabeWechsel && lauf) {

       //     while (inner.count > 0) {
        //        takeOne();
       //     }

            //   usleep(60000);
        

        return true;
    } else {
        return false;
    }
}

const T_PicturePath& PicturePath::O() {
    return inner;
}

void PicturePath::I(const T_PicturePath& irgendwas) {
    if (inner != irgendwas) {
      //  inner.count = irgendwas.bitmapData.size() - 1;

        inner.bitmapData = irgendwas.bitmapData;
        inner.eingabeWechsel = true;
    }
}

void PicturePath::takeOne() {
    if ( inner.count < inner.bitmapData.size()) {
        uint8_t pixel = 255 ;// inner.bitmapData.at(inner.count);

        if (pixel < 255) {
inner.pathData.push_back(inner.bitmapData.back()); inner.bitmapData.pop_back();
        } else {
              int trys = 1;
              while (trys <= PIXEL_MAX_AWAY) {
                  if (searchRight(trys) > 0) {
                      std::cout << "r";
                      break;
                  } else if (searchDown(trys) > 0) {
                      std::cout << "d";
                      break;
                  } else {
                      std::cout << " ";
                  }
                  trys++;
              }
        }

        //    inner.bitmapData.pop_back();
        if (inner.count % 15 == 0) {
            //y += 10;
            //x = 0;
             std::cout << std::endl;
        }
     //   inner.count--;
    }
}
void PicturePath::printOne() {}
int PicturePath::searchRight(uint8_t trys) {
    if ((inner.count - trys) >= 0) {
        uint8_t pixel = 255; //inner.bitmapData.at(inner.count - trys);
        if (pixel < 255) {
            return inner.count - trys;
        }
    }
    return 0;
}
int PicturePath::searchDown(uint8_t trys) {
    int downWithMod = inner.count % 15;
    if ((inner.count - (downWithMod * trys)) >= 0) {
        uint8_t pixel = 255; //inner.bitmapData.at(inner.count - (downWithMod * trys));
        if (pixel < 255) {
            return inner.count - (downWithMod * trys);
        }
    }
    return 0;
}